#!/usr/bin/env python3
"""
OSINT-style contact lookup: reads a CSV with facebook_url and name,
searches the public web for email and phone, writes a new CSV with
facebook_url, name, email, phone.

Uses DuckDuckGo search (no API key). Contact info is from publicly
indexed pages (LinkedIn, company sites, etc.), not from Facebook.
"""

import csv
import re
import sys
import time
from pathlib import Path

# Optional: duckduckgo_search. Install with: pip install duckduckgo-search
try:
    from duckduckgo_search import DDGS
except ImportError:
    DDGS = None

# --- Regex patterns (email and phone) ---
EMAIL_PATTERN = re.compile(
    r"\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b"
)
# International phone: +prefix, (xxx), xxx-xxxx, etc. Min 7 digits.
PHONE_PATTERN = re.compile(
    r"(?:\+?\d{1,4}[-.\s]?)?(?:\(?\d{2,4}\)?[-.\s]?)?\d{3,4}[-.\s]?\d{3,4}(?:[-.\s]?\d{1,4})?\b"
)

# Reject obvious false positives
SKIP_EMAIL_DOMAINS = {
    "example.com", "test.com", "email.com", "domain.com",
    "sentry.io", "wixpress.com", "facebook.com", "youtube.com",
    "twitter.com", "linkedin.com", "github.com", "google.com",
    "apple.com", "amazon.com", "cloudflare.com", "schema.org",
}
SKIP_EMAIL_LOCAL = {"noreply", "no-reply", "support", "info", "contact", "admin", "mail"}
# Skip short number sequences that are likely not phones (e.g. years, IDs)
MIN_PHONE_DIGITS = 7


def normalize_phone(s: str) -> str:
    digits = re.sub(r"\D", "", s)
    return digits if len(digits) >= MIN_PHONE_DIGITS else ""


def extract_emails(text: str) -> list[str]:
    if not text:
        return []
    found = set()
    for m in EMAIL_PATTERN.finditer(text):
        email = m.group(0).lower()
        domain = email.split("@")[-1].lower()
        local = email.split("@")[0].lower()
        if domain in SKIP_EMAIL_DOMAINS:
            continue
        if any(s in local for s in SKIP_EMAIL_LOCAL) and len(found) == 0:
            # Allow one generic (e.g. contact@company) if nothing else
            pass
        found.add(email)
    return list(found)[:3]  # max 3 per source


def extract_phones(text: str) -> list[str]:
    if not text:
        return []
    found = set()
    for m in PHONE_PATTERN.finditer(text):
        raw = m.group(0)
        norm = normalize_phone(raw)
        if not norm or len(norm) > 15:
            continue
        # Skip if it looks like a year or small ID
        if norm.startswith("19") or norm.startswith("20"):
            if len(norm) <= 4 or (len(norm) <= 8 and int(norm[:4]) in range(1900, 2030)):
                continue
        found.add(raw.strip())
    return list(found)[:3]


def search_contact(name: str, delay_sec: float = 2.0) -> tuple[str, str]:
    """Search the web for name + contact; return first email and first phone found."""
    email, phone = "", ""
    if not DDGS:
        return email, phone
    query = f'"{name}" email OR phone OR contact'
    try:
        with DDGS() as ddgs:
            results = list(ddgs.text(query, max_results=8))
    except Exception as e:
        print(f"  [search error for '{name}']: {e}", file=sys.stderr)
        return email, phone

    all_emails, all_phones = set(), set()
    for r in results:
        title = r.get("title") or ""
        body = r.get("body") or ""
        href = r.get("href") or ""
        combined = " ".join([title, body, href])
        for e in extract_emails(combined):
            all_emails.add(e)
        for p in extract_phones(combined):
            all_phones.add(p)

    email = list(all_emails)[0] if all_emails else ""
    phone = list(all_phones)[0] if all_phones else ""
    time.sleep(delay_sec)
    return email, phone


def main():
    script_dir = Path(__file__).resolve().parent
    input_path = script_dir.parent / "FB+Name - Sheet1.csv"
    output_path = script_dir.parent / "FB+Name+Contact - Sheet1.csv"
    limit = None  # process all rows

    # CLI: [input.csv] [output.csv] or --limit N
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if "--limit" in sys.argv:
        idx = sys.argv.index("--limit")
        if idx + 1 < len(sys.argv):
            limit = int(sys.argv[idx + 1])
    if len(args) >= 1:
        input_path = Path(args[0])
    if len(args) >= 2:
        output_path = Path(args[1])

    if not input_path.exists():
        print(f"Input CSV not found: {input_path}", file=sys.stderr)
        sys.exit(1)

    rows = []
    with open(input_path, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        fieldnames = list(reader.fieldnames or []) + ["email", "phone"]
        for row in reader:
            rows.append(row)

    if limit is not None:
        rows = rows[:limit]
    total = len(rows)
    print(f"Loaded {total} rows. Searching for email/phone (rate-limited). Output: {output_path}")

    with open(output_path, "w", newline="", encoding="utf-8") as out:
        writer = csv.DictWriter(out, fieldnames=fieldnames)
        writer.writeheader()
        for i, row in enumerate(rows):
            name = (row.get("name") or "").strip()
            fb_url = (row.get("facebook_url") or "").strip()
            if not name and not fb_url:
                writer.writerow({**row, "email": "", "phone": ""})
                continue
            display_name = name or fb_url or f"Row {i+2}"
            print(f"  [{i+1}/{total}] {display_name}")
            email, phone = search_contact(name or "unknown")
            row["email"] = email
            row["phone"] = phone
            writer.writerow(row)

    print(f"Done. Wrote {output_path}")


if __name__ == "__main__":
    main()

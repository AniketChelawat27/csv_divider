// Plus and Minus Functions with Method Chaining

function plus(num) {
    return new Calculator(num);
}

function minus(num) {
    return new Calculator(-num);
}

class Calculator {
    constructor(value) {
        this.currentValue = value;
    }
    
    plus(num) {
        this.currentValue += num;
        return this;
    }
    
    minus(num) {
        this.currentValue -= num;
        return this;
    }
    
    value() {
        return this.currentValue;
    }
}

// Test cases
console.log("Test Case 1: plus(2).plus(3).value() =", plus(2).plus(3).value()); // Should return 5
console.log("Test Case 2: plus(4).minus(2).value() =", plus(4).minus(2).value()); // Should return 2
console.log("Test Case 3: plus(5).minus(3).plus(6).minus(1).value() =", plus(5).minus(3).plus(6).minus(1).value()); // Should return 7

// Export for use in other files
module.exports = { plus, minus };
// Comprehensive Test Suite for Plus and Minus Functions

const { plus, minus } = require('./plus-minus.js');

console.log("=== Comprehensive Test Suite ===\n");

// Original test cases
console.log("Original Test Cases:");
console.log("Test Case 1: plus(2).plus(3).value() =", plus(2).plus(3).value()); // Should return 5
console.log("Test Case 2: plus(4).minus(2).value() =", plus(4).minus(2).value()); // Should return 2
console.log("Test Case 3: plus(5).minus(3).plus(6).minus(1).value() =", plus(5).minus(3).plus(6).minus(1).value()); // Should return 7

console.log("\nAdditional Test Cases:");

// Test with single values
console.log("Single value tests:");
console.log("plus(10).value() =", plus(10).value()); // Should return 10
console.log("minus(5).value() =", minus(5).value()); // Should return -5

// Test with negative numbers
console.log("\nNegative number tests:");
console.log("plus(-5).plus(3).value() =", plus(-5).plus(3).value()); // Should return -2
console.log("plus(10).minus(-3).value() =", plus(10).minus(-3).value()); // Should return 13

// Test with zero
console.log("\nZero tests:");
console.log("plus(0).plus(5).value() =", plus(0).plus(5).value()); // Should return 5
console.log("plus(5).minus(0).value() =", plus(5).minus(0).value()); // Should return 5

// Test with floating point numbers
console.log("\nFloating point tests:");
console.log("plus(2.5).plus(3.7).value() =", plus(2.5).plus(3.7).value()); // Should return 6.2
console.log("plus(10.1).minus(3.6).value() =", plus(10.1).minus(3.6).value()); // Should return 6.5

// Test longer chains
console.log("\nLonger chain tests:");
console.log("plus(1).plus(2).plus(3).plus(4).plus(5).value() =", 
    plus(1).plus(2).plus(3).plus(4).plus(5).value()); // Should return 15

console.log("plus(100).minus(20).minus(15).plus(35).minus(10).value() =", 
    plus(100).minus(20).minus(15).plus(35).minus(10).value()); // Should return 90

console.log("\n=== All Tests Complete ===");
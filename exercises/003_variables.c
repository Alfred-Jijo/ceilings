#include <stdio.h>

//
// Welcome to the world of C Data Types!
//
// Unlike Python or JavaScript, C is "statically typed." You must tell the
// compiler EXACTLY what kind of data fits in every box before you use it.
//
// C has a small set of simple types:
// - int:   Whole numbers (usually -2 billion to +2 billion)
// - float: Decimal numbers (floating point)
// - char:  A single character (like 'a', 'Z', '!')
// - long:  Like an int, but often capable of holding bigger numbers.
//
// PLEASE FIX ME:
// 1. Fill in the missing types (____) for the variables.
// 2. Fill in the missing format specifier (__) in the printf statement.
//

int main(void)
{
    // A number with a decimal point.
    float pointNumber = 8008.5;

    // A standard whole number.
    int funnyNumber = 420;

    // A really big number! 
    long long bigNumberOwO = 2147483648; 

    // Hint: 2,147,483,648 is exactly ONE higher than a standard 'int' 
    // can hold on many computers. We need a 'long' or 'long long' here.
    
    //  C uses single quotes for single characters!
    // "Strings" (double quotes) are actually arrays of chars, which we 
    // will learn about later.
    char letter = 'u';
    char letter2 = 'w';
    char letter3 = 'u';

    // You can declare variables without giving them a value yet.
    // WARNING: Until you give them a value, 'x' and 'y' contain "garbage" 
    // (whatever random bytes happened to be in that memory address).
    int x, y;
    float z, a;

    x = funnyNumber + 5;
    y = (x - 5) * 100;
    
    // If you divide two integers (5 / 2), C throws away the decimal.
    // We use '5.0' here to force C to use floating point math.
    z = pointNumber / 5.0; 
    
    // The modulo operator (%) gives us the remainder of division.
    a = bigNumberOwO % 3;
    
    // We need a format specifier to print the float. 
    // Hint: %d is for decimals(integers), %s is for strings... what is for floats?
    printf("pointNumber is: %f\n", pointNumber);

    // Wait, why does this work? 
    // In C, characters are secretly just small integers (ASCII codes).
    // 'u' is 117. So 117 + 3 = 120.
    // Try changing %i to %c to see what letter 120 represents!
    printf("new letter is: %i\n", letter + 3);

    return 0;
}

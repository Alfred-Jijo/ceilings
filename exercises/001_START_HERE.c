#include <stdio.h>

//
// Uh-oh! The compiler is confused about our main function.
//
// In C, the main function is the entry point of your program. It has a
// specific "contract" with the operating system:
// 
// 1. It returns an integer (int) to indicate success or failure.
// 2. If we aren't using command line arguments, we should explicitly 
//    say it takes "void" (nothing).
//
// PLEASE FIX ME:
// Fill in the blanks below to satisfy the contract.
//

int main(void)
{
    printf("Hello world!\n");
    return 0;
}

// ----------------------------------------------------------------------
// FOR THE CURIOUS:
//
// You might wonder: why not just write `main()`? 
//
// In modern C (C23), `()` actually implies no arguments! But in older
// versions of C (which act as the foundation for much of the world's 
// software), `()` meant "an unknown number of arguments." 
//
// Because C is picky, we use `(void)` to be 100% explicit that we 
// want absolutely zero arguments.

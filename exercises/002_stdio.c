//
// Oops! C doesn't know what "printf" means yet. 
//
// In C, standard tools like printing to the console live in the 
// "Standard Input/Output" library. We need to tell the compiler to 
// include the header file for that library.
//
// PLEASE FIX ME:
// Add the missing include directive below. 
// Hint: It looks like #include <something.h>
//

___

int main(void)
{
    printf("Hello world!\n"); 
    return 0;
}

// ----------------------------------------------------------------------
// EXPERIMENTS (Try these after you get the code to run!):
//
// 1. Newlines: Change the '\n' to '\t'. What happens to the output?
// 2. Quotes: How would you print "Hello" (with the quotes)? 
//    (Hint: You need to escape them like \")
// 3. Return codes: The `return 0` tells the OS the program finished 
//    successfully. Try changing 0 to 1, compiling, running, and then 
//    immediately typing `echo $?` in your terminal to see the error code.

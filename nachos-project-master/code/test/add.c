/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main() {
    int result1;
    int result2;
    result1 = Add(42, 23);
    result2 = Mul(9, 6);
    PrintNum(result2);
    PrintString("\n");
    Sleep(5000000);
    PrintString("I am Mokshith\n");
    
    Halt();
    /* not reached */
}
/* num_io.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a syscall that read an interger and print it
 *
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() { 

    
    // commented by me
    //PrintNum(ReadNum()); 
    // added by me
    int pid;
    int i;
    int u =100;
    PrintString("start-In Prog: num_io.c\n");
    pid = Exec2("../test/add",11);
 //  pid = Exec("../test/add");
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
        PrintNum(pid);
     }
 while(u>0)
 {
  
  for(i=0;i<1;i++);
  PrintString("In Prog: num_io.c\n");
  u--;
 }


}

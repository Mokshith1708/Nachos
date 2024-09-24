/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid;
    int i;
     PrintString("start-In Prog: exec.c\n");
    pid = Exec2("../test/num_io",100);
  //   pid = Exec("../test/num_io");
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
        PrintNum(pid);
     } //else
    //     Join(pid);

// code added by me
  while(1)
  {
     for(i=1;i<300000;i++);
     PrintString("In Prog: exec.c\n");
    
  }
}

/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid;
    int i;
    int  u = 10;
    // PrintString("start-In Prog: exec.c\n");
    pid = Exec("../test/num_io");
    Wait2(pid);
  //   pid = Exec("../test/num_io");
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
        PrintNum(pid);
     } //else
    //     Join(pid);

// code added by me

  while(u>0)
  {
     for(i=1;i<30;i++);
     PrintString("In Prog: exec.c\n");
    u--;
  }
}

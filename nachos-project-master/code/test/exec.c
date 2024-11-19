/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1
int u =100;
int main() {
     int pid=0;
     int i;
     int  u = 10;
    PrintString("start-In Prog: exec.c\n");
    // pid = 100;
     PrintNum(pid);

     pid = 5;
     pid =6;
     pid=1-0;
     pid=1-0;
     pid=1-0;
     pid=1-0;
     pid=1-0;

    PrintNum(pid);

    pid = Exec("../test/add");
    // PrintString()
    Wait2(pid);
    //pid = Exec("../test/num_io");
    PrintNum(pid);
    if (pid < 0) {
       Write("Exec failed: ", 14, stdout);
       PrintNum(pid);
    }
   //  } //else
       // Join(pid);

// code added by me

  // while(1)
  // {
  //    for(i=1;i<30000;i++);
  //    PrintString("In Prog: exec.c\n");
  //   u--;
  // }
}

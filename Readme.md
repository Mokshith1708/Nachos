# lab1
## q1) Implement Mul
### hints
    - Write the assembly language assist for userprograms in start.S (in test).
    - Define the function call example "SC_Mul" and a number to it in syscall.h (in userprog) .
    - Write the handler for mul in exception.cc (in test) and add it to switch statements.
    - Write the function definition used in exception.cc in ksyscall.h (in userprog) eg: SysMul.

## q2) Replace Hash with space
### hints
    - In ksyscall.h (in userprog) file in "SysPrintString" funcion add this line.
   

## q3) Run time process
### hints
    - In thread.h (in threads) add this line in thread class (clock_t start_time;). later in thread.cc contructor start the clock by using this syntax  (start_time = clock();).
    - Later in Syshalt function (in ksyscall.h file) add the code to stop the clock and print it. note: thread can be accessed by using kernel->currentThread. 

## q4) Implement sleep
### hints
    - in scheduler.cc (in threads) add a list for sleeping processes. neatly define the structure for sleeplist, Instantiate the list and add a function to keep process in that list.
    - In alarm.cc (in threads) in callback function add logic to remove processes from sleeplist after time is over.
    - Write all the function definitions like Mul in all the required files
    - Finally in ksyscall.h add logic so that current process which should got to sleep will not continue.
    
## q4) What type of sheduling is present in nachos
### hints
    - In one test files use Exec and call another test file then you will observe it is round robin.
    - To find how much time a process is given before change is seen write some code in alarm callback function. you will roughly get 10 microseconds.

## q5) Implement priority scheduling
### hints
    - In pcb.cc you will find Exec function copy it and make another file named Exec2 which also takes priority as parameter.
    - Add extra book keeping in thread to store priority and in Exec2 write code to give priority given in paramter to the thread priority.
    - In ptable.cc add ExecUpdate2 function by copying ExecUpdate function in that function replace Exec function with Exec2 and also add parameter.
    - In scheduler.cc change the logic in the function FindNextToRun() so that it gives the next process according to priority. Either make a new priority list and do or use the old readList.
    - Add the function call in start.S
    - Add the function number and function in syscall.h.
    - In ksyscall.h add a function SysExec2 seeing SysExec and cahnge the function call in it to ExecUpdate2(name,pri).
    - In exception.cc add the handle_SC_Exec2() here te change with respect to handle_SC_Exec() is we also need to read priority from reg5 and pass it to SysExec2().   

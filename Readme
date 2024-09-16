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
    - In alarm.cc (in threads) in callback function add logic to remove processes fomr sleeplist after time is over.
    - Write all the function definitions like Mul in all the required files
    - Finally in ksyscall.h add logic so that current process which should got to sleep doesnt continue.
    

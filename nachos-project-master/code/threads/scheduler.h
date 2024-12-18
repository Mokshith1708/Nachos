// scheduler.h
//	Data structures for the thread dispatcher and scheduler.
//	Primarily, the list of threads that are ready to run.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "copyright.h"
#include "list.h"
#include "thread.h"
 #include <queue>

// The following class defines the scheduler/dispatcher abstraction --
// the data structures and operations needed to keep track of which
// thread is running, and which threads are ready but not running.

/* code added by me starts here */
  struct sleepNode{
     Thread* process;
     int timeLeft =0;
     struct sleepNode* nextProcess;
    };
/* code added by me ends here */

class Scheduler {
   public:
    Scheduler();   // Initialize list of ready threads
    ~Scheduler();  // De-allocate ready list

    void ReadyToRun(Thread* thread);
    void ReadyToSleep(Thread* thread, int time);  /* code added by me */
    bool ReadyToWait(Thread* thread, int pid);
    void checkWait(Thread* thread);  /* code added by me */
    // Thread can be dispatched.
    Thread* FindNextToRun();  // Dequeue first thread on the ready
                              // list, if any, and return thread.
    void Run(Thread* nextThread, bool finishing);
    // Cause nextThread to start running
    void CheckToBeDestroyed();  // Check if thread that had been
                                // running needs to be deleted
    void Print();               // Print contents of ready list

    struct sleepNode* sleepList; /* code added by me */
     List<Thread*>* waitList; /* code added by me*/
    // SelfTest for scheduler is implemented in class Thread
    struct CompareThreads {
    bool operator()(Thread* thread1, Thread* thread2) {
        // For max-heap: return true if thread1 should go after thread2
        return thread1->pri > thread2->pri;
    }
    };
    priority_queue<Thread *, vector<Thread *>,CompareThreads> priorityList;
    

   private:
    List<Thread*>* readyList;  // queue of threads that are ready to run,
                               // but not running
    Thread* toBeDestroyed;     // finishing thread to be destroyed
                               // by the next thread that runs
   
 
};

#endif  // SCHEDULER_H

// scheduler.cc
//	Routines to choose the next thread to run, and to dispatch to
//	that thread.
//
// 	These routines assume that interrupts are already disabled.
//	If interrupts are disabled, we can assume mutual exclusion
//	(since we are on a uniprocessor).
//
// 	NOTE: We can't use Locks to provide mutual exclusion here, since
// 	if we needed to wait for a lock, and the lock was busy, we would
//	end up calling FindNextToRun(), and that would put us in an
//	infinite loop.
//
// 	Very simple implementation -- no priorities, straight FIFO.
//	Might need to be improved in later assignments.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "debug.h"
#include "scheduler.h"
#include "main.h"


//----------------------------------------------------------------------
// Scheduler::Scheduler
// 	Initialize the list of ready but not running threads.
//	Initially, no ready threads.
//----------------------------------------------------------------------

Scheduler::Scheduler() {
    readyList = new List<Thread *>;
    waitList = new List<Thread *>;/* code added by me*/
    sleepList = new sleepNode(); /* code added by me*/
    toBeDestroyed = NULL;
}

//----------------------------------------------------------------------
// Scheduler::~Scheduler
// 	De-allocate the list of ready threads.
//----------------------------------------------------------------------

Scheduler::~Scheduler() { delete readyList; }

//----------------------------------------------------------------------
// Scheduler::ReadyToRun
// 	Mark a thread as ready, but not running.
//	Put it on the ready list, for later scheduling onto the CPU.
//
//	"thread" is the thread to be put on the ready list.
//----------------------------------------------------------------------

void Scheduler::ReadyToRun(Thread *thread) {
    ASSERT(kernel->interrupt->getLevel() == IntOff);
    DEBUG(dbgThread, "Putting thread on ready list: " << thread->getName());

    thread->setStatus(READY);
    readyList->Append(thread);
   // priorityList.push(thread);
}

/* code added by me starts here */
void Scheduler::ReadyToSleep(Thread *thread,int time)
{

     // ASSERT(kernel->interrupt->getLevel() == IntOff);
       DEBUG(dbgThread, "Putting thread on sleep list: " << thread->getName());
       struct sleepNode* sleepProcess = new sleepNode();
       sleepProcess->nextProcess = sleepList;
       sleepProcess->process = thread;
       sleepProcess->timeLeft = time;
       sleepList = sleepProcess;
      // timeLeft = time;
}
/* code added by me ends here */

/* code added by me starts here */
 bool Scheduler::ReadyToWait(Thread* thread, int pid)
 {  
    if(kernel->pTab->IsExist(pid))
    {
    thread->waitID = pid;
    waitList->Append(thread);
    return true;
    }
   return false;

 }
/* code added by me ends here */
// code added by me starts here
void Scheduler::checkWait(Thread* thread)
{  //   printf("i am in checkwait start\n");
     ListIterator<Thread *> *itr = new ListIterator<Thread *>(waitList);
      Thread *c=nullptr;
      List<Thread *> *empty = new List<Thread *>();
      int max = 100;
      while(!itr->IsDone())
      {
        c = itr->Item();
       //printf("i am in checkwait\n");
        if(thread->processID == c->waitID)
        {
            cout << "Adding " << c->processID << endl;   
            kernel->scheduler->ReadyToRun(c);
        //    printf("i am in checkwait\n");
            empty->Append(c);
        }
        itr->Next();
      }

      delete itr;
      itr = new ListIterator<Thread *>(empty);

      while(!itr->IsDone())
      {  
        cout<<itr->Item()<<" "<<endl;
        waitList->Remove(itr->Item());
        itr->Next();
      }
       printf("i am in checkwait start\n");
     ListIterator<Thread *> *itr1 = new ListIterator<Thread *>(readyList);
      while(!itr1->IsDone())
      {
        c = itr1->Item();
        cout<<c->processID<<endl;
       //printf("i am in checkwait\n");
        // if(thread->processID == c->waitID)
        // {   
        //   //  kernel->scheduler->ReadyToRun(c);
        // //    printf("i am in checkwait\n");
        //   //  empty->Append(c);
        // }
        itr1->Next();
      }
}

// code added by me ends here.


//----------------------------------------------------------------------
// Scheduler::FindNextToRun
// 	Return the next thread to be scheduled onto the CPU.
//	If there are no ready threads, return NULL.
// Side effect:
//	Thread is removed from the ready list.
//----------------------------------------------------------------------

Thread *Scheduler::FindNextToRun() {
    ASSERT(kernel->interrupt->getLevel() == IntOff);

    if (readyList->IsEmpty()) {
        return NULL;
    } else {
         // code added by me starts here
    //   ListIterator<Thread *> *itr = new ListIterator<Thread *>(readyList);
    //   Thread *c=nullptr, *c1=nullptr;
    //   int max = 100;
    //   while(!itr->IsDone())
    //   {
    //     c = itr->Item();
    //     if(max>c->pri)
    //     {
    //         max = c->pri;
    //         c1 = c;
    //     }
    //     itr->Next();
    //   }

    //   delete itr;
    
    //   readyList->Remove(c1);
    //   return c1;
      // code added by me ends here
     return readyList->RemoveFront();

    // Thread *c1;
    // c1 = priorityList.top();
    // priorityList.pop();
    // readyList->Remove(c1);
    //   return c1;

    
    }
}

//----------------------------------------------------------------------
// Scheduler::Run
// 	Dispatch the CPU to nextThread.  Save the state of the old thread,
//	and load the state of the new thread, by calling the machine
//	dependent context switch routine, SWITCH.
//
//      Note: we assume the state of the previously running thread has
//	already been changed from running to blocked or ready (depending).
// Side effect:
//	The global variable kernel->currentThread becomes nextThread.
//
//	"nextThread" is the thread to be put into the CPU.
//	"finishing" is set if the current thread is to be deleted
//		once we're no longer running on its stack
//		(when the next thread starts running)
//----------------------------------------------------------------------

void Scheduler::Run(Thread *nextThread, bool finishing) {
    Thread *oldThread = kernel->currentThread;

    ASSERT(kernel->interrupt->getLevel() == IntOff);

    if (finishing) {  // mark that we need to delete current thread
        ASSERT(toBeDestroyed == NULL);
        toBeDestroyed = oldThread;
    }

    if (oldThread->space != NULL) {  // if this thread is a user program,
        oldThread->SaveUserState();  // save the user's CPU registers
        oldThread->space->SaveState();
    }

    oldThread->CheckOverflow();  // check if the old thread
                                 // had an undetected stack overflow

    kernel->currentThread = nextThread;  // switch to the next thread
    nextThread->setStatus(RUNNING);      // nextThread is now running

    DEBUG(dbgThread, "Switching from: " << oldThread->getName()
                                        << " to: " << nextThread->getName());

    // This is a machine-dependent assembly language routine defined
    // in switch.s.  You may have to think
    // a bit to figure out what happens after this, both from the point
    // of view of the thread and from the perspective of the "outside world".

    SWITCH(oldThread, nextThread);

    // we're back, running oldThread

    // interrupts are off when we return from switch!
    ASSERT(kernel->interrupt->getLevel() == IntOff);

    DEBUG(dbgThread, "Now in thread: " << oldThread->getName());

    CheckToBeDestroyed();  // check if thread we were running
                           // before this one has finished
                           // and needs to be cleaned up

    if (oldThread->space != NULL) {     // if there is an address space
        oldThread->RestoreUserState();  // to restore, do it.
        oldThread->space->RestoreState();
    }
}

//----------------------------------------------------------------------
// Scheduler::CheckToBeDestroyed
// 	If the old thread gave up the processor because it was finishing,
// 	we need to delete its carcass.  Note we cannot delete the thread
// 	before now (for example, in Thread::Finish()), because up to this
// 	point, we were still running on the old thread's stack!
//----------------------------------------------------------------------

void Scheduler::CheckToBeDestroyed() {
    if (toBeDestroyed != NULL) {
        delete toBeDestroyed;
        toBeDestroyed = NULL;
    }
}

//----------------------------------------------------------------------
// Scheduler::Print
// 	Print the scheduler state -- in other words, the contents of
//	the ready list.  For debugging.
//----------------------------------------------------------------------
void Scheduler::Print() {
    cout << "Ready list contents:\n";
    readyList->Apply(ThreadPrint);
    printf("\nWaitlist:");
    waitList->Apply(ThreadPrint);
    printf("\n");
}

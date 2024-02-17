#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100
//converted HZ to microseconds
#define TIMER (1000000/ HZ);

// initialized sigaction structs
struct sigaction signal_action;
struct sigaction previous_signal_action;

// initialized timer structs
struct itimerval previous_timer;
struct itimerval current_timer;

bool preemptStatus = 0;

/*a signal handler that receives alarm signals.
If it receives SIGVTALRM, then the uthread would yield.	*/
void signal_handler(int sigNum)
{
	if (sigNum == SIGVTALRM){
		uthread_yield();
	}
}

// preemption is disabled by blocking the SIGVTALRMN
void preempt_disable(void)
{

	if(preemptStatus){
		sigset_t sigSet;
		sigemptyset(&sigSet);
		sigaddset(&sigSet, SIGVTALRM);
		sigprocmask(SIG_BLOCK, &sigSet, NULL);
	}
	

}

// preemption is enabled through unblocking the SIGVTALRM
void preempt_enable(void)
{
	if(preemptStatus){
		sigset_t sigSet;
		sigemptyset(&sigSet);
		sigaddset(&sigSet, SIGVTALRM);
		sigprocmask(SIG_UNBLOCK, &sigSet, NULL);
	}
}

void preempt_start(bool preempt)
{
	// initializes the preempt status
	preemptStatus = preempt;

	// if the preempt status is false, then preemption is not started
	if(preemptStatus){
		// sets up the signal handler
		signal_action.sa_handler = signal_handler;
		sigemptyset(&signal_action.sa_mask);
		signal_action.sa_flags = 0;
		sigaction(SIGVTALRM, &signal_action, &previous_signal_action);

		// set the timer for alarm
		current_timer.it_interval.tv_sec = 0;
		current_timer.it_interval.tv_usec = TIMER;
		current_timer.it_value.tv_sec = 0;
		current_timer.it_value.tv_usec = TIMER;

		setitimer(ITIMER_VIRTUAL, &current_timer, &previous_timer);
		 
	}
}

void preempt_stop(void)
{
	// restores the timer and signal action back to the previous state
	if(preemptStatus){
		sigaction(SIGVTALRM, &previous_signal_action, NULL);
		setitimer(ITIMER_VIRTUAL, &previous_timer, NULL);
	}
}


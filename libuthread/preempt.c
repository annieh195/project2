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
#define FREQUENCY (HZ*100)

struct sigaction signal_action;
struct sigaction previous_signal_action;

struct itimerval previous_timer;
struct itimerval current_timer;

bool preemptStatus = 0;

void signal_handler(int sigNum)
{
	if (sigNum == SIGVTALRM){
		uthread_yield();
	}
}

void preempt_disable(void)
{
	/* TODO Phase 4 */
	if(preemptStatus){
		sigset_t sigSet;
		sigemptyset(&sigSet);
		sigaddset(&sigSet, SIGVTALRM);
		sigprocmask(SIG_BLOCK, &sigSet, NULL);
	}
	

}

void preempt_enable(void)
{
	/* TODO Phase 4 */
	if(preemptStatus){
		sigset_t sigSet;
		sigemptyset(&sigSet);
		sigaddset(&sigSet, SIGVTALRM);
		sigprocmask(SIG_UNBLOCK, &sigSet, NULL);
	}
}

void preempt_start(bool preempt)
{
	/* TODO Phase 4 */
	preemptStatus = preempt;
	if(preemptStatus){
		signal_action.sa_handler = signal_handler;
		sigemptyset(&signal_action.sa_mask);
		signal_action.sa_flags = 0;
		sigaction(SIGVTALRM, &signal_action, &previous_signal_action);

		//set the timer for alarm
		current_timer.it_interval.tv_sec = 0;
		current_timer.it_interval.tv_usec = FREQUENCY;
		current_timer.it_value.tv_sec = 0;
		current_timer.it_value.tv_usec = FREQUENCY;

		setitimer(ITIMER_REAL, &current_timer, &previous_timer);
		 
	}
}

void preempt_stop(void)
{
	/* TODO Phase 4 */

	if(preemptStatus){
		sigaction(SIGVTALRM, &previous_signal_action, NULL);
		setitimer(ITIMER_REAL, &previous_timer, NULL);
	}
}


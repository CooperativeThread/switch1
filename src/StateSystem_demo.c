/*
 ============================================================================
 Name        : StateSystem.c
 Author      : f
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "StateSystem.h"
TaskThread_t  TaskThread[MaximumTask];

int Task1(void *d,TaskThread_t  *pts)
{
  	TaskStart(pts);
	while(1) {
     printf("Task1");
     TaskDelayMs(pts,5000,SIGN);
	}
	TaskStop(pts);
	return 0;
}
int Task2(void *d,TaskThread_t  *pts)
{
  	TaskStart(pts);
	while(1) {
     printf("Task2");
     TaskSetTimer(pts,5000);
     TaskSleep(pts, pts->task_timer==0,SIGN);
	}
	TaskStop(pts);
	return 0;
}
int main(void) {
	puts("Hello World"); /* prints Hello World */
	char k[1];
	while(1)
	{
		Task1(k,&TaskThread[0]);
		Task2(k,&TaskThread[1]);
		TaskVxdTimer();
	}
	return EXIT_SUCCESS;
}

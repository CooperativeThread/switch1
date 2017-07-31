

#ifndef __StateSystem_H__
#define __StateSystem_H__
#define SIGN __LINE__
#define MaximumTask    10
typedef struct TaskThread {
  unsigned short task_state;
  unsigned long  task_timer;
}TaskThread_t;
extern TaskThread_t  TaskThread[MaximumTask];
#define TASK_WAITING 0
#define TASK_YIELDED 1
#define TASK_EXITED  2
#define TASK_ENDED   3

#define TASK_DEFAULT(task_state) task_state = 0;
#define TASK_RESUME(task_state) switch(task_state) { case 0:
#define TASK_SET(task_state,const_sign) task_state = const_sign; case const_sign:
#define TASK_END(task_state) }

#define TaskSystemReg(Task)   TASK_DEFAULT((Task)->task_state)
#define TaskStart(Task) { TASK_RESUME((Task)->task_state)
#define TaskStop(Task) TASK_END((Task)->task_state);  \
                       TaskSystemReg(Task); \
					   return TASK_ENDED; }
#define TaskSleep(Task, condition,const_sign)	        \
  do {						\
    TASK_SET((Task)->task_state,const_sign);				\
    if(!(condition)) {				\
      return TASK_WAITING;			\
    }						\
  } while(0)
#define TaskReset(Task)				\
  do {						\
    TaskSystemReg(Task);				\
    return TASK_WAITING;			\
  } while(0)
#define TaskExit(Task)				\
  do {						\
    TaskSystemReg(Task);				\
    return TASK_EXITED;			\
  } while(0)
#define TaskSetTimer(Timer,TimerN)  \
  do{               \
	 Timer->task_timer=TimerN;  \
  }while(0)
#define TaskVxdTimer() \
	do{   \
	  for(int i=0;i<MaximumTask;i++) \
	  { \
	  if(TaskThread[i].task_timer>0) \
	  { \
	    TaskThread[i].task_timer--; \
	  } \
	  } \
	}while(0)
#define TaskDelayMs(Task,timer,const_sign) \
	do {     \
		 TaskSetTimer(Task,timer);      \
         TaskSleep(Task, Task->task_timer==0,const_sign); \
	}while(0)
	

	
#endif 



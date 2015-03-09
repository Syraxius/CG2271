#include <kernel.h>
#include <mutex.h>
#include <queue.h>
#include <sema.h>
// Data structure for the barrier.
typedef struct OSBarrier
{
  int count;
  OSSema sema;
};
// Creates a new barrier.
// Parameters: count = # of tasks expected to reach the barrier
// barrier = pointer to barrier data structure
void OSCreateBarrier(unsigned int count, struct OSBarrier *barrier)
{
  // TO DO: IMPLEMENT THE CREATE BARRIER FUNCTION
  barrier->count = count;
  OSCreateSema(&barrier->sema,0,1);
}
// Informs barrier that tasks has reached it. barrier = pointer to
// barrier data structure
void OSReachBarrier(struct OSBarrier *barrier)
{
  // TO DO: IMPLEMENT REACH BARRIER
  if (--barrier->count) {
    OSTakeSema(&barrier->sema);
  }
  if (procPeek(&barrier->sema.taskQ) != 255) {
    OSGiveSema(&barrier->sema);
  }
}
// DO NOT MODIFY ANYTHING BELOW THIS LINE
#define QLEN 8
int crossedBuffer[QLEN];
int reachedBuffer[QLEN];
OSQueue crossedQueue;
OSQueue reachedQueue;
struct OSBarrier barrier;
void task1(void *p)
{
  char crossed=0;
  while(1)
  {
    if(!crossed)
    {
      OSSleep(250);
      OSEnqueue(1, &reachedQueue);
      OSReachBarrier(&barrier);
      OSEnqueue(1, &crossedQueue);
      crossed=1;
    }
    else
      OSSleep(100);
  }
}
void task2(void *p)
{
  char crossed=0;
  while(1)
  {
    if(!crossed)
    {
      OSSleep(195);
      OSEnqueue(2, &reachedQueue);
      OSReachBarrier(&barrier);
      OSEnqueue(2, &crossedQueue);
      crossed=1;
    }
    else
      OSSleep(100);
  }
}
void task3(void *p)
{
  char crossed=0;
  while(1)
  {
    if(!crossed)
    {
      OSSleep(850);
      OSEnqueue(3, &reachedQueue);
      OSReachBarrier(&barrier);
      OSEnqueue(3, &crossedQueue);
      crossed=1;
    }
    else
      OSSleep(100);
  }
}
void reachTask(void *p)
{
  while(1)
  {
    unsigned pnum=OSDequeue(&reachedQueue);
    Serial.print(pnum);
    Serial.println(" has reached the barrier");
    OSSleep(50);
  }
}
void crossTask(void *p)
{
  while(1)
  {
    unsigned pnum=OSDequeue(&crossedQueue);
    Serial.print(pnum);
    Serial.println(" has crossed the barrier");
    OSSleep(50);
  }
}
void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("------ NEW RUN -----");
  Serial.println();
  OSInit(5);
  OSCreateBarrier(3, &barrier);
  OSCreateQueue(crossedBuffer, QLEN, &crossedQueue);
  OSCreateQueue(reachedBuffer, QLEN, &reachedQueue);
  OSCreateTask(4, task1, NULL);
  OSCreateTask(2, task2, NULL);
  OSCreateTask(3, task3, NULL);
  OSCreateTask(0, reachTask, NULL);
  OSCreateTask(1, crossTask, NULL);
  OSRun();
}
void loop()
{
}



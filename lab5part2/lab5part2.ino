#include <kernel.h>
#include <mutex.h>
#include <queue.h>
#include <sema.h>
#define QLEN 64
int buffer[QLEN];
OSQueue queue;
void serialPrint(void *p)
{
  int x;
  while(1)
  {
    x=OSDequeue(&queue);
    Serial.print("Task ");
    Serial.println(x);
    OSSleep(80);
  }
}
void task1and2(void *p)
{
  int taskNum=(int) p;
  while(1)
  {
    OSEnqueue(taskNum, &queue);
    OSSleep(100);
  }
}
void setup()
{
  Serial.begin(9600);
  OSInit(3);
  OSCreateQueue(buffer, QLEN, &queue);
  OSCreateTask(0, serialPrint, NULL);
  OSCreateTask(1, task1and2, (void *) 1);
  OSCreateTask(2, task1and2, (void *) 2);
  OSRun();
}
void loop()
{
}



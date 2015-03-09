#include <kernel.h>
#include <mutex.h>
#include <queue.h>
#include <sema.h>

void task1and2(void *p)
{
  while(1)
  {
    int taskNum=(int) p;
    Serial.print("Hello there! I am task #");
    Serial.println(taskNum);
    OSSleep(30);
  }
}

void setup()
{
  Serial.begin(9600);
  OSInit(2);
  OSCreateTask(0, task1and2, (void *) 1);
  //OSCreateTask(1, task1and2, (void *) 2);
  OSRun();
}

void loop()
{
}


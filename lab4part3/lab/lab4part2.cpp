/*
 * lab4part1.cpp
 *
 * Created: 3/3/2015 10:50:57 AM
 *  Author: Kelvin
 */ 

#include <avr/io.h>
#include <Arduino.h>
#include "kernel.h"
#include "sema.h"
OSSema task1Go, task2Go;
void task1(void *param)
{
	while(1)
	{
		// Wait for task1Go
		OSTakeSema(&task1Go);
		for(int i=0; i<5; i++)
		{
			digitalWrite(6, HIGH);
			OSSleep(250);
			digitalWrite(6, LOW);
			OSSleep(250);
		}
		// Release task 2
		OSGiveSema(&task2Go);
	}
}
void task2(void *param)
{
	while(1)
	{
		// Wait on task2Go
		OSTakeSema(&task2Go);
		for(int i=0; i<2; i++)
		{
			digitalWrite(7, HIGH);
			OSSleep(500);
			digitalWrite(7, LOW);
			OSSleep(500);
		}
		// Release task1Go
		OSGiveSema(&task1Go);
	}
}
void setup()
{
	// Set pins 6 and 7 as output
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	// Initialize the OS
	OSInit(2);
	// Create the binary semaphores
	// Set task1Go to initial value of 1 so that Task1 can run
	OSCreateSema(&task1Go, 1, 1);
	OSCreateSema(&task2Go, 0, 1);
	// Add in the tasks
	OSCreateTask(0, task1, NULL);
	OSCreateTask(1, task2, NULL);
	// Launch the OS
	OSRun();
}
void loop()
{
	// Empty
}
int main()
{
	init();
	setup();
	while(1)
	{
		loop();
		if(serialEventRun)
		serialEventRun();
	}
}
/*
 * lab4part1.cpp
 *
 * Created: 3/3/2015 10:50:57 AM
 *  Author: Kelvin
 */ 

#include <avr/io.h>
#include <Arduino.h>
#include "kernel.h"

#define NUMTASKS 2 // Number of tasks to create.

void task1(void *arg)
{
	// 5Hz = 200ms cycle time. Hence each half is 100ms
	while(1)
	{
		digitalWrite(6, HIGH);
		OSSleep(100);
		digitalWrite(6, LOW);
		OSSleep(100);
	}
}

void task2(void *arg)
{
	while(1)
	{
		// 1HZ = 1000ms cycle time. Each half is 500ms
		digitalWrite(7, HIGH);
		OSSleep(500);
		digitalWrite(7, LOW);
		OSSleep(500);
	}
}

void setup()
{
	// Set pins 6 and 7 as output
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	// Initialize the OS
	OSInit(NUMTASKS);
	// Add in the tasks
	OSCreateTask(0, task1, NULL);
	OSCreateTask(1, task2, NULL);
	// Start execution
	OSRun();
}

void loop()
{
	// Empty
}

// Do not modify this section!
int main(void)
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
/*
 * lab4part3.cpp
 *
 * Created: 4/10/2013 6:19:58 PM
 *  Author: dcstanc
 */ 


#include <avr/io.h>
#include <Arduino.h>
#include "kernel.h"
#include "sema.h"

OSSema pin6sema, pin7sema;

// Do switch debouncing
unsigned long int0time=0, int1time=0;

// Debouncing function. Returns TRUE if this interrupt was not caused by a bouncing switch
int debounce(unsigned long *debTimer)
{
	unsigned long tmp=*debTimer;
	unsigned long currTime=OSticks();
	
	if((currTime-tmp) > 500)
	{
		*debTimer=currTime;
		return 1;
	}
	else
	return 0;
	
}

void flashPin6(void *param) {
	while (1) {
		OSTakeSema(&pin6sema);
		for (int i=0; i<5; i++) {
			digitalWrite(6,HIGH);
			OSSleep(250);
			digitalWrite(6,LOW);
			OSSleep(250);
		}
	}
}

void flashPin7(void *param) {
	while (1) {
		OSTakeSema(&pin7sema);
		for (int i=0; i<5; i++) {
			digitalWrite(7,HIGH);
			OSSleep(250);
			digitalWrite(7,LOW);
			OSSleep(250);
		}
	}
}

void int0isr() {
	if (debounce(&int0time)) {
		OSGiveSema(&pin6sema);
	}
}

void int1isr() {
	if (debounce(&int1time)) {
		OSGiveSema(&pin7sema);
	}
}

void setup()
{
	OSInit(2);
	attachInterrupt(0, int0isr, FALLING);
	attachInterrupt(1, int1isr, FALLING);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	OSCreateSema(&pin6sema, 0, 0);
	OSCreateSema(&pin7sema, 0, 0);
	OSCreateTask(0,flashPin6,NULL);
	OSCreateTask(1,flashPin7,NULL);
	OSRun();
}

void loop()
{
	// Empty
}

// Do not modify
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
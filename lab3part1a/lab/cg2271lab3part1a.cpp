/*
* cg2271lab3part1a.cpp
*
* Created: 12/9/2013 8:39:35 AM
* Author: dcstanc
*/

#include <avr/io.h>
#include <Arduino.h>
#include "prioq.h"
#define QLEN 10

TPrioQueue *queue;

void setup() {
	// Set up the queue.
	queue=makeQueue();
	// Initialize the serial port
	Serial.begin(9600);
	// Now enqueue 10 numbers in reverse priority
	for(int i=0; i<QLEN; i++) {
		enq(queue, (void *)i, QLEN-i-1);
	}
}

void loop() {
	int val;
	// If we still have an item to dequeue
	if(qlen(queue)>0) {
		// Dequeue it
		val=(int) deq(queue);
		// And print it on the serial port.
		Serial.println(val);
	}
	//500ms pause
	delay(500);
}

// Main has been set up to work correctly with the Arduino libraries.
// Do not modify.
int main(void) {
	init();
	setup();
	while(1) {
		loop();
		if(serialEventRun)
		serialEventRun();
	}
}
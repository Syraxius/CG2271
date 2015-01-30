/*
 * blinky.cpp
 *
 * Created: 1/28/2015 11:35:39 AM
 *  Author: Kelvin
 */ 

#include <avr/io.h>
#include <Arduino.h>
#define YELLOW_PIN 12
#define RED_PIN 13

void setup();
void blinky();
void blinkLed(unsigned pinNum);
void update();

int main(void) {
	while(1) {
		init();
		setup();
		blinky();
	}
}

void setup() {
	pinMode(YELLOW_PIN, OUTPUT);
	pinMode(RED_PIN, OUTPUT);
}

void blinky() {
	blinkLed(RED_PIN);
	update();
	blinkLed(YELLOW_PIN);
}

void blinkLed(unsigned pinNum) {
	digitalWrite(pinNum, HIGH);
	delay(1000);
	digitalWrite(pinNum, LOW);
	delay(1000);
}

void update() {
	static int x = 0;
	x = x + 1;
}
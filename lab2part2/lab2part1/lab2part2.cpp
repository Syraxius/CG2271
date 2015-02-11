/*
* lab2part2.cpp
*
* Created: 4/2/2014 12:00:00 PM
* Author: Kelvin
*/

#include <avr/io.h>
#include <Arduino.h>

#define polledPin 2
#define analogOut 6
#define analogChannel 0

static int val = 0;
static int valRemapped = 0;
static int touch = 0;
static int touchRemapped = 125;

void setup() {
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(7, OUTPUT);
	Serial.begin(9600);
}

void flashPin7(int delayVal) {
	digitalWrite(7, HIGH);
	delay(delayVal);
	digitalWrite(7, LOW);
	delay(delayVal);
}

int remap(int val) {
	return val * (int)(255.0 / 1023.0);
}

int remapTouch(int touch) {
	return 125 + (int)(touch * 375.0 / 1023.0);
}

void readPotentiometer() {
	val=analogRead(0);
	valRemapped = remap(val);
}

void readTouch() {
	touch=analogRead(1);
	touchRemapped = remapTouch(touch);
}

void outputBrightness() {
	analogWrite(6, valRemapped);
}

void outputBlink() {
	flashPin7(touchRemapped);
}

void outputSerial() {
	Serial.print(val);
	Serial.print(" ");
	Serial.print(valRemapped);
	Serial.print(" ");
	Serial.print(touch);
	Serial.println();
	Serial.print(touchRemapped);
	Serial.println();
}

void loop() {
	while(1) {		
		if (digitalRead(2)) {
			readPotentiometer();
		}
		
		outputBrightness();
		
		if (digitalRead(3)) {
			readTouch();
		}
		
		outputBlink();
		
		outputSerial();
	}
}

int main(void) {
	init();
	setup();
	while(1) {
		loop();
		if(serialEventRun)
			serialEventRun();
	}
	return 0;
}
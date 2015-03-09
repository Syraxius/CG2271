/*
* lab.cpp
*
* Created: 4/2/2014 12:00:00 PM
* Author: Kelvin
*/

#include <avr/io.h>
#include <Arduino.h>

#define polledPin 2
#define analogOut 6
#define analogChannel 0

void setup() {
	pinMode(2, INPUT);
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
	return (int)(val*255.0/1023.0);
}

int remapTouch(int touch) {
	return 125 + (int)(touch*375.0/1023.0);
}

void loop() {
	int val=analogRead(0);
	int valRemapped = remap(val);
	int touch=analogRead(1);
	int touchRemapped = remapTouch(touch);
	
	Serial.print(val);
	Serial.print(" ");
	Serial.print(valRemapped);
	Serial.print(" ");
	Serial.print(touch);
	Serial.print(" ");
	Serial.print(touchRemapped);
	Serial.println();
	
	analogWrite(6, valRemapped);
	flashPin7(touchRemapped);
}

// Note: Do not modify main. It has been written to work correctly with
// the Arduino library. Modify only setup() and loop(), though you may
// add new functions.
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
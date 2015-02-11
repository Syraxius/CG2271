#include <Arduino.h>

static long fastLoopTimer = millis();
static int slowLoopCounter = 0;

void togglePin6()
{
	static char state=1;
	
	if(state)
	digitalWrite(6, HIGH);
	else
	digitalWrite(6, LOW);
	
	state=!state;
}


void togglePin7()
{
	static char state=1;
	
	if(state)
	digitalWrite(7, HIGH);
	else
	digitalWrite(7, LOW);
	
	state=!state;
}

void setup()
{
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
}

void fastLoop()
{
	togglePin6();
}

void slowLoop()
{
	if (slowLoopCounter == 4) {
		togglePin7();
		slowLoopCounter = 0;
	} else {
		slowLoopCounter++;
	}
}

void loop()
{
	if (millis() - fastLoopTimer > 99) {
		fastLoopTimer = millis();
		fastLoop();
		slowLoop();
	}	
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
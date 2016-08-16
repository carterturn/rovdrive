#pragma once

#include "gpiopin.h"

class motor{
public:
	motor(short enablePin, short forwardPin, short reversePin);
	~motor();

	void init();
	void cleanup();

	void run(short dir);
private:
	gpiopin * enable;
	gpiopin * forward;
	gpiopin * reverse;
};

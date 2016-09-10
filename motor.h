#pragma once

#include "watchdog.h"

class motor{
public:
	motor(short enable_pin, short forward_pin, short reverse_pin, bool safe = true);

	void init();
	void cleanup();

	void run(short direction);
	void enable();
	void disable();
	void stop();
private:
	watchdog * dog;

	void setup_pin(short pin);
	void cleanup_pin(short pin);
	void write_pin(short pin, short value);
	
	short enable_pin;
	short forward_pin;
	short reverse_pin;
};

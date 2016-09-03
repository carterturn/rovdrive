#pragma once

#include <thread>

class watchdog {

public:
	watchdog(void (*kill_function)());
	~watchdog();
	
	int start();

	int kick(int time);

	int end();

protected:

	std::thread watcher;
	bool watching;

	int counter;

	void (*kill_function)();

	void run();
};

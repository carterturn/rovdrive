#include "watchdog.h"

#include <unistd.h>

watchdog::watchdog(void (*kill_function)()) : kill_function(kill_function) {}
watchdog::~watchdog(){
	end();
}

int watchdog::start(){
	watcher = std::thread(&watchdog::run, this);
	watching = true;
	
	return 0;
}

int watchdog::kick(int time){
	counter = time;

	return 0;
}

int watchdog::end(){
	watching = false;
	watcher.join();

	return 0;
}

void watchdog::run(){
	while(watching){
		counter--;
		usleep(1000);

		if(counter <= 0){
			kill_function();
		}
	}
}

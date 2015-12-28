#include "ct_time.h"

#include <time.h>

void cusleep(int usec){
	timespec ts1, ts2;
	if(usec > 1000000){
		ts1.tv_sec = (int) usec/1000000;
		usec = usec - ts1.tv_sec*1000000;
	}
	ts1.tv_nsec = usec*1000;
	nanosleep(&ts1, &ts2);
}

void csleep(int sec){
	timespec ts1, ts2;
	ts1.tv_sec = sec;
	ts1.tv_nsec = 0;
	nanosleep(&ts1, &ts2);
}

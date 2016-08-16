#include "motor.h"

motor::motor(short enablePin, short forwardPin, short reversePin){
	enable = new gpiopin(enablePin);
	forward = new gpiopin(forwardPin);
	reverse = new gpiopin(reversePin);
}

motor::~motor(){
	delete enable;
	delete forward;
	delete reverse;
}

void motor::init(){
	enable->exportpin();
	forward->exportpin();
	reverse->exportpin();
	enable->setmode(GPIO_WRITE_MODE);
	forward->setmode(GPIO_WRITE_MODE);
	reverse->setmode(GPIO_WRITE_MODE);
	enable->write(0);
	forward->write(0);
	reverse->write(0);
}

void motor::cleanup(){
	enable->unexport();
	forward->unexport();
	reverse->unexport();
}

void motor::run(short dir){
	switch(dir){
	case 1:
		enable->write(1);
		forward->write(1);
		reverse->write(0);
		return;
	case -1:
		enable->write(1);
		forward->write(0);
		reverse->write(1);
		return;
	case 0:
	default:
		enable->write(0);
		forward->write(0);
		reverse->write(0);
		return;
	}
}

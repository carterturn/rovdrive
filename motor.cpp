#include "motor.h"

motor::motor(short forwardPin, short reversePin){
	forward = new gpiopin(forwardPin);
	reverse = new gpiopin(reversePin);
}

motor::~motor(){
	delete forward;
	delete reverse;
}

void motor::init(){
	forward->exportpin();
	reverse->exportpin();
	forward->setmode(GPIO_WRITE_MODE);
	reverse->setmode(GPIO_WRITE_MODE);
	forward->write(0);
	reverse->write(0);
}

void motor::cleanup(){
	forward->unexport();
	reverse->unexport();
}

void motor::run(short dir){
	switch(dir){
	case 1:
		forward->write(1);
		reverse->write(0);
		return;
	case -1:
		forward->write(0);
		reverse->write(1);
		return;
	case 0:
	default:
		forward->write(0);
		reverse->write(0);
		return;
	}
}

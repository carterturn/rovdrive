#include "motor.h"

#include <sstream>
#include <fstream>
#include <unistd.h>

using namespace std;

motor::motor(short enable_pin, short forward_pin, short reverse_pin)
	: enable_pin{enable_pin}, forward_pin(forward_pin), reverse_pin(reverse_pin) {}

void motor::setup_pin(short pin){
	for(short i = 0; i < 2; i++){ // Needs to be done twice (not sure why)
		ofstream export_file("/sys/class/gpio/export");
		export_file << pin;
		export_file.close();

		stringstream direction_file_name;
		direction_file_name << "/sys/class/gpio/gpio" << pin << "/direction";

		ofstream direction_file(direction_file_name.str().c_str());
		direction_file << "out";
		direction_file.close();

		usleep(1000000);
	}
}

void motor::cleanup_pin(short pin){
	ofstream unexportFile("/sys/class/gpio/unexport");
	unexportFile << pin;
	unexportFile.close();
}

void motor::write_pin(short pin, short value){
	stringstream value_file_name;
	value_file_name << "/sys/class/gpio/gpio" << pin << "/value";
	
	ofstream value_file(value_file_name.str().c_str());
	value_file << value;
	value_file.close();
}

void motor::init(){
	setup_pin(enable_pin);
	setup_pin(forward_pin);
	setup_pin(reverse_pin);
	disable();
	run(0);
}

void motor::cleanup(){
	cleanup_pin(enable_pin);
	cleanup_pin(forward_pin);
	cleanup_pin(reverse_pin);
}

void motor::run(short direction){
	switch(direction){
	case 1:
		write_pin(forward_pin, 1);
		write_pin(reverse_pin, 0);
		return;
	case -1:
		write_pin(forward_pin, 0);
		write_pin(reverse_pin, 1);
		return;
	case 0:
	default:
		write_pin(forward_pin, 0);
		write_pin(reverse_pin, 0);
		return;
	}
}

void motor::enable(){
	write_pin(enable_pin, 1);
}

void motor::disable(){
	write_pin(enable_pin, 0);
}

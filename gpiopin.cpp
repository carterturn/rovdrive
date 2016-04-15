#include "gpiopin.h"

#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

gpiopin::gpiopin(short pin){
	pinnum = pin;
	stringstream pinStream;
	pinStream << pinnum;
	pinname = pinStream.str();

	pinmode = 0;
	exported = false;
}

void gpiopin::exportpin(){
	ofstream exportFile("/sys/class/gpio/export");
	exportFile << pinname;
	exportFile.close();
	exported = true;
}

void gpiopin::unexport(){
	ofstream unexportFile("/sys/class/gpio/unexport");
	unexportFile << pinname;
	unexportFile.close();
	exported = false;
	pinmode = 0;
}

void gpiopin::write(int value){
	if(pinmode != GPIO_WRITE_MODE){
		cout << "GPIO Error: pin " << pinnum << " not in write mode. Writing to pin disabled\n";
		return;
	}
	ofstream valueFile(getValueFile().c_str());
	valueFile << value;
	valueFile.close();
}

int gpiopin::read(){
	if(pinmode != GPIO_WRITE_MODE || pinmode != GPIO_READ_MODE){
		cout << "GPIO Error: pin " << pinnum << " not inread or  write mode. Reading from pin disabled\n";
		return -1;
	}
	ifstream valueFile(getValueFile().c_str());
	string value;
	valueFile >> value;
	valueFile.close();
	return strtol(value.c_str(), NULL, 10);
}

void gpiopin::setmode(short mode){
	if(!exported){
		cout << "GPIO Error: pin " << pinnum << " not exported. Setting pin mode disabled\n";
		return;
	}
	ofstream directionFile(getDirectionFile().c_str());
	switch(mode){
	case GPIO_NO_MODE:
		break;
		pinmode = mode;
	case GPIO_READ_MODE:
		directionFile << "in";
		break;
		pinmode = mode;
	case GPIO_WRITE_MODE:
		directionFile << "out";
		break;
		pinmode = mode;
	default:
		cout << "GPIO Error: undefined mode: " << mode << "\n";
		break;
	}
	directionFile.close();
}

string gpiopin::getValueFile(){
	return "/sys/class/gpio/gpio" + pinname + "/value";
}

string gpiopin::getDirectionFile(){
	return "/sys/class/gpio/gpio" + pinname + "/direction";
}

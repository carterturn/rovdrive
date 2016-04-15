#pragma once

#include <fstream>

#define GPIO_NO_MODE 0
#define GPIO_READ_MODE 1
#define GPIO_WRITE_MODE 2

class gpiopin{
public:
	gpiopin(short pin);

	void exportpin();
	void unexport();

	void write(int value);
	int read();

	void setmode(short mode);
private:
	short pinnum;
	std::string pinname;

	short pinmode;
	bool exported;

	std::string getValueFile();
	std::string getDirectionFile();
};

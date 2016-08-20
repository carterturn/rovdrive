#include <iostream>

#include "ctserver.h"
#include "motor.h"

using namespace std;

int ctoi(char in){
	switch(in){
	case 'a':
		return -1;
	case 'b':
		return 0;
	case 'c':
		return 1;
	default:
		return 0;
	}
}

int main(int argc, char* argv[]){
	// Initialization
	motor right(3, 27, 9);
	motor left(4, 22, 11);
	motor z(2, 17, 10);

	right.init();
	left.init();
	z.init();

	ctserver server;

	server.create(7276);

	right.enable();
	left.enable();
	z.enable();

	// Main loop

	bool exit = false;
	while(!exit){
		server.getconn();
		string cmd = server.c_read();
		cout << cmd << "\n";

		switch(cmd[0]){
		case 'r':
			server.c_write("right");
			right.run(ctoi(cmd[1]));
			break;
		case 'l':
			server.c_write("left");
			left.run(ctoi(cmd[1]));
			break;
		case 'z':
			server.c_write("z");
			z.run(ctoi(cmd[1]));
			break;
		case 'e':
			server.c_write("goodbye");
			exit = true;
			break;
		default:
			server.c_write("error");
			break;
		}

		server.c_close();
	}

	right.disable();
	left.disable();
	z.disable();

	// Cleanup
	right.cleanup();
	left.cleanup();
	z.cleanup();
}

#include <iostream>
#include <header.h>

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
		motor right(2, 3);
		motor left(4, 17);
		motor z(27, 22);

		right.init();
		left.init();
		z.init();

		right.run(0);
		left.run(0);
		z.run(0);
		
		gpiopin headlight(14);

		headlight.exportpin();
		headlight.setmode(GPIO_WRITE_MODE);
		headlight.write(0); // LED starts on, we need to turn it off

		serversocket server();

		server.create(7276);

		// Main loop

		bool exit = false;
		while(!exit){
				server.getconn();
				string cmd = server.c_read();

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
				case 'h':
						server.c_write("headlight");
						headlight.write(ctoi(cmd[1]));
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

		// Cleanup
		right.cleanup();
		left.cleanup();
		z.cleanup();
		
		led.write(0);
		led.unexport();
}

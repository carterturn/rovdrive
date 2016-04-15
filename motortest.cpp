#include <iostream>
#include "motor.h"
#include "ct_time.h"

using namespace std;

int main(int argc, char * argv[]){
	motor a(2, 3);
	motor b(4, 17);
	motor c(27, 22);

	a.init();
	b.init();
	c.init();
		
	cout << "a forward\n";
	a.run(1);
	csleep(2);
	cout << "a reverse\n";
	a.run(-1);
	csleep(2);
	cout << "a off\n";
	a.run(0);
	csleep(2);

	cout << "b forward\n";
	b.run(1);
	csleep(2);
	cout << "b reverse\n";
	b.run(-1);
	csleep(2);
	cout << "b off\n";
	b.run(0);
	csleep(2);

	cout << "c forward\n";
	c.run(1);
	csleep(2);
	cout << "c reverse\n";
	c.run(-1);
	csleep(2);
	cout << "c off\n";
	c.run(0);
	csleep(2);

	a.cleanup();
	b.cleanup();
	c.cleanup();

	return 0;
}

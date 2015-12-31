#pragma once

#include <iostream>

class serversocket {

public:
	serversocket();
	~serversocket();
	
	int create(int port);
	int getconn();
	
	std::string c_read();
	int c_write(std::string out_data);
	int c_close();

protected:
	int socketid = 0;
	int clientsocketid = 0;

};

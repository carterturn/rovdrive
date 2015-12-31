#include "serversocket.h"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

serversocket::serversocket(){}

serversocket::~serversocket(){}

int serversocket::create(int port){
	int serverSock=socket(AF_INET, SOCK_STREAM, 0);
	
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
	listen(serverSock,4);
	
	socketid = serverSock;
	
	return 0;
}

int serversocket::getconn(){
	
	sockaddr_in clientAddr;
	socklen_t sin_size=sizeof(struct sockaddr_in);
	clientsocketid = accept(socketid,(struct sockaddr*)&clientAddr, &sin_size);
	
	return 0;
}

string serversocket::c_read(){

	string in_data = "";
	bool reading = true;
	while(reading){
		char reccstr[10]; //Space for \0 termination character JIC
		bzero(reccstr,10);
		read(clientsocketid, reccstr, 9);
		in_data += reccstr;
		for(int i = 0; i < 9; i++){
			if(reccstr[i] == ';'){
				reading = false;
				i = 9;
			}
		}
	}
	
	bool text = false;
	string final_data = "";
	for(int i = 0; i < in_data.length(); i++){
		if(!text && in_data[i] == ' ') {}
		else {
			text = true;
			if(in_data[i] == ';') i = in_data.length();
			else final_data += in_data[i];
		}
	}
	
	return final_data;
}

int serversocket::c_write(string out_data){

	out_data = out_data+";";

	if(out_data.length() > 8){
	bool done = true;
	while(done){
		string temp = "";
		for(int i = 0; i < 8; i++){
			temp += out_data[0];
			if(out_data[0] == ';'){
				done = false;
				i = 8;
			}
			out_data.erase(0,1);
		}
		//cout << "WRITING: " << temp << "\n";
		send(clientsocketid,temp.c_str(),sizeof(temp.c_str()),0);
		}
	}
	else{
		send(clientsocketid,out_data.c_str(),sizeof(out_data.c_str()),0);
	}
	
	return 0;
}

int serversocket::c_close(){
	shutdown(clientsocketid, 2);
	close(clientsocketid);
	
	return 0;
}

/*
  Copyright 2016 Carter Turnbaugh

  This file is part of Terca ROV Drive.

  Terca ROV Drive is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Terca ROV Drive is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Terca ROV Drive.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <thread>

class watchdog {

public:
	watchdog(void (*kill_function)(void *), void * param);
	~watchdog();
	
	int start();

	int kick(int time);

	int end();

protected:

	std::thread watcher;
	bool watching;

	int counter;

	void (*kill_function)(void *);
	void * param;

	void run();
};

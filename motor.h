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

class motor{
public:
	motor(short enable_pin, short forward_pin, short reverse_pin);

	void init();
	void cleanup();

	void run(short direction);
	void enable();
	void disable();
private:

	void setup_pin(short pin);
	void cleanup_pin(short pin);
	void write_pin(short pin, short value);
	
	short enable_pin;
	short forward_pin;
	short reverse_pin;
};

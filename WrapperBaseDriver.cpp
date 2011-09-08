/***************************************************************************
 
    file                 : WrapperBaseDriver.cpp
    copyright            : (C) 2007 Daniele Loiacono
 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "WrapperBaseDriver.h"
#include <fstream>


string 
WrapperBaseDriver::drive(string sensors)
{
	CarState cs(sensors);
	CarControl cc = wDrive(cs);

	/* write sensor.data
	ofstream sensorFile;
	sensorFile.open("sensor.file.txt",ios::app);
	sensorFile << cs.writeSensor() << endl;
	sensorFile.close();

	ofstream speedFile;
	speedFile.open("calculator.file.txt",ios::app);
	speedFile << cs.writeTester() << cs.calculator() << endl;
	speedFile.close();

	ofstream effectorFile;
	effectorFile.open("effector.file.txt",ios::app);
	effectorFile << cc.toString() << endl;
	effectorFile.close(); */



	return cc.toString();	
}



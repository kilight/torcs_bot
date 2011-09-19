/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::drive.h
		10.09.2011
*/
/*		argument.set		value.set
		------------		---------
*/

#ifndef drive_class
#define drive_class

#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
#include"../CarState.h"
#include"../lib.db/db.h"
#include"fann_net.h"

class drive_object
{
private:	db* database;
		fann_net net;

		float accel;
		float brake;
		float steer;	
		
public:		 drive_object();		// race constructor
		 drive_object(db* database);	// learn constructor
		~drive_object();

		int race(CarState &cs);		// common racing interface

		float getAccel(){return accel;}
		float getBrake(){return brake;}
		float getSteer(){return steer;}
};
#endif

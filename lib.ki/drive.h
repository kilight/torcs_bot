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

const int num_inputs = 1;
const int num_outputs = 1;

class drive_object
{
private:	db* database;
		fann_net net;
	
		
public:		 
		drive_object();			// race constructor
		 drive_object(db* database);	// learn constructor
		~drive_object();

		float accel;
		float brake;
		float steer;

		void race(CarState &cs);		// common racing interface
		void race_ki(CarState &cs);

		float getAccel(){return accel;}
		float getBrake(){return brake;}
		float getSteer(){return steer;}
		
		void learnFromDatabase();
		void learnFromDataFolder();
		void loadPrevNet() {
			system("cp lib.ki/net.miner/torcs.net lib.ki/net.miner/torcs.bak");
			net.create_from_file("lib.ki/net.miner/torcs.net");
		}
};
#endif

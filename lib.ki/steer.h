/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::steer.h
		27.08.2011
*/
/*		argument.set		value.set
		------------		---------
*/

#ifndef steer_class
#define steer_class

#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
#include"../CarState.h"
#include"../lib.db/db.h"
#include"fann_net.h"

const int num_steer_inputs = 1;
const int num_steer_outputs = 1;

class steer_object
{
private:	db* database;
		fann_net net;
		
public:		 steer_object();		// race constructor
		steer_object(db* database);	// learn constructor
		~steer_object();
		
		
		float steer;
		float track[18];
		float getSteer(void){return steer;}
		
		void learnFromDatabase();
		void learnFromDataFolder();
		void loadPrevNet() {
			system("cp lib.ki/net.steer.miner/torcs.net lib.ki/net.steer.miner/torcs.bak");
			net.create_from_file("lib.ki/net.steer.miner/torcs.net");
		}
		
		void race(CarState &cs);
		void race_ki(CarState &cs);
				
};
#endif



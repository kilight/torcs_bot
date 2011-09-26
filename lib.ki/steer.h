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

class steer_object
{
private:	db* database;
		
public:		 steer_object();		// race constructor
		// steer_object(db* database);	// learn constructor
		~steer_object();
		
		
		float steer;
		float track[18];
		float getSteer(void){return steer;}
		
		void race(CarState &cs);
				
};
#endif



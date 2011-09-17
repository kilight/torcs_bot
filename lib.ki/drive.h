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
// #include"../lib.fann/include/fann.h"


class drive_object
{
private:	db* database;	
		
public:		 drive_object();		// race constructor
		 drive_object(db* database);	// learn constructor
		~drive_object();

		int race(CarState &cs);		// common racing interface
};
#endif

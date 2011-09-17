/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::shift.h
		27.08.2011
*/
/*		argument.set		value.set
		------------		---------
*/

#ifndef shift_class
#define shift_class

#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
#include"../CarState.h"
#include"../lib.db/db.h"
// #include"../lib.fann/include/fann.h"

class shift_object
{
private:	db* database;	
		
public:		 shift_object();		// race constructor
		 shift_object(db* database);	// learn constructor
		~shift_object();

		int race(CarState &cs);				// common racing interface
		int tree(CarState &cs);				// desicion.tree including online reinforcement.build
		int simple_interpolation_racer(CarState &cs);

		void slp_1(float rpm,int gear);			// single.layer.perceptron learn function
		void simple_interpolation(float rpm,int gear);	// simple learn funktion
};
#endif

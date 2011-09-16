/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::shift.h
		27.08.2011
*/
/*		argument.set		value.set
		------------		---------
		int speedX			int gear
		int speedY			bool clutch
		int speedZ
		int rpm
		int gear
*/

#ifndef shift_class
#define shift_class

#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

#include"../BaseDriver.h"
#include"../CarState.h"
#include"../CarControl.h"
#include"../SimpleParser.h"
#include"../WrapperBaseDriver.h"
#include"../lib.db/db.h"

class shift_learn
{
protected:	// int gear_y;		// y_0
			// int clutch;		// y_1

private:	 shift_learn();
			~shift_learn();

			// void set_0(DataBase &db);
			// void set_1(DataBase &db);
};

class shift_object
{
public:		int gear_x;			// x_0
			int rpm;			// x_1
			int rpm_puffer;		// x_2
			int speed;			// x_3
			int speed_puffer;	// x_4

			int speedX_puffer;	// x_5
			int speedY_puffer;	// x_6

			float clutch;
			float clutchMax;
			float clutchDelta;
			float clutchRange;
			float clutchDeltaTime;
			float clutchDeltaRaced;
			float clutchDec;
			float clutchMaxModifier;
			float clutchMaxTime;

			
public:		 shift_object();			
			 shift_object(CarState &cs);	// race constructor
			~shift_object();

			void set_0(CarState &cs);
			void set_1(CarState &cs);
			void set_2(void);
			void set_3(CarState &cs);
			void set_4(void);

			int get_0(void);
			int get_1(void);
			int get_2(void);
			int get_3(void);
			int get_4(void);

			int race(CarState &cs);			// racing method
			void clutching(CarState &cs);	// clutch calculator

};

#endif
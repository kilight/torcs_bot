/***************************************************************************
 
    file:				CarState.h
    change.date:		01.06.2011
 
 ***************************************************************************/

/***************************************************************************
 ***************************************************************************/

#ifndef CARSTATE_H_
#define CARSTATE_H_

#define FOCUS_SENSORS_NUM 5
#define TRACK_SENSORS_NUM 19
#define OPPONENTS_SENSORS_NUM 36

#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>
#include "SimpleParser.h"

using namespace std;

class CarState
{

	public:



		/* Funktionsdefinitionen */
		string writeSensor();	// string für sensor.file.txt
		string writeTester();	// string für Testzwecke

		int calculator();		// rechner für andere Strategiewerte



		CarState(){};				//
        CarState(string sensors);	//
        string toString();			// 

  

/*lap.time */		float getCurLapTime();
					void setCurLapTime(float curLapTime);
					float getLastLapTime();
					void setLastLapTime(float lastLapTime);

 /*lap.pos */       float getDistRaced();
				    void setDistRaced(float distRaced);
					float getDistFromStart();
					void setDistFromStart(float distFromStart);

/*lap.speed.a */	float getSpeedX();
					void setSpeedX(float speedX);
					float getSpeedY();
					void setSpeedY(float speedY);
					float getSpeedZ();
					void setSpeedZ(float speedZ);

/*lap.speed.b */    int getRpm();
					void setRpm(int rpm);
					int getGear();
					void setGear(int gear);

 /*lap.dist.a */    float getAngle();
					void setAngle(float angle);
				    float getTrackPos();
				    void setTrackPos(float trackPos);
					float getTrack(int i);
					void setTrack(int i, float value);			
				
		/*lap.konstanten */	
		float getDamage();
		void setDamage(float damage);
		float getFuel();
		void setFuel(float fuel);

        int getRacePos();
        void setRacePos(int racePos);
        float getOpponents(int i);
        void setOpponents(int i, float value);

        float getWheelSpinVel(int i);
        void setWheelSpinVel(int i, float value);
        float getFocus(int i);
        void setFocus(int i, float value);
        float getZ();
        void setZ(float z);



private:
        float angle;
        float curLapTime;
        float damage;
        float distFromStart;
        float distRaced;
        float focus[FOCUS_SENSORS_NUM];
        float fuel;
        int   gear;
        float lastLapTime;
        float opponents[OPPONENTS_SENSORS_NUM];
        int   racePos;
        int   rpm;
        float speedX;
        float speedY;
        float speedZ;
        float track[TRACK_SENSORS_NUM];
        float trackPos;
        float wheelSpinVel[4];
        float z;
        
};

#endif /*CARSTATE_H_*/
#ifndef SENSOR_H_
#define SENSOR_H_

#define FOCUS_SENSORS_NUM 5
#define TRACK_SENSORS_NUM 19
#define OPPONENTS_SENSORS_NUM 36

#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>
#include "../SimpleParser.h"

using namespace std;

class sensor
{

private:
	int numPnt;
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
	float accel;
	float brake;
	int gearCmd;
	float steer;
        float clutch;

public:
	
	sensor(){};

        sensor(string sensors);

        string toString();

        /* Getter and setter methods */
        
	int getNumPnt() {
		return numPnt;
	}
	
	void setNumPnt(int numPnt) {
		this->numPnt = numPnt;
	}
		
        float getAngle();
        
        void setAngle(float angle);
        
        float getCurLapTime();
        
        void setCurLapTime(float curLapTime);
        
        float getDamage();
        
        void setDamage(float damage);
        
        float getDistFromStart();
        
        void setDistFromStart(float distFromStart);
        
        float getDistRaced();
        
        void setDistRaced(float distRaced);

        float getFocus(int i);

        void setFocus(int i, float value);

        float getFuel();
        
        void setFuel(float fuel);
        
        int getGear();
        
        void setGear(int gear);
        
        float getLastLapTime();
        
        void setLastLapTime(float lastLapTime);
        
        float getOpponents(int i);
        
        void setOpponents(int i, float value);
        
        int getRacePos();
        
        void setRacePos(int racePos);
        
        int getRpm();
        
        void setRpm(int rpm);
        
        float getSpeedX();
        
        void setSpeedX(float speedX);
        
        float getSpeedY();
        
        void setSpeedY(float speedY);
        
        float getSpeedZ();

        void setSpeedZ(float speedZ);

        float getTrack(int i);
        
        void setTrack(int i, float value);
        
        float getTrackPos();
        
        void setTrackPos(float trackPos);
        
        float getWheelSpinVel(int i);
        
        void setWheelSpinVel(int i, float value);

        float getZ();

        void setZ(float z);

	float getAccel() {
		return accel;
	}
	
	void setAccel(float accel) {
		this->accel = accel;
	}
	
	float getBrake() {
		return brake;
	}
	
	void setBrake(float brake) {
		this->brake = brake;
	}
	
	int getGearCmd() {
		return gearCmd;
	}
	
	void setGearCmd(int gearCmd) {
		this->gearCmd = gearCmd;
	}
	
	float getSteer() {
		return steer;
	}
	
	void setSteer(float steer) {
		this->steer = steer;
	}
	
	float getClutch() {
		return clutch;
	}
	
	void setClutch(float clutch) {
		this->clutch = clutch;
	}

};

#endif /*SENSOR_H_*/

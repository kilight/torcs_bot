/*	Sensor class for AI Light Torcs project
	author: Robin Lehmann
	date: 11.08.2011
*/

#ifndef sensorclass
#define sensorclass

#include <string>
#include "SimpleParser.h"

class sensor{
	public:
		sensor();
		sensor(string stateString);
	
		void setCurLapTime(double curLapTime) { this->curLapTime = curLapTime; }
		double getCurLapTime() { return this->curLapTime; }

                void setDamage ( int damage ) { this->damage = damage; }
                int getDamage() { return this->damage; }

                void setAngle ( double angle ) { this->angle = angle; }
                double getAngle() { return this->angle; }

                void setDistFromStart ( double distFromStart ) { this->distFromStart = distFromStart; }
                double getDistFromStart() { return this->distFromStart; }

                void setDistRaced ( double distRaced ) { this->distRaced  = distRaced; }
                double getDistRaced() { return this->distRaced; }

                void seuel ( double fuel ) { this->fuel  =fuel; }
                double getFuel() { return this->fuel; }

                void setGear ( int gear ) { this->gear = gear; }
                int getGear() { return this->gear; }

                void setLastLapTime ( double lastLapTime ) { this->lastLapTime = lastLapTime; }
                double getLastLapTime() { return this->lastLapTime; }

                void setOppSensor ( double* oppSensor ) { this->oppSensor = oppSensor; }
                double* getOppSensor() { return this->oppSensor; }

                void setPos ( double pos ) { this->pos = pos; }
                double getPos() { return this->pos; }

                void setRpm ( double rpm ) { this->rpm = rpm; }
                double getRpm() { return this->rpm; }

                void sepeedX ( double speedX ) { this->speedX = speedX; }
                double getSpeedX() { return this->speedX; }

                void setSpeedY ( double speedY ) { this->speedY = speedY; }
                double getSpeedY() { return this->speedY; }

                void setSpeedZ ( double speedZ ) { this->speedZ = speedZ; }
                double getSpeedZ() { return this->speedZ; }

                void setTrackSensor ( double* trackSensor ) { this->trackSensor = trackSensor; }
                double* getTrackSensor() { return this->trackSensor; }

                void setTrackPos ( double trackPos ) { this->trackPos = trackPos; }
                double getTrackPos() { return this->trackPos; }

                void setWheelSpin ( double* wheelSpin ) { this->wheelSpin = wheelSpin; }
                double* getWheelSpin() { return this->wheelSpin; }

                void setZ ( double z ) { this->z = z; }
                double getZ() { return this->z; }

                void setFocus ( double* focus ) { this->focus = focus; }
                double* getFocus() { return this->focus; }

	
	private:
		double angle;
		double curLapTime;
		int damage;
		double distFromStart;
		double distRaced;
		double fuel;
		int gear;
		double lastLapTime;
		double* oppSensor;
		double pos;
		double rpm;
		double speedX;
		double speedY;
		double speedZ;
		double* trackSensor;
		double trackPos;
		double* wheelSpin;
		double z;
		double* focus;
	
};

#endif

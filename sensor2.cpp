#include "sensor2.h"


sensor::sensor(string sensors)
{
        SimpleParser::parse(sensors, "angle", this->angle);
        SimpleParser::parse(sensors, "curLapTime", this->curLapTime);
        SimpleParser::parse(sensors, "damage", this->damage);
        SimpleParser::parse(sensors, "distFromStart", this->distFromStart);
        SimpleParser::parse(sensors, "distRaced", this->distRaced);
        SimpleParser::parse(sensors, "focus", this->focus, FOCUS_SENSORS_NUM);
        SimpleParser::parse(sensors, "fuel", this->fuel);
        SimpleParser::parse(sensors, "gear", this->gear);
        SimpleParser::parse(sensors, "lastLapTime", this->lastLapTime);
        SimpleParser::parse(sensors, "opponents", this->opponents, OPPONENTS_SENSORS_NUM);
        SimpleParser::parse(sensors, "racePos", this->racePos);
        SimpleParser::parse(sensors, "rpm", this->rpm);
        SimpleParser::parse(sensors, "speedX", this->speedX);
        SimpleParser::parse(sensors, "speedY", this->speedY);
        SimpleParser::parse(sensors, "speedZ", this->speedZ);
        SimpleParser::parse(sensors, "track", this->track, TRACK_SENSORS_NUM);
        SimpleParser::parse(sensors, "trackPos", this->trackPos);
        SimpleParser::parse(sensors, "wheelSpinVel", this->wheelSpinVel, 4);
        SimpleParser::parse(sensors, "z", this->z);
}

string
sensor::toString()
{
	string str;
	str  = SimpleParser::stringify("angle", this->angle);
	str += SimpleParser::stringify("curLapTime", this->curLapTime);
	str += SimpleParser::stringify("damage", this->damage);
	str += SimpleParser::stringify("distFromStart", this->distFromStart);
	str += SimpleParser::stringify("distRaced", this->distRaced);
	str += SimpleParser::stringify("focus", this->focus, FOCUS_SENSORS_NUM);
	str += SimpleParser::stringify("fuel", this->fuel);
	str += SimpleParser::stringify("gear", this->gear);
	str += SimpleParser::stringify("lastLapTime", this->lastLapTime);
	str += SimpleParser::stringify("opponents", this->opponents, OPPONENTS_SENSORS_NUM);
	str += SimpleParser::stringify("racePos", this->racePos);
	str += SimpleParser::stringify("rpm", this->rpm);
	str += SimpleParser::stringify("speedX", this->speedX);
	str += SimpleParser::stringify("speedY", this->speedY);
	str += SimpleParser::stringify("speedZ", this->speedZ);
	str += SimpleParser::stringify("track", this->track, TRACK_SENSORS_NUM);
	str += SimpleParser::stringify("trackPos", this->trackPos);
	str += SimpleParser::stringify("wheelSpinVel", this->wheelSpinVel, 4);
	str += SimpleParser::stringify("z", this->z);
	
	return str;
	        
}

float 
sensor::getAngle()
{
        return angle;
};

void 
sensor::setAngle(float angle)
{
        this->angle = angle;
};

float 
sensor::getCurLapTime()
{
        return curLapTime;
};

void 
sensor::setCurLapTime(float curLapTime)
{
        this->curLapTime = curLapTime;
};

float
sensor::getDamage()
{
        return damage;
};

void
sensor::setDamage(float damage)
{
        this->damage = damage;
};

float
sensor::getDistFromStart()
{
        return distFromStart;
};

void
sensor::setDistFromStart(float distFromStart)
{
        this->distFromStart = distFromStart;
};

float
sensor::getDistRaced()
{
        return distRaced;
};

void
sensor::setDistRaced(float distRaced)
{
        this->distRaced = distRaced;
};

float
sensor::getFocus(int i)
{
        assert(i>=0 && i<FOCUS_SENSORS_NUM);
        return focus[i];
};


void
sensor::setFocus(int i, float value)
{
        assert(i>=0 && i<FOCUS_SENSORS_NUM);
        this->focus[i] = value;
};

float
sensor::getFuel()
{
        return fuel;
};

void
sensor::setFuel(float fuel)
{
        this->fuel = fuel;
};

int
sensor::getGear()
{
        return gear;
};

void
sensor::setGear(int gear)
{
        this->gear = gear;
};

float 
sensor::getLastLapTime()
{
        return lastLapTime;
};

void 
sensor::setLastLapTime(float lastLapTime)
{
        this->lastLapTime = lastLapTime;
};

float
sensor::getOpponents(int i)
{
        assert(i>=0 && i<OPPONENTS_SENSORS_NUM);
        return opponents[i];
        
};

void
sensor::setOpponents(int i, float value)
{
        assert(i>=0 && i<OPPONENTS_SENSORS_NUM);
        this->opponents[i] = value;
};

int
sensor::getRacePos()
{
        return racePos;
};

void
sensor::setRacePos(int racePos)
{
        this->racePos = racePos;
};

int
sensor::getRpm()
{
        return rpm;
};

void
sensor::setRpm(int rpm)
{
        this->rpm = rpm;
};

float
sensor::getSpeedX()
{
        return speedX;
};

void
sensor::setSpeedX(float speedX)
{
        this->speedX = speedX;
};

float
sensor::getSpeedY()
{
        return speedY;
};

void
sensor::setSpeedY(float speedY)
{
        this->speedY = speedY;
};

float
sensor::getSpeedZ()
{
        return speedZ;
};


void
sensor::setSpeedZ(float speedZ)
{
        this->speedZ = speedZ;
};

float
sensor::getTrack(int i)
{
        assert(i>=0 && i<TRACK_SENSORS_NUM);
        return track[i];
};


void
sensor::setTrack(int i, float value)
{
        assert(i>=0 && i<TRACK_SENSORS_NUM);
        this->track[i] = value;
};

float
sensor::getTrackPos()
{
        return trackPos;
};

void
sensor::setTrackPos(float prackPos)
{
        this->trackPos = trackPos;
};

float 
sensor::getWheelSpinVel(int i)
{
	assert(i>=0 && i<4);
	return wheelSpinVel[i];
}

void 
sensor::setWheelSpinVel(int i, float value)
{
	assert(i>=0 && i<4);
	wheelSpinVel[i]=value;
}

float
sensor::getZ()
{
        return z;
};

void
sensor::setZ(float z)
{
    this->z = z;
};

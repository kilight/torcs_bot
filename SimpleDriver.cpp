/***************************************************************************
 
    file                 : SimpleDriver.cpp
    copyright            : (C) 2007 Daniele Loiacono
 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "SimpleDriver.h"


/***  shift management  ***/
/**************************/
CarControl SimpleDriver::wDrive(CarState cs)
{
/*	check if car is currently stuck and update stuck counter
	after car is stuck for a while apply recovering policy
    	set gear and sterring command assuming car is pointing in a direction out of track
    	to bring car parallel to track axis
*/

/*	const int SimpleDriver::stuckTime = 25;
	const float SimpleDriver::stuckAngle = .523598775; //PI/6

	if(fabs(cs.getAngle())>stuckAngle){stuck++;}
	else{stuck = 0;}

    	if(stuck>stuckTime)
	{
	        float steer=-cs.getAngle()/steerLock; 
	        int gear=-1;

        	if(cs.getAngle()*cs.getTrackPos()>0)		// if car is pointing in the correct direction revert gear and steer  
        	{
        	    gear=1;
        	    steer=-steer;
        	}

	        clutching(cs,clutch);				// Calculate clutching
	        CarControl cc (1.0,0.0,gear,steer,clutch);	// build a CarControl variable and return it
	        return cc;
	}
   	else
*/
   	
        	float steer=getSteer(cs); 	// compute steering
		if(steer < -1)			// normalize steering
		steer = -1;
		if(steer > 1)
		steer = 1;

        	clutching(cs,clutch);
		driver.race_ki(cs);	
        	CarControl cc(driver.getAccel(),driver.getBrake(),shift.race(cs),steer,clutch);	
        	return cc;
}

/* Clutch constants */
const float SimpleDriver::clutchMax=0.5;
const float SimpleDriver::clutchDelta=0.05;
const float SimpleDriver::clutchRange=0.82;
const float SimpleDriver::clutchDeltaTime=0.02;
const float SimpleDriver::clutchDeltaRaced=10;
const float SimpleDriver::clutchDec=0.01;
const float SimpleDriver::clutchMaxModifier=1.3;
const float SimpleDriver::clutchMaxTime=1.5;
void SimpleDriver::clutching(CarState &cs, float &clutch)
{
  double maxClutch = clutchMax;

  // Check if the current situation is the race start
  if (cs.getCurLapTime()<clutchDeltaTime  && stage==RACE && cs.getDistRaced()<clutchDeltaRaced)
    clutch = maxClutch;

  // Adjust the current value of the clutch
  if(clutch > 0)
  {
    double delta = clutchDelta;
    if (cs.getGear() < 2)
	{
      // Apply a stronger clutch output when the gear is one and the race is just started
	  delta /= 2;
      maxClutch *= clutchMaxModifier;
      if (cs.getCurLapTime() < clutchMaxTime)
        clutch = maxClutch;
	}

    // check clutch is not bigger than maximum values
	clutch = min(maxClutch,double(clutch));

	// if clutch is not at max value decrease it quite quickly
	if (clutch!=maxClutch)
	{
	  clutch -= delta;
	  clutch = max(0.0,double(clutch));
	}
	// if clutch is at max value decrease it very slowly
	else
		clutch -= clutchDec;
  }
}
/* Steering constants*/
const float SimpleDriver::steerLock=0.785398;
const float SimpleDriver::steerSensitivityOffset=160.0;
const float SimpleDriver::wheelSensitivityCoeff=1;
float SimpleDriver::getSteer(CarState &cs)
{
	// steering angle is compute by correcting the actual car angle w.r.t. to track 
	// axis [cs.getAngle()] and to adjust car position w.r.t to middle of track [cs.getTrackPos()*0.5]
    float targetAngle=(cs.getAngle()-cs.getTrackPos()*0.5);
    // at high speed reduce the steering command to avoid loosing the control
        return targetAngle/steerLock;


}

/* ABS Filter Constants */
const float SimpleDriver::wheelRadius[4]={0.3179,0.3179,0.3276,0.3276};
const float SimpleDriver::absSlip=2.0;
const float SimpleDriver::absRange=3.0;
const float SimpleDriver::absMinSpeed=3.0;
float SimpleDriver::filterABS(CarState &cs,float brake)
{
	// convert speed to m/s
	float speed = cs.getSpeedX() / 3.6;
	// when spedd lower than min speed for abs do nothing
    if (speed < absMinSpeed)
        return brake;
    
    // compute the speed of wheels in m/s
    float slip = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        slip += cs.getWheelSpinVel(i) * wheelRadius[i];
    }
    // slip is the difference between actual speed of car and average speed of wheels
    slip = speed - slip/4.0f;
    // when slip too high applu ABS
    if (slip > absSlip)
    {
        brake = brake - (slip - absSlip)/absRange;
    }
    
    // check brake is not negative, otherwise set it to zero
    if (brake<0)
    	return 0;
    else
    	return brake;
}

void SimpleDriver::onShutdown(){cout<<"Bye bye!"<<endl;}
void SimpleDriver::onRestart(){cout<<"Restarting the race!"<<endl;}
void SimpleDriver::init(float *angles)
{

	// set angles as {-90,-75,-60,-45,-30,20,15,10,5,0,5,10,15,20,30,45,60,75,90}

	for (int i=0; i<5; i++)
	{
		angles[i]=-90+i*15;
		angles[18-i]=90-i*15;
	}

	for (int i=5; i<9; i++)
	{
			angles[i]=-20+(i-5)*5;
			angles[18-i]=20-(i-5)*5;
	}
	angles[9]=0;
}

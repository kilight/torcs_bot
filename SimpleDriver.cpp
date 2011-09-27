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
/***  ki management  ***/
/**************************/
const int SimpleDriver::stuckTime = 25;
const float SimpleDriver::stuckAngle = .523598775; //PI/6
CarControl SimpleDriver::wDrive(CarState cs)
{
/*	check if car is currently stuck and update stuck counter
	after car is stuck for a while apply recovering policy
    	set gear and sterring command assuming car is pointing in a direction out of track
    	to bring car parallel to track axis
*/



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
	{

   	
		// correcting the actual car angle getAngle() to 0
		// adjust car position getTrackPos() to 0


		/*float steer=(cs.getAngle()-cs.getTrackPos()*0.5)/steerLock;
		if (cs.getSpeedX() > steerSensitivityOffset) steer/(steerLock*(cs.getSpeedX()-steerSensitivityOffset)*wheelSensitivityCoeff);
   		else steer/steerLock;
		if(steer<-1){steer=-1;}
		if(steer>1){steer=1;}

        	float accel,brake;
		float ab = getAccel(cs);
		if (ab>0){accel=ab; brake = 0;}
		else     {accel=0; brake = filterABS(cs,-ab);}*/
        

		// ki racing interlink
		/**********************************/
		// shifting bot
			// shift.reinforcement(cs);
			// shift.race(cs);
			shift.tree(cs);
		// driving bot
			driver.race(cs);
			// driver.race_ki(cs);
		// steering bot
			// steer.race(cs);
			steer.race(cs);
		// clutching (stolen.code)
			clutching(cs,clutch);
		/**********************************/
        	CarControl cc(driver.getAccel(),driver.getBrake(),shift.getGear(),steer.getSteer(),clutch);	
        	return cc;
	}
}
const float SimpleDriver::steerLock=0.785398;
const float SimpleDriver::steerSensitivityOffset=160.0;
const float SimpleDriver::wheelSensitivityCoeff=1;

const float SimpleDriver::clutchMax=0.5;
const float SimpleDriver::clutchDelta=0.05;
const float SimpleDriver::clutchRange=0.82;
const float SimpleDriver::clutchDeltaTime=0.02;
const float SimpleDriver::clutchDeltaRaced=10;
const float SimpleDriver::clutchDec=0.01;
const float SimpleDriver::clutchMaxModifier=1.3;
const float SimpleDriver::clutchMaxTime=1.5;
void SimpleDriver::clutching(CarState &cs,float &clutch)
{
  	 double maxClutch = clutchMax;

  	// Check if the current situation is the race start
  	if (cs.getCurLapTime()<clutchDeltaTime  && stage==RACE && 
	    cs.getDistRaced()<clutchDeltaRaced)
   	{clutch = maxClutch;}

  
  	if(clutch > 0)	// Adjust the current value of the clutch
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

/* Accel and Brake Constants*/
const float SimpleDriver::maxSpeedDist=30;
const float SimpleDriver::maxSpeed=350;
const float SimpleDriver::sin5 = 0.08716;
const float SimpleDriver::cos5 = 0.99619;
float SimpleDriver::getAccel(CarState &cs)
{
	if (cs.getTrackPos() < 1 && cs.getTrackPos() > -1)	// checks if car is out of track else accel=0,3
	{
	        float rxSensor=cs.getTrack(10);		// reading of sensor at +5 degree w.r.t. car axis
	        float cSensor=cs.getTrack(9);		// reading of sensor parallel to car axis
	        float sxSensor=cs.getTrack(8);		// reading of sensor at -5 degree w.r.t. car axis
	        float targetSpeed;
        
	        if (cSensor>maxSpeedDist || 
		   (cSensor>=rxSensor && cSensor >= sxSensor))	// track is straight and enough far from a turn: max speed
		{targetSpeed = maxSpeed;}
		else					// approaching a rightturn 
		{if(rxSensor>sxSensor)			// approximate "angle" of turn
	         {
			float h = cSensor*sin5;
			float b = rxSensor - cSensor*cos5;
			float sinAngle = b*b/(h*h+b*b);
	                targetSpeed = maxSpeed*(cSensor*sinAngle/maxSpeedDist);		// target speed depending on turn and how close it is
		 }
	         else // approaching a turn on left
		 {
 	               float h = cSensor*sin5;						// approximate the "angle" of turn
 	               float b = sxSensor - cSensor*cos5;
 	               float sinAngle = b*b/(h*h+b*b);					// target speed depending on turn and how close it is
 	               targetSpeed = maxSpeed*(cSensor*sinAngle/maxSpeedDist);
		 }
		}
		return 2/(1+exp(cs.getSpeedX()-targetSpeed))-1;		// accel/brake (expontially scaled): difference target speed and current one
	}
	else return 0.3; 						// out of track

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
				angles[9]=0;			// set angle[0]=0
	for (int i=0;i<5;i++){	angles[i]=-90+i*15;		// set angle[ 0 bis  4]={-90,-75,-60,-45,-30}
				angles[18-i]=90-i*15;	}	// set angle[14 bis 18]={+30,+45,+60,+75,+90}
	for (int i=5;i<9;i++){	angles[i]=-20+(i-5)*5;		// set angle[ 5 bis  8]={-20,-15,-10,-5}
				angles[18-i]=20-(i-5)*5;}	// set angle[10 bis 13]={+5,+10,+15,+20}
}

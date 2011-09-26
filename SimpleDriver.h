/***************************************************************************
 
    file                 : SimpleDriver.h
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
#ifndef SIMPLEDRIVER_H_
#define SIMPLEDRIVER_H_

#include <iostream>
#include <cmath>
#include "BaseDriver.h"
#include "CarState.h"
#include "CarControl.h"
#include "SimpleParser.h"
#include "WrapperBaseDriver.h"

#include "lib.ki/shift.h"
#include "lib.ki/drive.h"
#include "lib.ki/steer.h"

#define PI 3.14159265

using namespace std;

class SimpleDriver : public WrapperBaseDriver
{
public:		SimpleDriver(){stuck=0;clutch=0.0;};		// Constructor
		virtual CarControl wDrive(CarState cs);		// SimpleDriver implements a simple 
								// and heuristic controller for driving
		virtual void onShutdown();			// Print a shutdown message 
		virtual void onRestart();			// Print a restart message 
		virtual void init(float *angles);		// Initialization of the desired angles for the rangefinders

private:

	/*** Bot classes ***/
	/*******************/
	shift_object shift;
	drive_object driver;
	steer_object steer;
	
	/*** Stuck constants ***/
	/***********************/
	int stuck;				// counter of stuck steps
	static const int stuckTime;		// How many time steps the controller wait 
						// before recovering from a stuck position
	static const float stuckAngle;		// When car angle w.r.t. track axis is grather
						// tan stuckAngle, the car is probably stuck

	/* Steering constants*/
	static const float steerLock;			// Angle associated to a full steer command
	static const float steerSensitivityOffset;	// Min speed to reduce steering command 
	static const float wheelSensitivityCoeff;	// Coefficient to reduce steering command 
							// at high speed (to avoid loosing the control)
	
	/* Accel and Brake Constants*/
	static const float maxSpeed;		// max speed allowed
	static const float maxSpeedDist;	// Min distance from track border to drive at  max speed
	static const float sin5;		// pre-computed sin5
	static const float cos5;		// pre-computed cos5
	
	/* ABS Filter Constants */
	static const float wheelRadius[4];	// Radius of the 4 wheels of the car
	static const float absSlip;		// min slip to prevent ABS					
	static const float absRange;		// range to normalize the ABS effect on the brake
	static const float absMinSpeed;		// min speed to activate ABS

	/* Clutch constants */
	float clutch;				// current clutch
	static const float clutchMax;
	static const float clutchDelta;
	static const float clutchRange;
	static const float clutchDeltaTime;
	static const float clutchDeltaRaced;
	static const float clutchDec;
	static const float clutchMaxModifier;
	static const float clutchMaxTime;

	float getSteer(CarState &cs);			// Solves the steering subproblems
	float getAccel(CarState &cs);			// Solves the gear changing subproblems
	float filterABS(CarState &cs,float brake);	// Apply an ABS filter to brake command
	void clutching(CarState &cs, float &clutch);	// Solves the clucthing subproblems
};

#endif /*SIMPLEDRIVER_H_*/

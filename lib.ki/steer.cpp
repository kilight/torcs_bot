/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::shift.cpp
		27.08.2011
*/
#include"steer.h"
/***  class steer_object  ****
*****************************/
steer_object::steer_object()
{
	steer=0;
}
steer_object::~steer_object(){}
/**   class steer_object race.net   **
*************************************/
void steer_object::race(CarState &cs)
{
	int view=0;	
	int track=0;
	
	float direction[19];
	direction[9]=0;							// set angle[0]=0
	for (int i=0;i<5;i++){	direction[i]=-90+i*15;			// set angle[ 0 bis  4]={-90,-75,-60,-45,-30}
				direction[18-i]=90-i*15;	}	// set angle[14 bis 18]={+30,+45,+60,+75,+90}
	for (int i=5;i<9;i++){	direction[i]=-20+(i-5)*5;		// set angle[ 5 bis  8]={-20,-15,-10,-5}
				direction[18-i]=20-(i-5)*5;	}	// set angle[10 bis 13]={+5,+10,+15,+20}

	bool offTrack = false;
	int totalsum = 0;
	for(int i=0;i<17;i++)
	{	
		int sum = cs.getTrack(i)+cs.getTrack(i+1)+cs.getTrack(i+2);
		if(sum>track)
		{ track=sum;
		  view=i+1; }
		if(sum <0)
		  offTrack = true;
	}

/*	if(track == 0) 
		{ view = 9; } */
	if(offTrack && track == 0) 
	{ if (cs.getTrackPos() < -0.95 && track < 150) 
		{ view = 18;}
	  else if (cs.getTrackPos() > 0.95 && track < 150)
		{ view = 0;}

	  cout << cs.getTrackPos() << " " << view << endl;
	}

	if(cs.getTrackPos() < -0.8 && view < 9) { view = 9; }
	if(cs.getTrackPos() > 0.8 && view > 9) {view = 9;}

	for(int i=0;i<19;i++){if (view==i){steer=(1)*(float)sin(direction[view])*0.2 * (125/(cs.getSpeedX()+1));}}

	for(int i=0;i<17;i++)
	{	
		if((cs.getTrack(i)+cs.getTrack(i+1))<stuck)
		{ stuck=(cs.getTrack(i)+cs.getTrack(i+1)); }
	}

	// if(track<0){steer=(-1)*cs.getTrackPos()/*(abs(cs.getAngle())/3.141)*/*abs(cs.getTrackPos());}

		char format[3]={':','+','='};
		ofstream outD5("lib.ki/debug.data/debug.steer",ios_base::app);
		outD5<<view<<format[0]<<track<<format[0]<<direction[view]<<format[0]<<steer<<format[0]<<stuck<<endl;
}



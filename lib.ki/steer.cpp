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
	int trackView=0;

	for(int i=0;i<16;i++){if((cs.getTrack(i)+cs.getTack(i+1)+cs.getTrack(i+2))>trackView){view=i+1;}}
	for(int i=0;i<16;i++){if (view==i){/*drive in view direction*/}}



	steer=(-1)*cs.getTrackPos()/*(abs(cs.getAngle())/3.141)*/*abs(cs.getTrackPos());
}



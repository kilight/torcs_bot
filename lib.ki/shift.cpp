/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::gear.cpp
		27.08.2011
*/
#include"shift.h"

/***  class shift_learn  ***/
shift_learn::shift_learn()
{	
	db test;
	db test2;
	test2.calcLaps();
	string temp="config.txt";
	// set_0(db);
	// set_1(db);
}
shift_learn::~shift_learn()
{}

/*void shift_object::set_1(Trainingsdatensatz)
{gear_y=db.getGear();}*/
/*void shift_object::set_1(Trainingsdatensatz)
{clutch=db.getClutch();}*/

/**   class shift_object learn.net   **/


/***  class shift_object  ***/
shift_object::shift_object()
{
}
shift_object::shift_object(CarState &cs)	// .net
{}
shift_object::~shift_object()
{}
/**   class shift_object set.argument  **/
void shift_object::set_0(CarState &cs)
{int gear_x=cs.getGear();}
void shift_object::set_1(CarState &cs)
{int rpm=cs.getRpm();}
void shift_object::set_2(void)
{rpm_puffer=rpm;}
void shift_object::set_3(CarState &cs)
{speed=int(sqrt(pow(2,cs.getSpeedX())+pow(2,cs.getSpeedY())));}
void shift_object::set_4(void)
{speed_puffer=speed;}
/**   class shift_object get.argument  **/
int shift_object::get_0(void)
{return gear_x;}
int shift_object::get_1(void)
{return rpm;}
int shift_object::get_2(void)
{return rpm_puffer;}
int shift_object::get_3(void)
{return speed;}
int shift_object::get_4(void)
{return speed_puffer;}


/**   class shift_object race.net   **/
int shift_object::race(CarState &cs)
{
	int gear_x=cs.getGear();
	int rpm=cs.getRpm();
	int speedX=cs.getSpeedX();

	int gearUp[6]={4000,5500,7000,8500,8500,0};
	int gearDown[6]={0,1000,2000,2000,5000,5000};
	
	char* buffer;
	long size;

	ifstream infile ("puffer.txt",ifstream::binary);
	infile.seekg(0,ifstream::end);	// get size of file
	size=infile.tellg();
	infile.seekg(0);
	buffer=new char [size];			// allocate memory for file content
	infile.read(buffer,size);		// read content of infile
	delete[] buffer;				// release dynamically-allocated memory
	infile.close();


	if(gear_x==0 || gear_x==-1){return 1;}
	
	if(char(speedX+100)-buffer[0]>0)
	{
		if(gear_x==1)
		{if(rpm>=4000){return gear_x+1;};}
		else if(gear_x==2)
		{if(rpm>=5500){return gear_x+1;};}
		else if(gear_x==3)
		{if(rpm>=7000){return gear_x+1;};}
		else if(gear_x==4)
		{if(rpm>=8500){return gear_x+1;};}
		else if(gear_x==5)
		{if(rpm>=8500){return gear_x+1;};}
		else if(gear_x==6)
		{if(rpm>=0){return gear_x+1;};}
		else{return gear_x;}
	}
	else
	{
		if(gear_x==2)
		{if(rpm<=1000){return gear_x-1;};}
		else if(gear_x==3)
		{if(rpm<=2000){return gear_x-1;};}
		else if(gear_x==4)
		{if(rpm<=2000){return gear_x-1;};}
		else if(gear_x==5)
		{if(rpm<=5000){return gear_x-1;};}
		else if(gear_x==6)
		{if(rpm<=5000){return gear_x-1;};}
		else{return gear_x;}
	}
	char tmp=char(rpm);
	ofstream outfile("puffer.txt",ofstream::binary);
	outfile.put(tmp);	// write to outfile
	outfile.close();
}
/*    class shift_object stolen.code    */
void shift_object::clutching(CarState &cs)
{
  double maxClutch=clutchMax;
  clutch=float(maxClutch);  
  if(clutch>0)						// Adjust the current value of the clutch
  {
    double delta=clutchDelta;
    if(cs.getGear()<2)				// Apply a stronger clutch output
	{								// when the gear is one and the
	  delta/=2;						// race is just started
      maxClutch*=clutchMaxModifier;
	  if(cs.getCurLapTime()<clutchMaxTime){clutch=float(maxClutch);}
	}
	clutch=float(min(maxClutch,double(clutch)));// check clutch is not bigger than maximum values
	if (clutch!=float(maxClutch))				// if clutch is not at max value
	{											// decreaseit quite quickly
	  clutch-=float(delta);
	  clutch=float(max(0.0,double(clutch)));
	}
	else{clutch-=clutchDec;}	// if clutch is at max value decrease it very slowly
  }
}

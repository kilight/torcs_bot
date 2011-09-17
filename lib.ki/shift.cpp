/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::shift.cpp
		27.08.2011
*/
#include"shift.h"
/***  class shift_object  ****
*****************************/
shift_object::shift_object(){}	
shift_object::shift_object(db* database)
{
	this->database=database;



	fstream data;
	data.open("../lib.ki/shift.miner",fstream::out|fstream::app);
	cout<<"Start example"<<endl;



	// alle sensordaten eines bots einer strecke in eine datei schreiben
	for(int i=0;i<database->getTracks()->size();i++)
	{                
		// rundenbetrachtung
		// das (* .... )[] braucht man, da die Funktion getLaps() einem einen Zeiger auf einen Array zurückliefert
		// die -1 am Ende ist wegen dem Start bei 0

                for(int j=0;j<(*database->getLaps())[i].size();j++)
		{
			for(int k=0;k<(*database->getLaps())[i][j].getNumPoints();k++)
			{
				// beispiel um das k-te Element zu speichern
				sensor* tmp;
				// getData() gibt einen Zeiger auf den Vektor zurück in dem Zeiger auf die Sensordaten gespeichert sind
				// da es ein Vektor ist geht hier [] aber wegen Zeiger => (* ... )
				tmp=(*(*database->getLaps())[i][j].getData())[k];
				slp_1(tmp->getRpm(),tmp->getGear());
			}
		}
	}
	data.close();
}
shift_object::~shift_object(){}
/**   class shift_object race.net   **
*************************************/
int shift_object::race(CarState &cs)
{
	int gear=cs.getGear();
	// read speedX from speed.miner
	// set to standart constructor if in use
	/***************************************/
	float speed_miner=0;
	ifstream inSpeedFile("lib.ki/speed.miner");
	inSpeedFile>>speed_miner;
	/***************************************/
	if(gear==0||gear==-1)
	{
		// write current speedX to speed.miner
		/*******************************************/
		ofstream outSpeedFile("lib.ki/speed.miner");
		outSpeedFile<<cs.getSpeedX();
		outSpeedFile.close();
		/*******************************************/		
		return 1;
	}
	if(cs.getSpeedX()>speed_miner)		// if faster
	{
		if(gear==1)
		{
			// read shift point from g1.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g1up.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()>=miner){return gear+1;}
			else{return gear;}
		}
		else if(gear==2)
		{
			// read shift point from g2.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g2up.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()>=miner){return gear+1;}
			else{return gear;}
		}
		else if(gear==3)
		{
			// read shift point from g3.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g3up.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()>=miner){return gear+1;}
			else{return gear;}
		}
		else if(gear==4)
		{
			// read shift point from g4.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g4up.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()>=miner){return gear+1;}
			else{return gear;}
		}
		else if(gear==5)
		{
			// read shift point from g2.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g5up.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()>=miner){return gear+1;}
			else{return gear;}
		}
		else if(gear==6)
		{
			// read shift point from g2.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g6up.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()>=miner){return gear+1;}
			else{return gear;}
		}
		else {}
	}
	else if(cs.getSpeedX()<speed_miner)		// if slower
	{
		if(gear==2)
		{
			// read shift point from g2.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g2do.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()<=miner){return gear-1;}
			else{return gear;}
		}
		else if(gear==3)
		{
			// read shift point from g3.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g3do.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()<=miner){return gear-1;}
			else{return gear;}
		}
		else if(gear==4)
		{
			// read shift point from g4.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g4do.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()<=miner){return gear-1;}
			else{return gear;}
		}
		else if(gear==5)
		{
			// read shift point from g5.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g5do.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()<=miner){return gear-1;}
			else{return gear;}
		}
		else if(gear==6)
		{
			// read shift point from g6.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g6do.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()<=miner){return gear-1;}
			else{return gear;}
		}
		else if(gear==7)
		{
			// read shift point from g7.miner
			// set to standart constructor if in use
			/***************************************/
			float miner=0;
			ifstream inMind("lib.ki/g7do.miner");
			inMind>>miner;
			/***************************************/
			// write current speedX to speed.miner
			/*******************************************/
			ofstream outSpeedFile("lib.ki/speed.miner");
			outSpeedFile<<cs.getSpeedX();
			outSpeedFile.close();
			/*******************************************/
			if(cs.getRpm()<=miner){return gear-1;}
			else{return gear;}
		}
		else{}
	}
}

int shift_object::tree(CarState &cs)
{	
	int gear=cs.getGear();
	int rpm=cs.getRpm();

	// read speedX and rpm from dataminer
	// set to standart constructor if in use
	/***************************************/
	float mind_speed=0;
	ifstream inSpeedFile("lib.ki/mind_speed.dat");
	inSpeedFile>>mind_speed;
	int mind_rpm;
	ifstream inRpmFile("lib.ki/mind_rpm.dat");
	inRpmFile>>mind_rpm;
	/***************************************/

	// reinforcement ansatz (logisch falsche stelle)
	/***********************************************
	if(rpm<mind_rpm){ increase shift point value }
	***********************************************/


	if(gear==0 || gear==-1){return 1;}
	
	// write current speedX and rpm to dataminer
	ofstream outSpeedFile("lib.ki/mind_speed.dat");
	outSpeedFile<<cs.getSpeedX();

	if(cs.getSpeedX()-mind_speed>0)
	{
		if(gear==1)
		{if(rpm>=4000){return gear+1;};}
		else if(gear==2)
		{if(rpm>=5500){return gear+1;};}
		else if(gear==3)
		{if(rpm>=7000){return gear+1;};}
		else if(gear==4)
		{if(rpm>=8500){return gear+1;};}
		else if(gear==5)
		{if(rpm>=8500){return gear+1;};}
		else if(gear==6)
		{if(rpm>=0){return gear+1;};}
		else{return gear;}
	}
	else
	{
		if(gear==2)
		{if(rpm<=1000){return gear-1;};}
		else if(gear==3)
		{if(rpm<=2000){return gear-1;};}
		else if(gear==4)
		{if(rpm<=4000){return gear-1;};}
		else if(gear==5)
		{if(rpm<=4000){return gear-1;};}
		else if(gear==6)
		{if(rpm<=5000){return gear-1;};}
		else{return gear;}
	}
}
int shift_object::simple_interpolation_racer(CarState& cs)
{
	float miner;
	ifstream inMind("lib.ki/si.miner");
	inMind>>miner;	
	return miner*cs.getRpm();	
}


/**   class shift_object learn.net   **
**************************************/
void shift_object::slp_1(float rpm,int gear)
{
	/****  single.layer.perceptron  ****/
	/***********************************
	if(t=0){if(mx<=Schwelle){m=m+x;}}
	if(t=1){if(mx>Schwelle){m=m-x;}}   */
}


void shift_object::simple_interpolation(float rpm,int gear)
{
	/****  simple.interpolation  ****/
	/********************************/
	float miner;
	ifstream inMind("lib.ki/si.miner");
	inMind>>miner;	

	if((miner*rpm-gear)<0)
	{
		miner=miner-1/(miner*rpm-gear);
		ofstream outMind("lib.ki/si.miner");
		outMind<<miner;
	}
	else if((miner*rpm-gear)>0)
	{
		miner=miner+1/(miner*rpm-gear);
		ofstream outMind("lib.ki/si.miner");
		outMind<<miner;
	}
	else{}	
}




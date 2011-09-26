/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::shift.cpp
		27.08.2011
*/
#include"shift.h"
/***  class shift_object  ****
*****************************/
shift_object::shift_object()
{
	// read shiftPoint argument from g*.miner
	// set to standart constructor if in use
	/***************************************/
	// read shift point upshifting
	ifstream g1up("lib.ki/shift.miner/g1up.miner");
	ifstream g2up("lib.ki/shift.miner/g2up.miner");
	ifstream g3up("lib.ki/shift.miner/g3up.miner");
	ifstream g4up("lib.ki/shift.miner/g4up.miner");
	ifstream g5up("lib.ki/shift.miner/g5up.miner");
	ifstream g6up("lib.ki/shift.miner/g6up.miner");
	g1up>>geUp[0];
	g2up>>geUp[1];
	g3up>>geUp[2];
	g4up>>geUp[3];
	g5up>>geUp[4];
	g6up>>geUp[5];
	g1up.close();
	g2up.close();
	g3up.close();
	g4up.close();
	g5up.close();
	g6up.close();
	/***************************************/
	// read shift point downshifting
	ifstream g2do("lib.ki/shift.miner/g2do.miner");
	ifstream g3do("lib.ki/shift.miner/g3do.miner");
	ifstream g4do("lib.ki/shift.miner/g4do.miner");
	ifstream g5do("lib.ki/shift.miner/g5do.miner");
	ifstream g6do("lib.ki/shift.miner/g6do.miner");
	ifstream g7do("lib.ki/shift.miner/g7do.miner");
	g2do>>geDo[0];
	g3do>>geDo[1];
	g4do>>geDo[2];
	g5do>>geDo[3];
	g6do>>geDo[4];
	g7do>>geDo[5];
	g2do.close();
	g3do.close();
	g4do.close();
	g5do.close();
	g6do.close();
	g7do.close();
	/***************************************/
	// read speedX from speed.miner
	// set to standart constructor if in use
	ifstream inSpeedFile("lib.ki/shift.miner/speed.miner");
	inSpeedFile>>speed;
	/***************************************/
	// read rpm from rpm.miner
	// set to standart constructor if in use
	ifstream inRpmFile("lib.ki/shift.miner/rpm.miner");
	inRpmFile>>rpm;
	/***************************************/
	// read gear from gear.miner
	// set to standart constructor if in use
	ifstream inGearFile("lib.ki/shift.miner/gear.miner");
	inGearFile>>gear;
	/***************************************/
}	
shift_object::~shift_object(){}
/*
shift_object::shift_object(db* database)
{
	this->database=database;
	net.generateNet();

	// alle tracks laden
	for(int i=0;i<database->getTracks()->size();i++)
	{                
		// rundenbetrachtung
		// das (* .... )[] braucht man, da die Funktion getLaps() einem einen Zeiger auf einen Array zurückliefert
		// die -1 am Ende ist wegen dem Start bei 0

                for(int j=0;j<(*database->getLaps())[i].size();j++)
		{

			net.setNumData((*database->getLaps())[i][j].getNumPoints());
			net.setNumInput(3);
			net.setOutput(1);			

			for(int k=0;k<(*database->getLaps())[i][j].getNumPoints();k++)
			{
				// beispiel um das k-te Element zu speichern
				sensor* tmp;
				// getData() gibt einen Zeiger auf den Vektor zurück in dem Zeiger auf die Sensordaten gespeichert sind
				// da es ein Vektor ist geht hier [] aber wegen Zeiger => (* ... )
				tmp=(*(*database->getLaps())[i][j].getData())[k];

				// Place Code here

				fann_type* input = new fann_type[3];
				fann_type* output = new fann_type[1];

				input[0] = (float) tmp->getRpm();
				input[1] = (float) tmp->getGear();
				input[2] = (float) tmp->getSpeedX();

				output[0] = (float) tmp->getGearCmd();

				net.saveInputFieldVector(input);
				net.saveOutputFieldVector(output);
			}
			net.inputTraindata();
			net.train();
		}
	}
}
*/

/**   class shift_object race.net   **
*************************************/
void shift_object::race(CarState &cs)
{
		// write reinforcement.miner
		/*******************************************/
		// write current gear to reinforcement.miner
		ofstream outGearFile("lib.ki/shift.miner/gear.miner");
		outGearFile<<cs.getGear();
		outGearFile.close();
		// write current rpm to reinforcement.miner
		/*******************************************/
		ofstream outRpmFile("lib.ki/shift.miner/rpm.miner");
		outRpmFile<<cs.getRpm();
		outRpmFile.close();
		/*******************************************/

	if(cs.getGear()==0||cs.getGear()==-1){gear=1;}		// start
	if(cs.getSpeedX()>=speed)				// faster
	{
		if(cs.getGear()==1){if(cs.getRpm()>=geUp[0]){gear=2;}}
		else if(cs.getGear()==2){if(cs.getRpm()>=geUp[1]){gear=3;}}
		else if(cs.getGear()==3){if(cs.getRpm()>=geUp[2]){gear=4;}}
		else if(cs.getGear()==4){if(cs.getRpm()>=geUp[3]){gear=5;}}
		else if(cs.getGear()==5){if(cs.getRpm()>=geUp[4]){gear=6;}}
		else if(cs.getGear()==6){if(cs.getRpm()>=geUp[5]){gear=7;}}
		else {}
	}
	else if(cs.getSpeedX()<speed)				// slower
	{
		if(cs.getGear()==2){if(cs.getRpm()<=geDo[0]){gear=1;}}
		else if(cs.getGear()==3){if(cs.getRpm()<=geDo[1]){gear=2;}}
		else if(cs.getGear()==4){if(cs.getRpm()<=geDo[2]){gear=3;}}
		else if(cs.getGear()==5){if(cs.getRpm()<=geDo[3]){gear=4;}}
		else if(cs.getGear()==6){if(cs.getRpm()<=geDo[4]){gear=5;}}
		else if(cs.getGear()==7){if(cs.getRpm()<=geDo[5]){gear=6;}}
		else {}		
	}
	else{}

		// write current speedX to speed.miner
		/*******************************************/
		ofstream outSpeedFile("lib.ki/shift.miner/speed.miner");
		outSpeedFile<<cs.getSpeedX();
		outSpeedFile.close();
		/*******************************************/
}
void shift_object::reinforcement(CarState &cs)
{
	if(cs.getGear()>gear)		// shiftup reinforcement
	{				// open g*.miner for reinforcement
					/***************************************/
					// write shift point upshifting
					ofstream g1up("lib.ki/shift.miner/g1up.miner");
					ofstream g2up("lib.ki/shift.miner/g2up.miner");
					ofstream g3up("lib.ki/shift.miner/g3up.miner");
					ofstream g4up("lib.ki/shift.miner/g4up.miner");
					ofstream g5up("lib.ki/shift.miner/g5up.miner");
					ofstream g6up("lib.ki/shift.miner/g6up.miner");
					/***************************************/

		float tmp=(cs.getRpm()-rpm)/10;
		if(cs.getSpeedX()<=speed)// langsamer geworden
		{			// erhöhe shift point um speed(neu)-speed(alt)
					// write shiftPoint argument to g*.miner
					/***************************************/
			if(cs.getGear()==1){geUp[0]+=tmp;g1up<<geUp[0];}
			else if(cs.getGear()==2){geUp[1]+=tmp;g2up<<geUp[1];}	
			else if(cs.getGear()==3){geUp[2]+=tmp;g3up<<geUp[2];}
			else if(cs.getGear()==4){geUp[3]+=tmp;g4up<<geUp[3];}
			else if(cs.getGear()==5){geUp[4]+=tmp;g5up<<geUp[4];}
			else if(cs.getGear()==6){geUp[5]+=tmp;g6up<<geUp[5];}
			else{}
		}
		else			// falls nicht langsamer geworden
		{			// reduziere shift point um speed(neu)-speed(alt)
					// write shiftPoint argument to g*.miner
					/***************************************/
			if(cs.getGear()==1){geUp[0]-=tmp;}	
			else if(cs.getGear()==2){geUp[1]-=tmp;g2up<<geUp[1];}	
			else if(cs.getGear()==3){geUp[2]-=tmp;g3up<<geUp[2];}
			else if(cs.getGear()==4){geUp[3]-=tmp;g4up<<geUp[3];}
			else if(cs.getGear()==5){geUp[4]-=tmp;g5up<<geUp[4];}
			else if(cs.getGear()==6){geUp[5]-=tmp;g6up<<geUp[5];}
			else{}		
		}
					// close g*.miner for style points
					/***************************************/
					g1up.close();
					g2up.close();
					g3up.close();
					g4up.close();
					g5up.close();
					g6up.close();
					/***************************************/
	}
	else if(cs.getGear()<gear)	// shiftdown reinforcement
	{				// write shiftPoint argument to g*.miner
					// set to standart constructor if in use
					/***************************************/
					// write shift point upshifting
					ofstream g2do("lib.ki/shift.miner/g2do.miner");
					ofstream g3do("lib.ki/shift.miner/g3do.miner");
					ofstream g4do("lib.ki/shift.miner/g4do.miner");
					ofstream g5do("lib.ki/shift.miner/g5do.miner");
					ofstream g6do("lib.ki/shift.miner/g6do.miner");
					ofstream g7do("lib.ki/shift.miner/g7do.miner");
					/***************************************/

		float tmp=(cs.getRpm()-rpm)/10;
		if(cs.getRpm()>rpm)	// höhere drehzahl
		{			// reduziere shift point um rpm(alt)-rpm(neu)
					// write shiftPoint argument to g*.miner
					/***************************************/
			if(cs.getGear()==2){geDo[0]-=tmp;g2do<<geDo[0];}	
			else if(cs.getGear()==3){geDo[1]-=tmp;g3do<<geDo[1];}
			else if(cs.getGear()==4){geDo[2]-=tmp;g4do<<geDo[2];}
			else if(cs.getGear()==5){geDo[3]-=tmp;g5do<<geDo[3];}
			else if(cs.getGear()==6){geDo[4]-=tmp;g6do<<geDo[4];}
			else if(cs.getGear()==7){geDo[5]-=tmp;g6do<<geDo[5];}
			else{}
		}
		else 			// niedrigere drehzahl
		{			// erhöhe shift point um rpm(alt)-rpm(neu)
					// write shiftPoint argument to g*.miner
					/***************************************/
			if(cs.getGear()==2){geDo[0]+=tmp;g2do<<geDo[0];}	
			else if(cs.getGear()==3){geDo[1]+=tmp;g3do<<geDo[1];}
			else if(cs.getGear()==4){geDo[2]+=tmp;g4do<<geDo[2];}
			else if(cs.getGear()==5){geDo[3]+=tmp;g5do<<geDo[3];}
			else if(cs.getGear()==6){geDo[4]+=tmp;g6do<<geDo[4];}
			else if(cs.getGear()==7){geDo[5]+=tmp;g6do<<geDo[5];}
			else{}
		}
					// close g*.miner for style points
					/***************************************/
					g2do.close();
					g3do.close();
					g4do.close();
					g5do.close();
					g6do.close();
					g7do.close();
					/***************************************/
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
	if(gear==0 || gear==-1){return 1;}

	// write current speedX and rpm to dataminer
	/*******************************************/
	ofstream outSpeedFile("lib.ki/mind_speed.dat");
	outSpeedFile<<cs.getSpeedX();

	if(cs.getSpeedX()-mind_speed>0)
	{
		if(gear==1)	{if(rpm>=4000){return gear+1;};}
		else if(gear==2){if(rpm>=5500){return gear+1;};}
		else if(gear==3){if(rpm>=7000){return gear+1;};}
		else if(gear==4){if(rpm>=8500){return gear+1;};}
		else if(gear==5){if(rpm>=8500){return gear+1;};}
		else if(gear==6){if(rpm>=9000){return gear+1;};}
		else{return gear;}
	}
	else
	{
		if(gear==1)	{if(rpm>=8000){return gear+1;};}
		else if(gear==2){if(rpm<=1000){return gear-1;};}
		else if(gear==3){if(rpm<=2000){return gear-1;};}
		else if(gear==4){if(rpm<=4000){return gear-1;};}
		else if(gear==5){if(rpm<=4000){return gear-1;};}
		else if(gear==6){if(rpm<=5000){return gear-1;};}
		else if(gear==7){if(rpm<=6000){return gear-1;};}
		else{return gear;}
	}
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




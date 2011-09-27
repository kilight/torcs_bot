/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::drive.cpp
		10.09.2011
*/
#include"drive.h"

/***  class drive_object  ****
*****************************/
drive_object::drive_object(){
	net.destroy();
	net.create_from_file("./lib.ki/net.miner/torcs.drive.net");
}
	
drive_object::drive_object(db* database)
{
	this->database=database;
	net.destroy();
	net.generateNet();
}

void drive_object::learnFromDatabase()
{
	
	for(int i=0;i<database->getTracks()->size();i++)	// alle tracks laden
	{                
		for(int j=0;j<1;j++)
		{

			cout << "Lap Nr. " << j+1 << endl;

			net.setNumData((*database->getLaps())[i][j].getNumPoints());
			net.setNumInput(num_inputs);
			net.setNumOut(num_outputs);

			fann_type** output = new fann_type*[net.getNumData()];
			fann_type** input = new fann_type*[net.getNumData()];			
			fann_type* inputvec;
			fann_type* outputvec;

			for(int k=0;k<(*database->getLaps())[i][j].getNumPoints();k++)
			{
				// beispiel um das k-te Element zu speichern
				
				sensor* tmp;
					
				tmp=(*(*database->getLaps())[i][j].getData())[k];
				
				inputvec = new fann_type[num_inputs];
				outputvec = new fann_type[num_outputs];

			
				input[k] = inputvec;
				output[k] = outputvec;
			}
			cout << "lap complete" << endl;
			net.inputTraindata(input,output);
			net.train();
		}
	}
}

void drive_object::learnFromDataFolder() 
{
	file data("./data/");
	data.setName("data.input.output_1");
	data.open();
	
	sensor s;
	int numPoints = 0;
	while(!data.eof() && (s.getDistFromStart() != -10.0 && s.getCurLapTime() != -10.0)) 
	{
		s = data.fetchNextData();
		numPoints++;
	}
	
	cout << "numPoints in file: " << numPoints << endl;

	net.setNumData(numPoints);
	net.setNumInput(num_inputs);
	net.setNumOut(num_outputs);

	fann_type** output = new fann_type*[net.getNumData()];
	fann_type** input = new fann_type*[net.getNumData()];
			
	fann_type* inputvec;
	fann_type* outputvec;

	data.close();
	data.open();
	data.setPosition(ios::beg);

	int countPointsFetched = 0;
	for(int k=0;k < numPoints;k++)
	{	
		s=data.fetchNextData();
		countPointsFetched++;
		
		inputvec = new fann_type[num_inputs];
		outputvec = new fann_type[num_outputs];

		float wheelSpinDifv=abs(s.getWheelSpinVel(0)-s.getWheelSpinVel(1));
		float wheelSpinDifh=abs(s.getWheelSpinVel(2)-s.getWheelSpinVel(3));

	inputvec[0]=s.getAngle();
	// inputvec[1]=s.getTrackPos();
	// inputvec[2]=s.getSpeedX();
	// inputvec[3]=s.getSpeedY();	

	string X="+";
	string Y=" steer value ";
	ofstream outD1("lib.ki/debug.data/debug.learn.steer",ios_base::app);
	outD1<<inputvec[0]<<X<<inputvec[1]<<X<<inputvec[2]<<X<<inputvec[3]<<Y<<s.getSteer()<<endl;

	outputvec[0]=s.getSteer()*0.785398;

		/* accel brake 
		inputvec[0]=wheelSpinDifv/5+wheelSpinDifh;
		inputvec[1]=s.getTrack(8)+s.getTrack(9)+s.getTrack(10);

		inputvec[2]=(s.getTrack(13))+(s.getTrack(14))+(s.getTrack(15)*(-1));
		inputvec[3]=s.getTrack(13)+s.getTrack(14)+s.getTrack(15);

		// inputvec[3]=1;
		// inputvec[4]=1;

		outputvec[0]=s.getAccel();
		outputvec[1]=s.getBrake();
	
*/		input[k] = inputvec;
		output[k] = outputvec;
	}
	cout << "lap complete" << endl;
	net.inputTraindata(input,output);
	net.train();
	data.close();
}

drive_object::~drive_object(){}

void drive_object::race(CarState &cs) 
{
		float wheelSpinDifv=abs(cs.getWheelSpinVel(0)-cs.getWheelSpinVel(1));
		float wheelSpinDifh=abs(cs.getWheelSpinVel(2)-cs.getWheelSpinVel(3));

		float t0=(cs.getTrack(8)+cs.getTrack(9)+cs.getTrack(10));
		float t1=(cs.getTrack(13)+cs.getTrack(14)+cs.getTrack(15));
		float t2=(cs.getTrack(5)+cs.getTrack(4)+cs.getTrack(3));

	if(wheelSpinDifh < 3)
	{
		accel=exp(-2.5f*(float)pow(wheelSpinDifv/5+wheelSpinDifh,2))*(1-abs(cs.getTrackPos()))*(3.141-abs(cs.getAngle()))/3.141;
		if(t0 > 450)
			accel = 1;
		brake=0;
	}

	else if(t0 < 350)
	{
		brake=(-1)*exp(-0.01f*pow(wheelSpinDifh,2))+1;
		if(t0 < 250 && brake < 0.6 && cs.getSpeedX() > 100)
			brake += 0.4;
		if(t0 < 150 && brake < 0.8 && cs.getSpeedX() > 80)
			brake += 0.2;
		accel=0;

	}
	else {accel=0,brake=0;}
	if(cs.getSpeedX()<20){accel=1,brake=0;}
	if(cs.getTrackPos() > 1 || cs.getTrackPos() < -1) {accel *= 0.5;}


		char format[3]={':','+','='};
		ofstream outD5("lib.ki/debug.data/debug.send.race",ios_base::app);
		outD5<<cs.getCurLapTime()<<format[0]<<wheelSpinDifh<<format[1]<<t0<<format[1]<<endl
		     <<t1<<format[1]<<t0<<format[2]<<accel<<endl;

		/*float track[19];
		for(int i=0;i<19;i++){track[i]=cs.getTrack(i);}*/

		/*string middle="straight forward: ";
		string lookLeft="look left: ";
		string lookRigth="look right: ";
		ofstream outD1("lib.ki/debug.data/debug.track.steer",ios_base::app);
		outD1<<middle<<track[9]<<endl<<lookLeft;
		for(int i=0;i<9;i++){track[i]=cs.getTrack(i);outD1<<track[i]<<format;}
		outD1<<endl<<lookRigth;
		for(int i=10;i<19;i++){track[i]=cs.getTrack(i);outD1<<track[i]<<format;}
		outD1<<accel<<format<<brake<<endl;
		outD1.close();*/
}
void drive_object::race_ki(CarState &cs)
{
	fann_type* input = new fann_type[num_inputs];
	fann_type* output = new fann_type[num_outputs];	

	if(cs.getSpeedX()<10){accel=0.75f;}

		float wheelSpinDifv=abs(cs.getWheelSpinVel(0)-cs.getWheelSpinVel(1));
		float wheelSpinDifh=abs(cs.getWheelSpinVel(2)-cs.getWheelSpinVel(3));

		float track_mitte=(cs.getTrack(8)+cs.getTrack(9)+cs.getTrack(10));
		float track_rechts=(cs.getTrack(13)+cs.getTrack(14)+cs.getTrack(15));
		float track_links=(cs.getTrack(5)+cs.getTrack(4)+cs.getTrack(3));

	input[0]=cs.getAngle();
	// input[1]=cs.getTrackPos();
	// input[2]=cs.getSpeedX();
	// input[3]=cs.getSpeedY();	
	
	output=net.run(input);
	steer=output[0]*0.785398;

	string X="+";
	string Y=" steer value ";
	ofstream outD1("lib.ki/debug.data/debug.race.steer",ios_base::app);
	outD1<<input[0]<<X<<input[1]<<X<<input[2]<<X<<input[3]<<Y<<steer<<endl;

	/* accel.brake 
	input[0]=wheelSpinDifv/5+wheelSpinDifh;
	input[1]=t0;
	input[2]=(cs.getTrack(13))+(cs.getTrack(14))+(cs.getTrack(15)*(-1));
	input[3]=cs.getTrack(13)+cs.getTrack(14)+cs.getTrack(15);

	output=net.run(input);
	accel=output[0];
	steer=output[1]; */
}





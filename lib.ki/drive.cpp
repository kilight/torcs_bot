/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::drive.cpp
		10.09.2011
*/
#include"drive.h"

/***  class drive_object  ****
*****************************/
drive_object::drive_object(){
	net.destroy();
	net.create_from_file("torcs.net");
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
	data.setName("data.input.output");
	data.open();
	
	sensor s;
	int numPoints = 0;
	while(!data.eof() && (s.getDistFromStart() != -10.0 && s.getCurLapTime() != -10.0)) {
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

		inputvec[0]=wheelSpinDifh;
		outputvec[0]=s.getAccel();
	
		input[k] = inputvec;
		output[k] = outputvec;
	}
	cout << "lap complete" << endl;
	net.inputTraindata(input,output);
	net.train();

}

drive_object::~drive_object(){}

void drive_object::race(CarState &cs) 
{
	// fann_type* input = new fann_type[num_inputs];
	// fann_type* output = new fann_type[num_outputs];	

		float wheelSpinDifv=abs(cs.getWheelSpinVel(0)-cs.getWheelSpinVel(1));
		float wheelSpinDifh=abs(cs.getWheelSpinVel(2)-cs.getWheelSpinVel(3));

	if(wheelSpinDifh<2){accel=(float) exp(-5*(float)pow(wheelSpinDifh,2)),brake=0;}
	else if(wheelSpinDifh>3) {brake=(float) -1*exp(-0.001f*(float)pow(wheelSpinDifh,2))+1,accel=0;}
	else{accel=0,brake=0;}
	if(cs.getSpeedX()<40){accel=1,brake=0;}

		char format=' ';
		char equal='=';
		ofstream outD5("lib.ki/debug.data/debug.send.race",ios_base::app);
		outD5<<cs.getCurLapTime()<<format<<wheelSpinDifh<<equal<<accel<<endl;
		outD5.close();

		float track[19];
		for(int i=0;i<19;i++){track[i]=cs.getTrack(i);}

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

	float wheelSpinDifv=abs(cs.getWheelSpinVel(0)-cs.getWheelSpinVel(1));
	float wheelSpinDifh=abs(cs.getWheelSpinVel(2)-cs.getWheelSpinVel(3));

	input[0]=wheelSpinDifh;
	output=net.run(input);
	accel=output[0];
}





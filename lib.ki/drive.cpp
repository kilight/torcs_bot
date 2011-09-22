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
	// alle tracks laden
	for(int i=0;i<database->getTracks()->size();i++)
	//for(int i=0;i<1;i++)
	{                
		// rundenbetrachtung
		// das (* .... )[] braucht man, da die Funktion getLaps() einem einen Zeiger auf einen Array zurückliefert
		// die -1 am Ende ist wegen dem Start bei 0

                //for(int j=0;j<(*database->getLaps())[i].size();j++)
		int j = 0;
		for(int z=0;z<5;z++)
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
				// getData() gibt einen Zeiger auf den Vektor zurück in dem Zeiger auf die Sensordaten gespeichert sind
				// da es ein Vektor ist geht hier [] aber wegen Zeiger => (* ... )
					
				tmp=(*(*database->getLaps())[i][j].getData())[k];
				
				inputvec = new fann_type[num_inputs];
				outputvec = new fann_type[num_outputs];

				if(tmp->getAngle() < 0) {
					inputvec[0]=(float) tmp->getAngle() / -1*2;
				}
				else {
					inputvec[0]=tmp->getAngle() / 2 + 0.5f;
				}
				inputvec[1]=(float) tmp->getSpeedX() / 300;
				inputvec[2]=(float) tmp->getSpeedY() / 200;
				if(tmp->getTrackPos() < 0) {
					inputvec[3]=(float) tmp->getTrackPos() / -3;
				}
				else {
					inputvec[3]=tmp->getTrackPos() / 3 + 0.5f;
				}
				for(int i=0;i<19;i++){ inputvec[i+4]=(float) tmp->getTrack(i) / 200; }
				inputvec[23]=(float) tmp->getRpm() / 8000;
				for(int i=0;i<4;i++){ inputvec[i+24]=(float) tmp->getWheelSpinVel(i) / 300; }

				if(tmp->getBrake() == 0) {
					if(tmp->getAccel() == 1) {
						outputvec[0] = 0.5f + tmp->getAccel() / 2;
						outputvec[0] -= 0.00001;
					}
					else {
						outputvec[0] = 0.5f + tmp->getAccel() / 2;
					}
				}
				else {
					outputvec[0] = tmp->getBrake() / 2;
				}
				if(tmp->getSteer() == 1) {
					outputvec[1]=(float) tmp->getSteer();
					outputvec[1] -= 0.00001;
				}
				else {
					if(tmp->getSteer() == 0) {
						outputvec[1]=(float) tmp->getSteer();
						outputvec[1] += 0.00001;
					}
				}
				// cout << "data vector " << k << "are put in the training data now" << endl;
				//net.saveInputFieldVector(input);
				//net.saveOutputFieldVector(output);
				input[k] = inputvec;
				output[k] = outputvec;
			}
			cout << "lap complete" << endl;
			net.inputTraindata(input,output);
			net.train();
/*			for(int i = 0; i < (*database->getLaps())[i][j].getNumPoints(); i++) {
				delete input[i];
				delete output[i];
			}
			delete input;
			delete output; */
		}
	}
}

void drive_object::learnFromDataFolder() 
{
	
		
	file data("./data/data.input.output");
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
		// beispiel um das k-te Element zu speichern
					
		s = data.fetchNextData();
		countPointsFetched++;
		
		inputvec = new fann_type[num_inputs];
		outputvec = new fann_type[num_outputs];

		if(s.getAngle() < 0) {
			inputvec[0]=(float) s.getAngle() / -1*2;
		}
		else {
			inputvec[0]=s.getAngle() / 2 + 0.5f;
		}
		inputvec[1]=(float) s.getSpeedX() / 300;
		inputvec[2]=(float) s.getSpeedY() / 200;
		if(s.getTrackPos() < 0) {
			inputvec[3]=(float) s.getTrackPos() / -3;
		}
		else {
			inputvec[3]=s.getTrackPos() / 3 + 0.5f;
		}
		for(int i=0;i<19;i++){ inputvec[i+4]=(float) s.getTrack(i) / 200; }
			inputvec[23]=(float) s.getRpm() / 8000;
			for(int i=0;i<4;i++){ inputvec[i+24]=(float) s.getWheelSpinVel(i) / 300; }

			if(s.getBrake() == 0) {
				if(s.getAccel() == 1) {
					outputvec[0] = 0.5f + s.getAccel() / 2;
					outputvec[0] -= 0.00001;
				}
				else {
					outputvec[0] = 0.5f + s.getAccel() / 2;
				}
			}
			else {
				outputvec[0] = s.getBrake() / 2;
			}
			if(s.getSteer() == 1) {
				outputvec[1]=(float) s.getSteer();
				outputvec[1] -= 0.00001;
			}
			else {
				if(s.getSteer() == 0) {
					outputvec[1]=(float) s.getSteer();
					outputvec[1] += 0.00001;
				}
			}
		// cout << "data vector " << k << "are put in the training data now" << endl;
		//net.saveInputFieldVector(input);
		//net.saveOutputFieldVector(output);
		input[k] = inputvec;
		output[k] = outputvec;
	}
	
	data.close();
	cout << "Points fetched for neural network: " << countPointsFetched << endl;
	cout << "lap complete" << endl;
	net.inputTraindata(input,output);
	net.train();
/*			for(int i = 0; i < (*database->getLaps())[i][j].getNumPoints(); i++) {
				delete input[i];
				delete output[i];
			}
			delete input;
			delete output; */
}


drive_object::~drive_object()
{
	
}

int drive_object::race(CarState &cs) {		// common racing interface
	fann_type* input = new fann_type[num_inputs];
	fann_type* output = new fann_type[num_outputs];	
	if(cs.getAngle() < 0) {
		input[0]=(float) cs.getAngle() / -1*2;
	}
	else {
		input[0]=cs.getAngle() / 2 + 0.5f;
	}
	input[1] = cs.getSpeedX() / 300;
	input[2] = cs.getSpeedY() / 200;
	if(cs.getTrackPos() < 0) {
		input[3]=cs.getTrackPos() / -3;
	}
	else {
		input[3]=cs.getTrackPos() / 3 + 0.5f;
	}
	for(int i = 0; i < 19; i++) {
		input[i+4] = cs.getTrack(i) / 200;
	}
	input[23]=(float) cs.getRpm() / 8000;
	for(int i=0;i<4;i++) {
		input[i+24]=(float) cs.getWheelSpinVel(i) / 300; 
	}


	output = net.run(input);
	if(output[0] > 0.5f) {
		accel = 2* (output[0] - 0.5f);
		brake = 0;
	}
	else {	
		brake = 2* output[1];
		accel = 0;
	}
	steer = output[2];
}

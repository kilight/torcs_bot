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
	net.generateNet();

	// alle tracks laden
	//for(int i=0;i<database->getTracks()->size();i++)
	for(int i=0;i<1;i++)
	{                
		// rundenbetrachtung
		// das (* .... )[] braucht man, da die Funktion getLaps() einem einen Zeiger auf einen Array zurückliefert
		// die -1 am Ende ist wegen dem Start bei 0

                //for(int j=0;j<(*database->getLaps())[i].size();j++)
		for(int j=0;j<10;j++)
		{

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

				inputvec[0]=(float) tmp->getAngle();
				inputvec[1]=(float) tmp->getSpeedX();
				inputvec[2]=(float) tmp->getSpeedY();
				inputvec[3]=(float) tmp->getTrackPos();
				// for(int i=0;i<19;i++){inputvec[i+4]=(float) tmp->getTrack(i);}

				outputvec[0]=(float) tmp->getAccel();
				outputvec[1]=(float) tmp->getBrake();
				outputvec[2]=(float) tmp->getSteer();
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
drive_object::~drive_object()
{
	
	
	
}

int drive_object::race(CarState &cs) {		// common racing interface
	fann_type* input = new fann_type[num_inputs];
	fann_type* output = new fann_type[num_outputs];	
	input[0] = cs.getAngle();
	input[1] = cs.getSpeedX();
	input[2] = cs.getSpeedY();
	input[3] = cs.getTrackPos();

	output = net.run(input);
	accel = output[0];
	brake = output[1];
	steer = output[2];
}

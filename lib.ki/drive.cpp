/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::drive.cpp
		10.09.2011
*/
#include"drive.h"

/***  class drive_object  ****
*****************************/
drive_object::drive_object(){}	
drive_object::drive_object(db* database)
{
	this->database=database;
	net.generateNet();

	// alle tracks laden
	for(int i=0;i<1;i++)
	{                
		// rundenbetrachtung
		// das (* .... )[] braucht man, da die Funktion getLaps() einem einen Zeiger auf einen Array zurückliefert
		// die -1 am Ende ist wegen dem Start bei 0

                for(int j=0;j<10;j++)
		{

			net.setNumData((*database->getLaps())[i][j].getNumPoints());
			net.setNumInput(22);
			net.setNumOut(3);			

			for(int k=0;k<(*database->getLaps())[i][j].getNumPoints();k++)
			{
				// beispiel um das k-te Element zu speichern
				sensor* tmp;
				// getData() gibt einen Zeiger auf den Vektor zurück in dem Zeiger auf die Sensordaten gespeichert sind
				// da es ein Vektor ist geht hier [] aber wegen Zeiger => (* ... )
				tmp=(*(*database->getLaps())[i][j].getData())[k];

				fann_type* input = new fann_type[22];
				fann_type* output = new fann_type[3];

				input[0]=(float) tmp->getAngle();
				input[1]=(float) tmp->getSpeedX();
				input[2]=(float) tmp->getSpeedY();
				input[3]=(float) tmp->getTrackPos();
				for(int i=0;i<19;i++){input[i+4]=(float) tmp->getTrack(i);}

				output[0]=(float) tmp->getAccel();
				output[1]=(float) tmp->getBrake();
				output[2]=(float) tmp->getSteer();

				net.saveInputFieldVector(input);
				net.saveOutputFieldVector(output);
			}
			net.inputTraindata();
			net.train();
		}
	}
}
drive_object::~drive_object(){}

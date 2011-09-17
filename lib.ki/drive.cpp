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



	fstream data;
	data.open("../lib.ki/drive.miner",fstream::out|fstream::app);
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

				// Place Code here

			}
		}
	}
	data.close();
}
drive_object::~drive_object(){}

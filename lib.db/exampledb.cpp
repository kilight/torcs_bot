/* example for a database application */

#include "exampledb.h"

using namespace std;

exampledb::exampledb() {
	
	
}

exampledb::exampledb(db* database) {
	this->database = database;
	
}

exampledb::~exampledb() {
	
	
}

void exampledb::start() {
	int input;
	do {
		cout << "Start example" << endl;
		cout << "1. test files" << endl;
		cout << "2. test data transfer" << endl;
		cout << "3. test lap files" << endl;
		cout << "0. quit" << endl;		
		cin >> input;
		if(input == 1) {
			this->testFiles();
		}
		if(input == 2) {
			this->testDataTransfer();
		}
		if(input == 3) {
			this->testLapFiles();
		}

	} while(input != 0);
}

void exampledb::testFiles() {
	cout << "existing files:" << endl;	
	for(int i = 0; i < database->getFiles()->size(); i++) {		
		cout << (*database->getFiles())[i].getPath() << (*database->getFiles())[i].getName() << endl;
	}

}

void exampledb::testLapFiles() {
	cout << "existing files in the laps:" << endl;
	cout << "there are " << database->getLaps()->size() << " vectors of laps in db.laps" << endl;
	for(int i = 0; i < database->getLaps()->size(); i++) {
		cout << "there are " << (*database->getLaps())[i].size() << " laps in db.laps[" << i << "]" << endl;
		for(int j = 0; j < (*database->getLaps())[i].size(); j++) {
			cout << ((*database->getLaps())[i][j]).getFileLink()->getPath() << ((*database->getLaps())[i][j]).getFileLink()->getName() << endl;
		}
	}

}

void exampledb::testDataTransfer() {	
	// für jeden track einmal die schleife ausführen
	cout << "num tracks " << database->getTracks()->size() << endl;
	for(int i = 0; i < database->getTracks()->size(); i++) {
		
		// nun durchlaufen wir die einzelnen Runden der Strecke
		// das (* .... )[ ] braucht man, da die Funktion getLaps() einem einen Zeiger auf einen Array zurückliefert
		// die -1 am Ende ist wegen dem Start bei 0
		
		cout << "num runs for track nr. " << i << ": " << (*database->getLaps())[i].size() << endl;
 
		for(int j = 0; j < (*database->getLaps())[i].size(); j++) {
			
			// nun sollen in jeder Runde alle Sensordaten rausgeschrieben werden
			// also greifen wir nun auf die einzelnen Runden zu
			
			cout << "num of points in run nr. " << j << ": " << (*database->getLaps())[i][j].getNumPoints() << endl;
			// cout << (*database->getLaps())[i * database->getNumBots() + bot - 1]
			
			for(int k = 0; k < (*database->getLaps())[i][j].getNumPoints(); k++) {
				
				// Beispiel um das kte Element zu speichern
				sensor* Bsp;
				
				// getData() gibt einen Zeiger auf den Vektor zurück in dem Zeiger auf die Sensordaten gespeichert sind
				// da es ein Vektor ist geht hier [ ] aber wegen Zeiger => (* ... )
				Bsp = (* (*database->getLaps())[i][j].getData() )[k];
				
				// nun wollen wir die 19 Sensortrackdaten rausschreiben:
				for(int l = 0; l < 19; l++) {
					// für das lte Trackdatum muss man die getTrack Methode so aufrufen:
					float datum = Bsp->getTrack(l);
					
					// nun ab in die Datei
//					cout << datum << " ";
					
				}
				
//				cout << "accel: " << Bsp->getAccel() << " steer: " << Bsp->getSteer() << endl;
				
				// eine Runde ist durch, also ein endl
//				cout << endl;
			}
			(*database->getLaps())[i][j].clearData();
			
		}
	}
}

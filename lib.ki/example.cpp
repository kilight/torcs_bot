/* example for a database application */

#include "example.h"

using namespace std;

example::example() {
	
	
}

example::example(db* database) {
	this->database = database;
	
}

example::~example() {
	
	
}

void example::start() {
	fstream datei;
	datei.open("/home/mobile/ai/tracksensoren.txt", fstream::out | fstream::app);
	
	
	cout << "Start example" << endl;
	// alle sensordaten vom bot in eine datei schreiben
	
	// für jeden track einmal die schleife ausführen
	for(int i = 0; i < database->getTracks()->size(); i++) {
		
		// nun durchlaufen wir die einzelnen Runden der Strecke
		// das (* .... )[ ] braucht man, da die Funktion getLaps() einem einen Zeiger auf einen Array zurückliefert
		// die -1 am Ende ist wegen dem Start bei 0
		
		for(int j = 0; j < (*database->getLaps())[i].size(); j++) {
			
			// nun sollen in jeder Runde alle Sensordaten rausgeschrieben werden
			// also greifen wir nun auf die einzelnen Runden zu
			
			cout << (*database->getLaps())[i].size() << endl;
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
					datei << datum << " ";
					
				}
				
				cout << "accel: " << Bsp->getAccel() << " steer: " << Bsp->getSteer() << endl;
				
				// eine Runde ist durch, also ein endl
				datei << endl;
			}
			
		}
	}
	datei.close();
}

/*	Database Interface methods for AI Light Torcs project
	author: Robin Lehmann
	date: 06.09.2011
*/

#include "dbinterface.h"

using namespace std;

dbi::dbi() {
	base = NULL;
}

dbi::dbi(db database) {
	base = &database;
}

// interface functions, if no feasable solution was found NULL is returned
	// hier siehst du wie man an die daten kommt. ist relativ kompliziert aber ich versuchs mal zu erklären:
	
	// test2.getTracks()->size()
	// mit getTracks kriegt man einen Zeiger auf ein vector<track> Objekt.
	// Vektoren haben die Funktion size() die die Anzahl der Objekte darin wieder gibt.
	// mehr Funktionen gibts auch im Internet.
	// mit (*(test2.getTracks())) greift man auf den Vektor zu. Der funktioniert eigentlich wie ein Array, also geht auch []
	// (*(test2.getTracks()))[k] so z.b. Nun ist man bei dem k-ten track in den geladenen Tracks angekommen.
	
	// track hat wiederum Funktionen, welche steht in track.h
	// für db etc stehen immer die Funktionen die es gibt in den .h Dateien.
	// was die dann machen kann dir eigentlich wumpe sein, ich hoffe die namen sind einigermaßen selbsterklärend.
	
	// tmp = test2.getFastest((*(test2.getTracks()))[k].getName());
	// hier habe ich dann die Funktion getFastest aufgerufen und dazu den kten Tracknamen verwendet,
	// d.h. es werden nun die schnellsten 3 runden des kten Tracks geladen

	// vector< lap* >* tmp; <=> tmp ist hier ein zeiger auf die schnellsten Runden.
	// wieder kann man die Anzahl der Elemente mit size abchecken um eine schleife zu bauen

	// for(int j = 0; j < (*tmp)[i]->getData()->size(); j++)
	// die schleife hier läuft nun über die Daten der einzelnen schnellsten Runden.
	// (*(*tmp)[i]->getData())[j] das Konstrukt hier steht für den Zugriff auf die Daten eines Sensor Objektes
	// welche funktionen es gibt steht wieder in sensor.h, ist etwas unaufgeräumt, da ich das von torcs kopiert hab.
	// das ist der punkt an dem du dir dann alles abholen kannst.
	
	// sind halt viele pointer etc, damit die vielen daten nicht unnötig kopiert werden.

lap** dbi::fastestLaps() {
	if (base == NULL)
		return NULL;
	
	int numLaps = 0;
	
	vector< lap* >* fastest;
	for(int i = 0; i < base->getTracks()->size(); i++) {
		fastest = base->getFastest((*(base->getTracks()))[i].getName());
		numLaps += fastest->size();
	}
	
	lap** result = new lap*[numLaps];
	
	for(int i = 0; i < base->getTracks()->size(); i++) {
		fastest = base->getFastest((*(base->getTracks()))[i].getName());
		for(int j = 0; j < fastest->size(); j++) {
			result[i * base->getTracks()->size() + j] = (*fastest)[j];
		}
	}
	
	return result;
}

lap** dbi::fastestLap(track* tTrack) {
	if (base == NULL || tTrack == NULL)
		return NULL;

	int numLaps = 0;
	
	vector< lap* >* fastest;
	fastest = base->getFastest(tTrack->getName());
	
	lap** result = new lap*[numLaps];
	
	for(int j = 0; j < fastest->size(); j++) {
		result[j] = (*fastest)[j];
	}
	
	return result;	
}
	
/*lap** dbi::getLatestLaps() {
	if (base == NULL)
		return NULL;
	
}

lap** dbi::getLatestLaps(bot* tBot) {
	if (base == NULL)
		return NULL;
		
}*/
	
sensor** dbi::getLapData(lap* tLap) {
	if (base == NULL || tLap == NULL)
		return NULL;
		
	sensor** result = new sensor*[tLap->getData()->size()];
	
	for(int i = 0; i < tLap->getData()->size(); i++) {
		result[i] = (*(tLap->getData()))[i];
	}
	
	return result;
}

sensor** dbi::getTimespanData(lap* tLap, float start, float end) {
	if (base == NULL || tLap == NULL)
		return NULL;	
	if ( start >= end )
		return NULL;
	
	return getWayspanData(tLap, start/6, end/6);
}

sensor** dbi::getWayspanData(lap* tLap, int start, int end) {
	if (base == NULL || tLap == NULL)
		return NULL;

	if ( start >= end || start < 0 || end > tLap->getData()->size())
		return NULL;
	
	sensor** result = new sensor*[end - start];

	for(int i = 0; i < end - start; i++) {
		result[i] = (*(tLap->getData()))[start + i];
	}
	
	return result;	
}

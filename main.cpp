#include "db.h"

int main() {
	
	db test;
	db test2("/home/lehmannr/ai/testdata/");
	//db test2("/media/data/log/");
	test2.calcFastestLaps();
	string temp = "/home/lehmannr/ai/config.txt";
	// test2.dbsave(tmp);
	
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

	vector< lap* >* tmp;
	for(int k = 0; k < test2.getTracks()->size(); k++) {
		tmp = test2.getFastest((*(test2.getTracks()))[k].getName());
		
		for(int i = 0; i < tmp->size(); i++) {
			for(int j = 0; j < (*tmp)[i]->getData()->size(); j++) {
				//cout << (*(*tmp)[i]->getData())[j].toString() << endl;
			}
		}
	}
	return 0;
}
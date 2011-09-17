/*	Database class for AI Light Torcs project
	author: Robin Lehmann
	date: 10.08.2011
*/

#include <map>
#include <string>
#include <vector>
#include "bot.h"
#include "track.h"
#include "file.h"
#include "lap.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#ifndef dbclass
#define dbclass

class db {
	public:
		db();
		db(string location);
		~db();
		
		bool dbrestore(string storeLocation); // Restore a dbsave configuration
		bool dbsave(string storeLocation);     // create a dbsave configuration to map the db data on disk
	
		bool insertBot(bot botinsert, file* fileinsert, bool fileadd);
		bool insertTrack(track trackinsert, file* fileinsert, bool fileadd);
	
		vector< track >* getTracks() { return &tracks; }
//		vector< bot >* getBots() { return &bots; }
//		vector< vector<int> >* getBotmap() { return &botmap; }
		vector< vector<int> >* getTrackmap() { return &trackmap; }
	
		vector< vector<lap> >* getLaps() {
			return &laps;
		}
		
		int getNumbots() { return this->numbots; }
		int getNumtracks() { return this->numtracks; }
		void calcLaps();
		void restoreDbaddLaps();
		void getBotsTracksFiles();
	
	private:
		bool restoreFastest(string trackname);
		bool loadFastestSensors(string trackname);
	
		void saveLap(lap* toSave);
		void findSmallestFiles();
	
		string savedir;
		string location;
		int numbots;
		int numtracks;
		vector<vector<int> > botmap;
		vector<vector<int> > trackmap;
		vector< bot > bots;
		vector< track > tracks;
		vector< vector< lap > > laps;
		vector< file > files;
};

#endif

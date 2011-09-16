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
		
		bool dbrestore(string storeLocation); // Restore a dbsave configuration
		bool dbsave(string storeLocation);     // create a dbsave configuration to map the db data on disk
	
		bool insertBot(bot botinsert, file* fileinsert, bool fileadd);
		bool insertTrack(track trackinsert, file* fileinsert, bool fileadd);
	
	private:
		int numbots;
		int numtracks;
		vector<vector< int> > botmap;
		vector<vector<int> > trackmap;
		vector< bot > bots;
		vector< track > tracks;
		vector< vector< lap > > laps;
		vector< file > files;
};

#endif
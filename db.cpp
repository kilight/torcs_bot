/*	Database methods for AI Light Torcs project
	author: Robin Lehmann
	date: 10.08.2011
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "db.h"

using namespace std;

db::db() {
	this->numbots = 0;
	this->numtracks = 0;
}

db::~db() {
	for( int i = 0; i < botmap.size(); i++) {
		botmap[i].clear();
	}
	botmap.clear();
	for( int i = 0; i < trackmap.size(); i++) {
		trackmap[i].clear();
	}
	trackmap.clear();
	bots.clear();
	tracks.clear();
	for( int i = 0; i < laps.size(); i++) {
		laps[i].clear();
	}
	laps.clear();
	files.clear();
	fastestLap.clear();
}

db::db(string location) {
//	system("ls /home/lehmannr/ai/testdata/ > /home/lehmannr/ai/files.txt");
	string tmp = "ls " + location;
	tmp += " > /home/lehmannr/ai/files.txt";
	
	system(tmp.c_str());
	
	fstream filelist;
	filelist.open("/home/lehmannr/ai/files.txt", fstream::in);
	
	if(filelist.fail())
	{
	  cout << "Error: Unable to open " << location << "files.txt.\n";
	}
	
	// Read the files.txt and analyze each file using the algorithm to create the files
	// figure out the number of tracks and bots and save them in the database instance
	
	lap* fill = new lap();
	fill->setSize(10000000.00);
	fastestLap.push_back(fill);
	fill = new lap();
	fill->setSize(10000000.00);
	fastestLap.push_back(fill);
	fill = new lap();
	fill->setSize(10000000.00);
	fastestLap.push_back(fill);
	
	while(!filelist.eof()) {
		char filename[256];
		filelist.getline(filename,256);
		
		// parse the name and set the mode if there is a ,xyz, then find the text until the next , and repeat
		
		/* filename creating code:
		if(filename[index].str() == "") { 
			filename[index] << "/home/work01/log/";
			filename[index] << ",bot," << s->cars[index]->_name << ",";
			filename[index] << ",track," << ReInfo->track->name << ",";
			filename[index] << ",laps," << s->cars[index]->_remainingLaps << ",";
			filename[index] << ",time," << stamp[index].tv_sec << "," << stamp[index].tv_usec << ",";
		}
		*/
	
		
		string botname = "";
		string trackname = "";
		string text = "";
		int laps = 0;
		int i = 0;
  		
		if(filename[i] < 32)
			break;
		if(filename[i] != ',')
			break;
		
		// parse the filename for the botname
		i++;
		for(; filename[i] != ','; i++) {}
		i++;
		for(; filename[i] != ','; i++) {
			text += filename[i];
		}
		botname = text;

		// parse the filename for the trackname
		text = "";
		i++;
		i++;
		for(; filename[i] != ','; i++) {}
		i++;
		for(; filename[i] != ','; i++) {
			text += filename[i];
		}
		trackname = text;
		
	
		// parse the filename for the number of laps
		text = "";
		i++;
		i++;
		for(; filename[i] != ','; i++) {}
		i++;
		for(; filename[i] != ','; i++) {
			text += filename[i];
		}
		laps = atoi(text.c_str());
		
		// create bot, track and file to insert into the db
		
		bot insertBot;
		insertBot.setName(botname);
	
		track insertTrack;
		insertTrack.setName(trackname);

		file* insertFile = new file(location);
		insertFile->setName(filename);
		insertFile->calcSize();

		cout << "inserted bot: " << botname << endl;
		
		this->insertBot(insertBot, insertFile, true);

		cout << " and track: " << trackname << endl;
		
		this->insertTrack(insertTrack, insertFile, false);

	}
	
	
	/*
	
	*/
	
	numbots = bots.size();
	numtracks = tracks.size();

	/* for(int i = 0; i < tracks.size(); i++) {
	
		string tmp = "ls *" + tracks[i].getName();
		tmp += "* > /home/lehmannr/ai/track";
		tmp << tracks[i].getName() << i; 
	} */	
}

void db::calcFastestLaps() {
	// analyze the files to create the lap linklist and remember the data in tracks
	for(int k = 0; k < trackmap.size(); k++) {
		for(int i = 0; i < trackmap[k].size(); i++) {
			
			// open file
			files[trackmap[k][i]].open();
			
			// fetch data until the start of lap 1 is reached
			
			int prestartOffset = 0;
			double temp = 0;
			for(sensor s = files[trackmap[k][i]].fetchNextData(); temp <= 0; prestartOffset++) {
				s = files[trackmap[k][i]].fetchNextData();
				temp = s.getCurLapTime();
			}
			
			// first find the size of the first lap

			sensor s2;
			int dataPoints = 0;
			int num = 0;
			
			lap * tmplap = new lap();
			tmplap->setPosInRun(num + 1);
			tmplap->setPosInPoints(prestartOffset);
			tmplap->setPosInFile(files[trackmap[k][i]].getPos());
			tmplap->setFile(trackmap[k][i]);

			for(sensor s = s2; 1 == 1 ; dataPoints++) {					
				s = files[trackmap[k][i]].fetchNextData();
				if (s.getCurLapTime() < s2.getCurLapTime() && s.getDistFromStart() < s2.getDistFromStart()) {
					tmplap->setLength(s2.getDistFromStart());				
					s2 = s;
					dataPoints++;
					cout << "lap " << num << " finished." << endl;
					break;
				}
				s2 = s;
			}

			tmplap->setSize(files[trackmap[k][i]].getPos() - tmplap->getPosInFile());
			tmplap->setNumPoints(dataPoints);
			
			saveLap(tmplap);

			// now determine how many laps there are in the file and where the laps start in relation to the file start
			
			// vector< lap > lapsInFile;			
			

			float fastest = tmplap->getLength();
			float longest = tmplap->getLength();
			int approximateSizePerPoint = tmplap->getSize() / tmplap->getNumPoints();
			
			for(int j = prestartOffset + dataPoints; files[trackmap[k][i]].getPos() < files[trackmap[k][i]].getSize() ; num++) {
			
				// create a new lap and set its starting position relative to the file
				lap * templap = new lap();
				templap->setPosInRun(num + 1);
				templap->setPosInPoints(j);
				templap->setPosInFile(files[trackmap[k][i]].getPos());
				templap->setFile(trackmap[k][i]);
				
				// determine the length of the lap
				
				if(files[trackmap[k][i]].getPos() + fastest > files[trackmap[k][i]].getSize()) {
					templap->setSize(files[trackmap[k][i]].getSize() - templap->getPosInFile());
					
					// calculate the number of dataPoints in the current lap via the time difference of the first to the last sensor value
					
					files[trackmap[k][i]].setPosition(templap->getPosInFile());
					sensor tmp = files[trackmap[k][i]].fetchNextData();
										
					files[trackmap[k][i]].setPosition(files[trackmap[k][i]].getSize() - 5 * approximateSizePerPoint);
					sensor tmp2 = files[trackmap[k][i]].fetchNextData();				
					
					templap->setNumPoints(dataPoints);
					
				}
				
				templap->setSize(files[trackmap[k][i]].getPos() - templap->getPosInFile());				
				templap->setNumPoints(dataPoints);
				
				//cout << "NumPoints " << dataPoints << " in lap " << num << " of track " << tracks[k].getName() << " in file " << files[trackmap[k][i]].getName() << endl;
				
				if(templap->getNumPoints() < fastestLap[0]->getNumPoints()) {
					delete fastestLap[2];
					fastestLap[2] = fastestLap[1];
					fastestLap[1] = fastestLap[0];
					fastestLap[0] = templap;
				}
				else {
					if(templap->getNumPoints() < fastestLap[1]->getNumPoints()) {
						delete fastestLap[2];
						fastestLap[2] = fastestLap[1];
						fastestLap[1] = templap;					
					}
					else {
						if(templap->getNumPoints() < fastestLap[2]->getNumPoints()) {
							delete fastestLap[2];
							fastestLap[2] = templap;
						}
						else {
							delete templap;
						}
					}
				}
				// lapsInFile.push_back(*tmplap);
				j += dataPoints;
			}
			// this->laps.push_back(lapsInFile);
			// files[i].setNumlaps(lapsInFile.size());
			
			// close file
			files[trackmap[k][i]].close();
		}
		
		fstream savefile;
		savefile.open(tracks[k].getName().c_str(), fstream::out);
		
		savefile << fastestLap.size() << endl;
		for(int i = 0; i < fastestLap.size(); i++) {
			savefile << fastestLap[i]->getPosInFile() << endl;
			savefile << fastestLap[i]->getPosInRun() << endl;
			savefile << fastestLap[i]->getLength() << endl;
			savefile << fastestLap[i]->getNumPoints() << endl;
			savefile << fastestLap[i]->getPosInPoints() << endl;
			savefile << fastestLap[i]->getSize() << endl;
			savefile << fastestLap[i]->getFile() << endl;
		}
		
		fastestLap.clear();
	}
}	

bool db::restoreFastest(string trackname) {
	fstream savefile;
	
	char t[500];
	int index = -1;
	for(int i = 0; i < tracks.size(); i++) {
		if(tracks[i].getName() == trackname) {
			index = i;
			//cout << "found " << trackname << " index " << index << endl;
		}
	}
	
	if(index == -1)
		return false;
	savefile.open(tracks[index].getName().c_str(), fstream::in);
	if(savefile.fail()) {
		cout << "Trackfile not found for track: " << trackname << endl;
		return false;
	}
	savefile.getline(t, 500, '\n');
	int limit = atoi(t);
	lap* iLaps;
	
	//cout << "starting to restore" << endl;
	for(int i = 0; i < limit; i++) {
		iLaps = new lap();
		savefile.getline(t, 500, '\n'); 
		iLaps->setPosInFile(atoi(t));
		savefile.getline(t, 500, '\n');
		iLaps->setPosInRun(atoi(t));
		savefile.getline(t, 500, '\n'); 
		iLaps->setLength(atof(t));
		savefile.getline(t, 500, '\n'); 
		iLaps->setNumPoints(atoi(t));
		savefile.getline(t, 500, '\n'); 
		iLaps->setPosInPoints(atoi(t));
		savefile.getline(t, 500, '\n'); 
		iLaps->setSize(atoi(t));
		savefile.getline(t, 500, '\n'); 
		iLaps->setFile(atoi(t));
		
		//cout << "restored: " << iLaps->getPosInFile() << " " << iLaps->getFile() << endl;
		fastestLap[i] = iLaps;
	}	
	return true;
}

bool db::dbrestore(string storeLocation) {
	// open the file at storeLocation and load the data into the datastructures, order is determined by db::dbsave

	fstream savefile;
	savefile.open(storeLocation.c_str(), fstream::in);
	
	char t[500];
	
	savefile.getline(t, 500, '\n');
	numbots = atoi(t);
	savefile.getline(t, 500, '\n'); 
	numtracks = atoi(t);
	
	savefile.getline(t, 500, '\n');
	int limit = atoi(t);
	
	bot insertBot;
	for(int i = 0; i < limit; i++) {
		savefile.getline(t, 500, '\n'); 
		insertBot.setName(t);
		savefile.getline(t, 500, '\n'); 
		insertBot.setRating(atof(t));
		bots.push_back(insertBot);
	}
	

	savefile.getline(t, 500, '\n');
	limit = atoi(t);
	
	track insertTrack;
	pair<string, int> blap;
	
	for(int i = 0; i < limit; i++) {
		savefile.getline(t, 500, '\n'); 
		insertTrack.setName(t);
		savefile.getline(t, 500, '\n');
		blap.first = t;
		savefile.getline(t, 500, '\n'); 
		blap.second = atoi(t);
		insertTrack.setBestLap(blap);
		tracks.push_back(insertTrack);
	}
	
	savefile.getline(t, 500, '\n');
	limit = atoi(t);	
	lap iLaps;
	
	for(int i = 0; i < limit; i++) {
		savefile.getline(t, 500, '\n'); 		
		int limit2 = atoi(t);		
		for(int j = 0; j < limit2; j++) {
			savefile.getline(t, 500, '\n'); 
			iLaps.setPosInFile(atoi(t));
			savefile.getline(t, 500, '\n');
			iLaps.setPosInRun(atoi(t));
			savefile.getline(t, 500, '\n'); 
			iLaps.setLength(atof(t));
			savefile.getline(t, 500, '\n'); 
			iLaps.setNumPoints(atoi(t));
			savefile.getline(t, 500, '\n'); 
			iLaps.setPosInPoints(atoi(t));
			savefile.getline(t, 500, '\n'); 
			iLaps.setSize(atoi(t));
			laps[i].push_back(iLaps);
		}
	}

	savefile.getline(t, 500, '\n');
	limit = atoi(t);
	file iFile;
	
	for(int i = 0; i < limit; i++) {
		savefile.getline(t, 500, '\n'); 
		iFile.setName(t);
		savefile.getline(t, 500, '\n'); 
		iFile.setNumlaps(atoi(t));
		savefile.getline(t, 500, '\n'); 
		iFile.setSize(atoi(t));
		files.push_back(iFile);
	}	
	
	savefile.getline(t, 500, '\n');
	limit = atoi(t);
	
	for(int i = 0; i < limit; i++) {
		savefile.getline(t, 500, '\n');
		int limit2 = atoi(t);
		for(int j = 0; j < limit2; j++) {
			savefile.getline(t, 500, '\n'); 
			botmap[i].push_back(atoi(t));
		}
	}

	savefile.getline(t, 500, '\n');
	limit = atoi(t);

	for(int i = 0; i < limit; i++) {
		savefile.getline(t, 500, '\n');
		int limit2 = atoi(t);		
		for(int j = 0; j < limit2; j++) {
			savefile.getline(t, 500, '\n'); 
			trackmap[i].push_back(atoi(t));
		}
	}
	return true;
	
}

bool db::dbsave(string storeLocation) {
	// save the datastructures to the file specified in storeLocation
	
	fstream savefile;
	savefile.open(storeLocation.c_str(), fstream::out);
	
	savefile << numbots << endl;
	savefile << numtracks << endl;
	
	savefile << bots.size() << endl;
	for(int i = 0; i < bots.size(); i++) {
		savefile << bots[i].getName() << endl;
		savefile << bots[i].getRating() << endl;
	}
	
	savefile << tracks.size() << endl;		
	for(int i = 0; i < tracks.size(); i++) {
		savefile << tracks[i].getName() << endl;
		savefile << tracks[i].getBestLap().first << endl;
		savefile << tracks[i].getBestLap().second << endl;
	}
	
	savefile << laps.size() << endl;
	for(int i = 0; i < laps.size(); i++) {
		savefile << laps[i].size() << endl;
		for(int j = 0; j < laps[i].size(); j++) {
			savefile << laps[i][j].getPosInFile() << endl;
			savefile << laps[i][j].getPosInRun() << endl;
			savefile << laps[i][j].getLength() << endl;
			savefile << laps[i][j].getNumPoints() << endl;
			savefile << laps[i][j].getPosInPoints() << endl;
			savefile << laps[i][j].getSize() << endl;
		}
	}

	savefile << files.size() << endl;
	for(int i = 0; i < files.size(); i++) {
		savefile << files[i].getName() << endl;
		savefile << files[i].getNumlaps() << endl;
		savefile << files[i].getSize() << endl;
	}	

	savefile << botmap.size() << endl;
	for(int i = 0; i < botmap.size(); i++) {
		savefile << botmap[i].size()  << endl;
		for(int j = 0; j < botmap[i].size(); j++) {
			savefile << botmap[i][j] << endl;
		}
	}
	
	savefile << trackmap.size() << endl;	
	for(int i = 0; i < trackmap.size(); i++) {
		savefile << trackmap[i].size()  << endl;
		for(int j = 0; j < trackmap[i].size(); j++) {
			savefile << trackmap[i][j] << endl;
		}
	}

	return true;
}

bool db::insertBot(bot botinsert, file* fileinsert, bool fileadd = false) {
	
	
	if(fileadd) {
		
		// check if the file has been added already
		for(int i = 0; i < files.size(); i++) {
			if (files[i].getName() == fileinsert->getName())
				return false;
		}
		// add bot and file to their corresponding vectors
		this->files.push_back(*fileinsert);
	}
		
	bool botadd = true;
	for(int i = 0; i < bots.size(); i++) {
		if (bots[i].getName() == botinsert.getName())
			botadd = false;
	}
	
	if (botadd) {
		this->bots.push_back(botinsert);
	}
	
	// if the bot doesnt exist in the map, a new vector for the files has to be created
	vector<int> botFilelist;
	botFilelist.push_back(files.size() - 1);
	// create a new mapentry for the bot
	if(botmap.size() < bots.size()) {
		botmap.push_back(botFilelist);
	}
	// if there has been an entry, we add the new file to the filevector
	else {
		botmap[bots.size() - 1].push_back(files.size());
	}
	
	return true;
}

bool db::insertTrack(track trackinsert, file* fileinsert, bool fileadd = false) {
	
	int fileIndex = -1;
	// check if the file has been added already
	for(int i = 0; i < files.size(); i++) {
		if(files[i].getName() == fileinsert->getName()) {
			fileIndex = i;
		}
	}
		
	// add track and file to their corresponding vectors
	if(fileadd) {
		if(fileIndex != -1) 
			return false;
		this->files.push_back(*fileinsert);
	}
	
	if(fileIndex == -1)
		return false;
	
	bool trackadd = true;
	int trackIndex = -1;
	for(int i = 0; i < tracks.size(); i++) {
		if(tracks[i].getName() == trackinsert.getName()) {
			trackadd = false;
			trackIndex = i;
		}
	}
	
	if (trackadd) {
		this->tracks.push_back(trackinsert);
	}
	
	// if the bot doesnt exist in the map, a new vector for the files has to be created
	vector<int> trackFilelist;
	trackFilelist.push_back(fileIndex);
	
	// create a new mapentry for the track

	if(trackadd) {
		//cout << "Trackmapentry for: " << trackinsert.getName() << " and file " << fileinsert->getName() << endl;
		trackmap.push_back(trackFilelist);
	}	
	
	// if there has been an entry, we add the new file to the filevector
	else {
		//cout << "Trackmap push in " << trackIndex << " for: " << trackinsert.getName() << " and file " << fileinsert->getName()  << " with id " << fileIndex << endl;
		trackmap[trackIndex].push_back(fileIndex);
	}
	
	return true;
}

bool db::loadFastestSensors(string trackname) {
	
	//cout << fastestLap.size() << endl;
	for(int i = 0; i < fastestLap.size(); i++) {
		//cout << fastestLap[i]->getNumPoints() << endl;
		//cout << fastestLap[i]->getPosInFile() << endl;
		files[fastestLap[i]->getFile()].open();
		sensor** s = files[fastestLap[i]->getFile()].fetchData(fastestLap[i]->getNumPoints(), fastestLap[i]->getPosInFile());
		files[fastestLap[i]->getFile()].close();
		for(int j = 0; j < fastestLap[i]->getNumPoints(); j++) {
			fastestLap[i]->getData()->push_back(s[j]);
		}
		delete s;
	}

	return true;
}

void db::saveLap(lap* toSave) {
	
}

void db::findSmallestFiles() {

	// find the smallest files for each track and save the data

	fstream smallestTracks;
	smallestTracks.open("/home/lehmannr/ai/stracks.txt", fstream::out);
			
	for(int i = 0; i < tracks.size(); i++) {
		pair<int, int>* trackSizes = new pair<int, int> [trackmap[i].size()];
	
		for(int j = 0; j < trackmap[i].size(); j++) {
			trackSizes[j].first = files[trackmap[i][j]].getSize();
			trackSizes[j].second = trackmap[i][j];
		}
		
		// bubble sort
		
		int n = trackmap[i].size();
		bool vertauscht;
		do {
			vertauscht = false;
			for(int j = 0; j < n - 1; j++) {
				if(trackSizes[j].first > trackSizes[j+1].first) {
					pair<int, int> tmp = trackSizes[j];
					trackSizes[j] = trackSizes[j+1];
					trackSizes[j+1] = tmp;
					vertauscht = true;
				}
			}
			n--;
		} while (vertauscht && n > 1);
		
		// write 7 smallest filesizes in a file
		
		smallestTracks << tracks[i].getName() << endl;
		for(int j = 0; j < 7; j++) {

			smallestTracks << files[trackSizes[j].second].getName() << endl;
			smallestTracks << trackSizes[j].first << endl;
			
			/*
			// copy those files in a seperate directory
	
			string tmp = "cp /media/data/log/\"" + files[trackSizes[j].second].getName() + "\"";
			tmp += " /media/data/fastest/";
			system(tmp.c_str());
			*/
		}
		smallestTracks << endl;
		smallestTracks << endl;
	}
	
	smallestTracks.close();	
}
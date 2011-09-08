/*	Database Interface class for AI Light Torcs project
	author: Robin Lehmann
	date: 06.09.2011
*/

#include "db.h"

using namespace std;

#ifndef dbiclass
#define dbiclass

class dbi {
	public:
		dbi();
		dbi(db database);
	
		// interface functions, if no feasable solution was found NULL is returned
	
		lap** fastestLaps();
		lap** fastestLap(track* tTrack);
	
/*		lap** getLatestLaps();
		lap** getLatestLaps(bot* tBot); */
	
		sensor** getLapData(lap* tLap);
		sensor** getTimespanData(lap* tLap, float start, float end);
		sensor** getWayspanData(lap* tLap, int start, int end);
	
		void setBase(db* base) {
			this->base = base;
		}
		
		db* getBase() {
			return this->base;
		}
			
	private:
	
		db* base;
};

#endif
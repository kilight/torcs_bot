/*	Track class for AI Light Torcs project
	author: Robin Lehmann
	date: 10.08.2011
*/

#ifndef trackclass
#define trackclass

#include <string>

using namespace std;

class track{
	public:
		track();
	
		void setName(string name) { this->name = name; }
		string getName() { return this->name; }
		
		void setBestLap(pair <string, int> bestLap) { this->bestLap = bestLap; }
		pair <string, int> getBestLap() { return this->bestLap; }
	
	private:
		string name;
		pair<string, int> bestLap;
};

#endif
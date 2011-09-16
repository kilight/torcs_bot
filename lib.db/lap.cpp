/*	Lap class for AI Light Torcs project
	author: Robin Lehmann
	date: 13.08.2011
*/

#include "lap.h"

lap::lap() {

}

vector<sensor* >* lap::getData() {
	// load the sensor data from file if its not in the memory
	
	if(data.size() == 0) {
		filelink.open();
		sensor** s = filelink.fetchData(numPoints, posInFile);
		filelink.close();
		for(int j = 0; j < numPoints; j++) {
			data.push_back(s[j]);
		}
		delete s;
	}
	
	return &data;
}
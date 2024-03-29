/*	File class for AI Light Torcs project
	author: Robin Lehmann
	date: 10.08.2011
*/

#ifndef fileclass
#define fileclass

#include <string>
#include <sstream>
#include "sensor2.h"
#include <fstream>

using namespace std;

class file{
	public:
		file();
		file(string location);
		~file() {}
	
		void setName(string name) { this->name = name; }
		string getName() { return this->name; }
		
		void calcSize();
		void setSize(int size) { this->size = size; }
		int getSize() { if (size != 0)
						return this->size;
					else {
						calcSize();
						return this->size;
					}
				}
		
		void setNumlaps(int numlaps) { this->numlaps = numlaps; }
		int getNumlaps() { return this->numlaps; }

		void setPath(string path) { this->path = path; }
		string getPath() { return this->path; }

		int getLastread() { return this->lastread; }
		
		sensor fetchNextData();
		sensor** fetchData(int num);
		sensor** fetchData(int num, int pos);
		
		int getPos();
		void setPosition(int pos);

		bool eof();
		
		void open();
		void close();

	private:
		string name;
		int numlaps;
		int size;
		int linesRead;
		string path;
		int lastread;
		bool op;
		fstream* filestream;
//		lap** laps;
};

#endif

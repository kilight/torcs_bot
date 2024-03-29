/*	Lap class for AI Light Torcs project
	author: Robin Lehmann
	date: 10.08.2011
*/

#ifndef lapclass
#define lapclass

#include "sensor2.h"
#include "file.h"
#include <vector>

class lap{
	public:
		lap();
		~lap() {
			if(data.size() != 0) {
				for( int i = 0; i < data.size(); i++) {
					delete data[i];
				}
			}
			data.clear();
		}

                void setPosInFile ( int posInFile ) { this->posInFile = posInFile; }
                int getPosInFile() { return this->posInFile; }

                void setData ( vector< sensor* > data ) { this->data = data; }
                vector< sensor* >* getData();
		
		void clearData() { 
			if(data.size() != 0) {
				for( int i = 0; i < data.size(); i++) {
					delete data[i];
				}
			}
			data.clear();
		}

                void setPosInRun ( int posInRun ) { this->posInRun = posInRun; }
                int getPosInRun() { return this->posInRun; }

                void setLength ( double length ) { this->length = length; }
                double getLength() { return this->length; }

                void setNumPoints ( int numPoints ) { this->numPoints = numPoints; }
                int getNumPoints() { return this->numPoints; }

                void setPosInPoints ( int posInPoints ) { this->posInPoints = posInPoints; }
                int getPosInPoints() { return this->posInPoints; }

		void setSize ( int size ) { this->size = size; }
		int getSize () { return this->size; }

		void setFile (int ifile) { this->iFile = ifile; }
		int getFile () { return iFile; }
		
		void setFileLink (file filelink) { this->filelink = filelink; }
		file* getFileLink() { return &filelink; } 
	
	private:
		int posInFile;
		vector< sensor* > data;
		file filelink;
		int posInRun;
		double length;
		int numPoints;
		int posInPoints;
		int size;
		int iFile;
};

#endif

/*	File class for AI Light Torcs project
	author: Robin Lehmann
	date: 13.08.2011
*/

#include "file.h"

file::file() {
	linesRead = 0;
	numlaps = 0;
	size = 0;
	name = "";
	path = "/home/lehmannr/ai/testdata/";
	lastread = 0;
	op = false;
	this->filestream = new fstream();
}

file::file(string location) {
	linesRead = 0;
	numlaps = 0;
	size = 0;
	name = "";
	lastread = 0;
	op = false;
	this->filestream = new fstream();	
	path = location;
}

void file::calcSize() {
	// determine size
	open();
	filestream->seekg(0, ios::end);
	this->setSize(filestream->tellg());
	close();
}

void file::open() {
	if(op || filestream->is_open())
		return;
	else {		
		string temp = path + name;
		cout << "attempting to open file (with path): " << temp << endl;
		this->filestream->open(temp.c_str(), fstream::in);
		if(filestream->fail()) {
			cout << "cannot open file " << name << endl;
			throw "Could not open file" + name;
		}
		cout << "file " << name << " opened." << endl;
		op = true;
	}
}

void file::close() {
	if(!op || !(filestream->is_open()))
		return;
	else {
		cout << "file " << name << " closed." << endl;		
		this->filestream->close();
		op = false;
	}
}

sensor file::fetchNextData() {
	filestream->seekg(linesRead);
	sensor retval;
	char s[1000];
	stringstream ss;
	filestream->getline(s, 1000, '\n');
	linesRead = filestream->tellg();
	ss << s;
	retval = sensor(ss.str());
	if(filestream->eof()) {
		cout << "reached eof" << endl;
		retval.setDistFromStart(-10.0);
		retval.setCurLapTime(-10.0);
	}
	return retval;
}

void file::setPosition(int pos) {
	filestream->clear();
	linesRead = pos;
	filestream->seekg(pos);
}

sensor** file::fetchData(int num) {
	filestream->seekg(linesRead);
	sensor** retval = new sensor*[num];
	char s[1000];
	sensor* tmp;
	for(int i = 0; i < num; i++) {
		stringstream ss;
		filestream->getline(s, 1000, '\n');
		linesRead = filestream->tellg();
		ss << s;
		tmp = new sensor(ss.str());
		if(filestream->eof()) {
			tmp->setDistFromStart(-10.0);
			tmp->setCurLapTime(-10.0);
		}
		retval[i] = tmp;
	}
	return retval;
}

sensor** file::fetchData(int num, int pos) {
	filestream->seekg(pos);
	sensor** retval = new sensor*[num];
	char* s;
	sensor* tmp;
//	cout << "fetching " << num << " points from postition " << pos << endl; 
	for(int i = 0; i < num; i++) {
		stringstream ss;
		s = new char[1000];		
		filestream->getline(s, 1000, '\n');
		linesRead = filestream->tellg();
//		cout << "linesRead: " << linesRead << endl;
		ss << s;
		delete s;
//		cout << "line " << i << " from file " << name << endl;
//		cout << ss.str() << endl << endl;
		tmp = new sensor(ss.str());
//		cout << "sensor from that line: " << tmp->toString() << endl << endl;
		if(filestream->eof()) {
			tmp->setDistFromStart(-10.0);
			tmp->setCurLapTime(-10.0);
		}
		retval[i] = tmp;
	}
	return retval;
}

int file::getPos() {
	return linesRead;
}

bool file::eof() {
	//open();
	bool retval = false;
	if (filestream->is_open())
		retval = filestream->eof();
	//close();
	return retval;
}

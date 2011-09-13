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
		this->filestream->open(temp.c_str(), fstream::in);
		cout << "file " << name << " opened." << endl;
		if(filestream->fail()) {
			cout << "cannot open file " << name << endl;
		}
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
		retval.setDistFromStart(-10.0);
		retval.setCurLapTime(-10.0);
	}
	return retval;
}

void file::setPosition(int pos) {
	filestream->seekg(pos);
}

sensor** file::fetchData(int num) {
	filestream->seekg(linesRead);
	sensor** retval = new sensor*[num];
	char s[1000];
	sensor* tmp;
	stringstream ss;
	for(int i = 0; i < num; i++) {
		filestream->getline(s, 1000, '\n');
		linesRead = filestream->tellg();
		ss << s;
		tmp = new sensor(ss.str());
		if(filestream->eof()) {
			tmp->setDistFromStart(-10.0);
			tmp->setCurLapTime(-10.0);
		}
		retval[i] = tmp;
		ss.flush();
	}
	return retval;
}

sensor** file::fetchData(int num, int pos) {
	filestream->seekg(pos);
	sensor** retval = new sensor*[num];
	char s[1000];
	stringstream ss;
	sensor* tmp;
	for(int i = 0; i < num; i++) {
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

int file::getPos() {
	return linesRead;
}

bool file::eof() {
	open();
	bool retval = filestream->eof();
	close();
	return retval;
}

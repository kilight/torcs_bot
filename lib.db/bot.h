/*	Roboter class for AI Light Torcs project
	author: Robin Lehmann
	date: 10.08.2011
*/

#ifndef botclass
#define botclass

#include <string>

using namespace std;

class bot{
	public:
		bot();
		
		void setName(string name) { this->name = name; }
		string getName() { return name; }
		
		void setRating(double rating) { this->rating = rating; }
		double getRating() { return rating; }
	
	private:
		string name;
		double rating;
		
};

#endif
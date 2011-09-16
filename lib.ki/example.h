/* example fo a database application */

#include "db.h"

class example {
	public:
	
	example();
	example(db* database);
	~example();
	
	void start();
	
	private:
		
	db* database;
	
};
/* example fo a database application */

#include "../lib.db/db.h"

class exampledb {
	public:
	
	exampledb();
	exampledb(db* database);
	~exampledb();
	
	void testFiles();
	void testDataTransfer();
	void testLapFiles();
	void start();
	
	private:
		
	db* database;
	
};

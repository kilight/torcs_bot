/* neuronal network class for the torcs bot */

#include "../lib.fann/include/floatfann.h"
#include "../lib.fann/include/fann_cpp.h"
#include "../lib.db/sensor2.h"

#include <ios>
#include <iostream>
#include <iomanip>

using namespace std;


const float learning_rate = 0.7f;
const unsigned int num_layers = 3;
const unsigned int num_input = 2;
const unsigned int num_hidden = 3;
const unsigned int num_output = 1;
const float desired_error = 0.001f;
const unsigned int max_iterations = 300000;
const unsigned int iterations_between_reports = 1000;

class fann_net {
public:
	fann_net();
	~fann_net();
	void menu();
//	void sensor2Float(vector< sensor* >* data);
	void saveInputFieldVector(fann_type* data);
	void saveOutputFieldVector(fann_type* data);
	void inputTraindata();
	void generateNet();
	void train();
	void setNumData(int numData) { this->numData = numData; }
	int getNumData() { return this->numData; }

	void setNumInput(int numIn) { this->numIn = numIn; }
	int getNumInpute() { return this->numIn; }
	
	void setNumOut(int numOut) { this->numOut = numOut; }
	int getNumOut() { return this->numOut; }

private:
	fann_type** input;
	fann_type** output;

	int numIn;
	int numOut;
	int numData;

	int insertedIn;
	int insertedOut;

	FANN::training_data data;
	FANN::neural_net net;
};

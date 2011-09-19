/* neuronal network class for the torcs bot */

#include "../lib.fann/include/floatfann.h"
#include "../lib.fann/include/fann_cpp.h"
#include "../lib.db/sensor2.h"

#include <ios>
#include <iostream>
#include <iomanip>

using namespace std;

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

	void setNetParameters(float learning_rate, unsigned int num_layers, unsigned int num_input, 
		unsigned int num_hidden, unsigned int num_output, float desired_error, 
		unsigned int max_iterations, unsigned int iterations_between_reports);

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

	float learning_rate;
	unsigned int num_layers;
	unsigned int num_input;
	unsigned int num_hidden;
	unsigned int num_output;
	float desired_error;
	unsigned int max_iterations;
	unsigned int iterations_between_reports;
};

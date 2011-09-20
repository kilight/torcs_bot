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
	void setNumData(int numData) { 
		this->numData = numData;
		if(output != NULL) {
			delete output;
		}		
		output = new fann_type*[numData];
		if(input != NULL) {
			delete input;
		}		
		input = new fann_type*[numData];
	}

	fann_type* run(fann_type* input) { return net.run(input); }
	void destroy() { net.destroy(); }
	bool create_from_file(const std::string& configuration_file) { return net.create_from_file(configuration_file); }

	bool create_standard_array(unsigned int num_layers, const unsigned int* layers) { 
		return net.create_standard_array(num_layers, layers);
	}
	bool create_sparse_array(float connection_rate, unsigned int num_layers, const unsigned int* layers) { 
		return net.create_sparse_array(connection_rate, num_layers, layers);
	}
	bool create_shortcut_array(unsigned int num_layers, const unsigned int* layers) { 
		return net.create_shortcut_array(num_layers, layers);
	}
	void cascadetrain_on_data(const FANN::training_data &data, unsigned int max_neurons, unsigned int neurons_between_reports, float desired_error) {
		net.cascadetrain_on_data(data, max_neurons, neurons_between_reports, desired_error);
	}


	void inputTraindata(fann_type** input, fann_type** output);

	int getNumData() { return this->numData; }

	void setNumInput(int numIn) { this->numIn = numIn; }
	int getNumInpute() { return this->numIn; }
	
	void setNumOut(int numOut) { this->numOut = numOut; }
	int getNumOut() { return this->numOut; }

	void setNetParameters(float learning_rate, unsigned int num_layers, unsigned int num_input, 
		unsigned int num_hidden, unsigned int num_output, float desired_error, 
		unsigned int max_iterations, unsigned int iterations_between_reports);
	void testData();

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

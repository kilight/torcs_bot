/* neuronal network class for the torcs bot */

#include "fann_net.h"
#include <iostream>

fann_net::fann_net() {
	input = NULL;
	output = NULL;

	numIn = 0;
	numOut = 0;
	numData = 0;

	insertedIn = 0;
	insertedOut = 0;

	learning_rate = 0.3f;
	num_layers = 12;
	num_input = 28;
	num_hidden = 3;
	num_output = 2;
	desired_error = 0.001f;
	max_iterations = 3000000;
	iterations_between_reports = 10000;
}

fann_net::~fann_net() {
	data.destroy_train();
}

void fann_net::menu() {

}

void fann_net::setNetParameters(float learning_rate, unsigned int num_layers, unsigned int num_input, 
		unsigned int num_hidden, unsigned int num_output, float desired_error, 
		unsigned int max_iterations, unsigned int iterations_between_reports) {
	this->learning_rate = learning_rate;
	this->num_layers = num_layers;
	this->num_input = num_input;
	this->num_hidden = num_hidden;
	this->num_output = num_output;
	this->desired_error = desired_error;
	this->max_iterations = max_iterations;
	this->iterations_between_reports = iterations_between_reports;
}

/* void fann_net::sensor2Float(vector< sensor* >* data) {
	
} */

void fann_net::saveInputFieldVector(fann_type* data) {
	if(insertedIn < numData) {	
		input[insertedIn] = data;
		insertedIn++;
	}
	else 
		cout << "Too many input vectors" << endl;
}

void fann_net::saveOutputFieldVector(fann_type* data) {
	if(insertedOut < numData) {	
		input[insertedOut] = data;
		insertedOut++;
	}
	else 
		cout << "Too many output vectors" << endl;
}

void fann_net::inputTraindata() {
	insertedIn = 0;
	insertedOut = 0;
	data.set_train_data(numData, numIn, input, numOut, output);
	cout << "data put in train data" << endl;
	for(int i = 0; i < numData; i++) {
			delete input[i];
			delete output[i];
	}
	delete input;
	delete output;	
}

void fann_net::inputTraindata(fann_type** input, fann_type** output) {
	insertedIn = 0;
	insertedOut = 0;
	data.set_train_data(numData, numIn, input, numOut, output);
	cout << "data put in train data" << endl;
/*		delete input[i];
			delete output[i];
	}
	delete input;
	delete output; */	
}

void fann_net::generateNet() {
	std::ios::sync_with_stdio();
 	cout << endl << "Creating network." << endl;
	unsigned int layers[12] = {num_input, 28, 26, 24, 22, 20, 18, 16, 11, 7, 4, num_output};
	net.create_standard_array(num_layers, layers);	
	// net.create_shortcut_array(2, layers);
        // net.create_standard(num_layers, num_input, num_hidden, num_output);

        net.set_learning_rate(learning_rate);

        net.set_activation_steepness_hidden(1.0);
        net.set_activation_steepness_output(1.0);

	net.set_training_algorithm(FANN::TRAIN_RPROP);
    
        net.set_activation_function_hidden(FANN::ELLIOT);
        net.set_activation_function_output(FANN::ELLIOT);
}

// Callback function that simply prints the information to cout
int print_callback(FANN::neural_net &net, FANN::training_data &train,
    unsigned int max_epochs, unsigned int epochs_between_reports,
    float desired_error, unsigned int epochs, void *user_data)
{
    cout << "Epochs     " << setw(8) << epochs << ". "
         << "Current Error: " << left << net.get_MSE() << right << endl;
    return 0;
}

void fann_net::train() {
	net.init_weights(data);
        net.set_callback(print_callback, NULL);
        net.train_on_data(data, max_iterations, iterations_between_reports, desired_error);
	//net.cascadetrain_on_data(data, 10000, 10, desired_error);        
	for (unsigned int i = 0; i < data.length_train_data(); ++i)
        {
            // Run the network on the test data
            fann_type *calc_out = net.run(data.get_input()[i]);
        }
        
        cout << endl << "Saving network." << endl;

        // Save the network in floating point and fixed point
        net.save("torcs.net");
        unsigned int decimal_point = net.save_to_fixed("torcs_fixed.net");
}

void fann_net::testData() {
	cout << "starting data test" << endl;
	for(int i = 0; i < numData; i++) {
		for(int j = 0; j < numIn; j++) {
			cout << input[i][j];
		}
//		cout << endl;
		for(int j = 0; j < numOut; j++) {
			cout << output[i][j];
		}
		cout << " " << i << endl;
//		cout << endl;
	}
	cout << "test done" << endl;
}

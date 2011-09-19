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
}

fann_net::~fann_net() {
	data.destroy_train();
}

void fann_net::menu() {

}

/* void fann_net::sensor2Float(vector< sensor* >* data) {
	
} */

void fann_net::saveInputFieldVector(fann_type* data) {
	if(insertedIn <= numData) {	
		input[insertedIn] = data;
		insertedIn++;
	}
	else 
		cout << "Too many input vectors" << endl;
}

void fann_net::saveOutputFieldVector(fann_type* data) {
	if(insertedOut <= numData) {	
		input[insertedOut] = data;
		insertedOut++;
	}
	else 
		cout << "Too many output vectors" << endl;
}

void fann_net::inputTraindata() {
	data.set_train_data(numData, numIn, input, numOut, output);
	for(int i = 0; i < numData; i++) {
			delete input[i];
			delete output[i];
	}	
}

void fann_net::generateNet() {

    cout << endl << "Creating network." << endl;

    net.create_standard(num_layers, num_input, num_hidden, num_output);

    net.set_learning_rate(learning_rate);

    net.set_activation_steepness_hidden(1.0);
    net.set_activation_steepness_output(1.0);
    
    net.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
    net.set_activation_function_output(FANN::SIGMOID_SYMMETRIC_STEPWISE);
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

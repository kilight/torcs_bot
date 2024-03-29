/*		hs.p.tex.lab/hs.ki.lab/torcs.client.1::shift.cpp
		27.08.2011
*/
#include"steer.h"
/***  class steer_object  ****
*****************************/
steer_object::steer_object()
{
	steer=0;
	net.destroy();
	net.create_from_file("./lib.ki/net.miner/torcs.steer.net");	
}

steer_object::steer_object(db* database)
{
	this->database=database;
	net.destroy();
	net.generateNet();
}
steer_object::~steer_object(){}
	
	
void steer_object::learnFromDataFolder() 
{
	file data("./data/");
	data.setName("e-speedway");
	data.open();
	
	sensor s;
	int numPoints = 0;
	while(!data.eof() && (s.getDistFromStart() != -10.0 && s.getCurLapTime() != -10.0)) 
	{
		s = data.fetchNextData();
		numPoints++;
	}
	
	cout << "numPoints in file: " << numPoints << endl;

	net.setNumData(numPoints);
	net.setNumInput(num_steer_inputs);
	net.setNumOut(num_steer_outputs);

	fann_type** output = new fann_type*[net.getNumData()];
	fann_type** input = new fann_type*[net.getNumData()];
			
	fann_type* inputvec;
	fann_type* outputvec;

	data.close();
	data.open();
	data.setPosition(ios::beg);

	int countPointsFetched = 0;
	for(int k=0;k < numPoints;k++)
	{	
		s=data.fetchNextData();
		countPointsFetched++;
		
		inputvec = new fann_type[num_steer_inputs];
		outputvec = new fann_type[num_steer_outputs];


	int track=0;
	int view=9;
	float direction[19];

		direction[9]=0;							// set angle[0]=0
		for (int i=0;i<5;i++){	direction[i]=-90+i*15;			// set angle[ 0 bis  4]={-90,-75,-60,-45,-30}
					direction[18-i]=90-i*15;	}	// set angle[14 bis 18]={+30,+45,+60,+75,+90}
		for (int i=5;i<9;i++){	direction[i]=-20+(i-5)*5;		// set angle[ 5 bis  8]={-20,-15,-10,-5}
					direction[18-i]=20-(i-5)*5;	}	// set angle[10 bis 13]={+5,+10,+15,+20}
										// viewCalculator
		for(int i=0;i<16;i++)
			{if((s.getTrack(i)+s.getTrack(i+1)+s.getTrack(i+2))>track){track=s.getTrack(i)+s.getTrack(i+1)+s.getTrack(i+2);view=i+1;}}

		// for(int i=0;i<18;i++){inputvec[i]=s.getTrack(i);}
		// inputvec[0]=s.getTrackPos();
		// inputvec[1]=s.getSpeedX();
		inputvec[0]=view;

		outputvec[0]=s.getSteer();

	
		input[k] = inputvec;
		output[k] = outputvec;
	}
	cout << "lap complete" << endl;
	net.inputTraindata(input,output);
	net.train();
	data.close();
}	
	
/**   class steer_object race.net   **
*************************************/
void steer_object::race(CarState &cs)
{
	int view=0;	
	int track=0;
	int stuck=200;
	
	float direction[19];
	direction[9]=0;							// set angle[0]=0
	for (int i=0;i<5;i++){	direction[i]=-90+i*15;			// set angle[ 0 bis  4]={-90,-75,-60,-45,-30}
				direction[18-i]=90-i*15;	}	// set angle[14 bis 18]={+30,+45,+60,+75,+90}
	for (int i=5;i<9;i++){	direction[i]=-20+(i-5)*5;		// set angle[ 5 bis  8]={-20,-15,-10,-5}
				direction[18-i]=20-(i-5)*5;	}	// set angle[10 bis 13]={+5,+10,+15,+20}

	bool offTrack = false;
	int totalsum = 0;
	for(int i=0;i<17;i++)
	{	
		int sum = cs.getTrack(i)+cs.getTrack(i+1)+cs.getTrack(i+2);
		if(sum>track)
		{ track=sum;
		  view=i+1; }
		if(sum <0)
		  offTrack = true;
	}

/*	if(track == 0) 
		{ view = 9; } */
	if(offTrack && track == 0) 
	{ if (cs.getTrackPos() < -0.95 && track < 150) 
		{ view = 18;}
	  else if (cs.getTrackPos() > 0.95 && track < 150)
		{ view = 0;}

//	  cout << cs.getTrackPos() << " " << view << endl;
	}

	if(cs.getTrackPos() < -0.8 && view < 9) { view = 9; }
	if(cs.getTrackPos() > 0.8 && view > 9) {view = 9;}

	for(int i=0;i<19;i++){if (view==i){steer=(1)*(float)sin(direction[view])*0.2 * (125/(cs.getSpeedX()+1));}}

	for(int i=0;i<17;i++)
	{	
		if((cs.getTrack(i)+cs.getTrack(i+1))<stuck)
		{ stuck=(cs.getTrack(i)+cs.getTrack(i+1)); }
	}

	// if(track<0){steer=(-1)*cs.getTrackPos()/*(abs(cs.getAngle())/3.141)*/*abs(cs.getTrackPos());}

		char format[3]={':','+','='};
		ofstream outD5("lib.ki/debug.data/debug.steer",ios_base::app);
		outD5<<view<<format[0]<<track<<format[0]<<direction[view]<<format[0]<<steer<<format[0]<<stuck<<endl;
}

void steer_object::race_ki(CarState &cs)
{
	fann_type* input = new fann_type[num_steer_inputs];
	fann_type* output = new fann_type[num_steer_outputs];

	// for(int i=0;i<18;i++){input[i]=cs.getTrack(i);}
	// input[0]=cs.getTrackPos();
	// input[1]=cs.getSpeedX();

	int track=0;
	int view=9;
	for(int i=0;i<16;i++)
	{if((cs.getTrack(i)+cs.getTrack(i+1)+cs.getTrack(i+2))>track){track=cs.getTrack(i)+cs.getTrack(i+1)+cs.getTrack(i+2);view=i+1;}}
	input[0]=view;

	output=net.run(input);
	steer=output[0];	
}



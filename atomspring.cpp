/*	atomspring.cpp
computes the position of atoms based on the "spring" force of the bond between them.
F = k(x2-x1-x0) where k is in N/m, x's are in m, and mass is in amu.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//functions
double force(double* const force, double x1, double x2);
double movement1(double* const acc, double* const vel, double force, double mass);
double movement2(double* const x, double acc, double vel);
int results(double* const period, double* const time, double x);

//setup of initial conditions
//mass in AMU
const double mass1 = 1.0079; //Hydrogen
const double mass2 = 18.9984; //Other element: F
const double amutokg = 1.660539e-27; //converts amu to kg

const double timestep = 1e-16;//0.000000000000001; //in seconds
const double x0 = 0.092e-9; //Specific to material: in m
const double k = 970;	//spring constant: in N/m

const double finish = timestep * 360; //how long should the test run?

int main(){
	//	char quits;
	double x1 = 0;
	double x2 = x0 + 0.05*x0;
	double v1 = 0;
	double v2 = 0;
	double acc1 = 0;
	double acc2 = 0;
	double force1 = 0;
	double force2 = 0;
	int ii = 0;
	double frequency = 0;
	double half_period = 0;

	string resultfile;
	cout << "File for results: " << endl;
	cout << "C:\\Temp\\";
	cin >> resultfile;
	resultfile = "C:\\Temp\\" + resultfile;
	ofstream thefile;
	thefile.open(resultfile);

	thefile << "ATOMSPRING" << endl << endl;
	thefile << "mass 1: " << mass1 << " amu" << endl;
	thefile << "mass 2: " << mass2 << " amu" << endl;
	thefile << "K: " << k << " N/m" << endl;
	thefile << "x0: " << x0 << " m " << endl;
	thefile << "time step: " << timestep << "s" << endl << endl;
	thefile << "Time \tPosition 2 (m)" << endl;

	for (double t = timestep; t < finish; t = t + timestep){	//how many times to run before stopping?
		force(&force1, x1, x2);
		force2 = -1 * force1;  	//force(&force2, x1, x2);
		movement1(&acc1, &v1, force1, mass1);
		movement2(&x1, acc1, v1);
		movement1(&acc2, &v2, force2, mass2);
		movement2(&x2, acc2, v2);

		results(&frequency, &half_period, x2);

		if (half_period == 0){
			thefile << frequency << endl;
		}
		//thefile << t << "\t" << x2 << endl;

	}
	thefile.close();
	//	cin >> quits;
	return 0;
}

//Compute force
double force(double* const force, double x1, double x2){
	*force = k*(x2 - x1 - x0);
	return *force;
}

//Compute acceleration and new velocity
double movement1(double* const acc, double* const vel, double force, double mass){
	(*vel) = (*vel) + 0.5 * (*acc) * timestep;
	(*acc) = force / (mass*amutokg);
	(*vel) = (*vel) + 0.5 * (*acc) * timestep;
	return *vel, *acc;
}

//Compute the new position
double movement2(double* const x, double acc, double vel){
	*x = (*x) + vel * timestep + 0.5 * acc * timestep*timestep;
	return *x;
}

int results(double* const period, double* const time, double x){
	if (x <= x0){
		*time = *time + timestep;
	}
	else if (x >= x0 && *time != 0){
		*period = 2 * *time;
		//period/2 = *time
		//time only contains 0.5*period
		*time = 0;
		return *period;
		//only return frequency if it was calculated
	}
	return *time;
}

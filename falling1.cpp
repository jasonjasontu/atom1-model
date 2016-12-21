/*Computing position of an object in freefall using verlet algorithm
Ivan Erway
9/26/2015
*/

#include <iostream>
#include <iomanip>
using namespace std;


//Setting up the given values

double verlet(double &x, double vel, double acc, double t);
double accel(double &a);


int main(){
	const double timestep = 0.000001;// 0.0005;
	double t = 0;
	double acc = -10;
	double y = 10.00;
	double vel = 0;
	int counter = 0;
	int i = y;
	while (y >= 0){
		if (i > y){
			cout << fixed << setprecision(5) << "Position: " << y << " m\t Time: " << t << "s" << "\tTotal loops: " << counter << endl;
			i--;
		}
		verlet(y, vel, acc, t);
		t = t + timestep;
		counter++;
	}
	cout << "Position: " << y << " m\t Time: " << t << "s" << "\tTotal loops: " << counter << endl;
	char finisher;
	cin >> finisher;
}

double verlet(double &x, double vel, double acc, double timestep){
	x = x + vel * timestep + 0.5 * acc * timestep * timestep;
	vel = vel + 0.5 * acc * timestep;
	accel(acc);
	vel = vel + 0.5 * acc * timestep;
	return x, vel;
}

//Placeholder for acceleration calculation since acceleration is constant
double accel(double &acc){
	return acc;
}

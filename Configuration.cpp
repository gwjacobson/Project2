#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <random>
#include <fstream>

using namespace std;

//Function for calculating the Energy of a certain
//configuration.
double Energy(vector<vector<int > > config) {
	double energy = 0.0;
	int size = config.size();
	for (int i = 0; i < size; i++) { //lots of boundary checks which are periodic
		for (int j = 0; j < size; j++) {
			if (i - 1 < 0) {
				if (j - 1 < 0) { //top left corner
					energy += (config[i][j] * config[i + 1][j]) + (config[i][j] * config[i][size - 1]) +
						(config[i][j] * config[size - 1][j]) + (config[i][j] * config[i][j + 1]);
				}
				else if (j + 1 >= size) { //bottom left corner
					energy += (config[i][j] * config[i + 1][j]) + (config[i][j] * config[i][j - 1]) +
						(config[i][j] * config[size - 1][j]) + (config[i][j] * config[i][0]);
				}
				else { //left side middle
					energy += (config[i][j] * config[i + 1][j]) + (config[i][j] * config[i][j - 1]) +
						(config[i][j] * config[size - 1][j]) + (config[i][j] * config[i][j + 1]);
				}
			}
			else if (i + 1 >= size) {
				if (j - 1 < 0) { //top right corner
					energy += (config[i][j] * config[0][j]) + (config[i][j] * config[i][size - 1]) +
						(config[i][j] * config[i - 1][j]) + (config[i][j] * config[i][j + 1]);
				}
				else if (j + 1 >= size) { //bottom right corner
					energy += (config[i][j] * config[0][j]) + (config[i][j] * config[i][j - 1]) +
						(config[i][j] * config[i - 1][j]) + (config[i][j] * config[i][0]);
				}
				else { //right side middle
					energy += (config[i][j] * config[0][j]) + (config[i][j] * config[i][j - 1]) +
						(config[i][j] * config[i - 1][j]) + (config[i][j] * config[i][j + 1]);
				}
			}
			else if (j - 1 < 0) { //top middle
				energy += (config[i][j] * config[i + 1][j]) + (config[i][j] * config[i][size - 1]) +
					(config[i][j] * config[i - 1][j]) + (config[i][j] * config[i][j + 1]);
			}
			else if (j + 1 >= size) { //bottom middle
				energy += (config[i][j] * config[i + 1][j]) + (config[i][j] * config[i][j - 1]) +
					(config[i][j] * config[i - 1][j]) + (config[i][j] * config[i][0]);
			}
			else { //rest of the cells
				energy += (config[i][j] * config[i + 1][j]) + (config[i][j] * config[i][j - 1]) +
					(config[i][j] * config[i - 1][j]) + (config[i][j] * config[i][j + 1]);
			}
		}
	}
	return (- energy)/2;
}

//Function for the energy difference between two
//configurations.
double deltaE(int x, int y, vector<vector<int > > original) {
	vector<vector<int > > config = original;
	config[x][y] = config[x][y] * (-1); //flip the single spin
	
	double diff = abs(Energy(original) - Energy(config));
	
	return diff;
}

//Function for taking a string representation of an
//Ising Model and turning it into a vector.
void fromString(string &myString) {}

//Function to print to a text file the bit and number sweep for each configuration to
//later analyze.
string print(string bit, int sweep) {
	string line = to_string(sweep) + " : " + bit; //line of the text file

	ofstream myfile;
	myfile.open("configs", ios::app);
	myfile << line << endl;
	myfile.close();

}



int main() {

	vector<vector<int > > spin; //vector of spins: 1 is up, -1 is down
	vector<vector<double > > h; //vector of magnet field values

	spin.resize(3); //make 3x3 vector
	for (int i = 0; i < spin.size(); i++) {
		spin[i].resize(3);
		fill(spin[i].begin(), spin[i].end(), 1); //fill vector with all spin up
	}

	//cout << Energy(spin) << endl;

	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> coord(0, 2);
	uniform_real_distribution<double> prob(0, 1);

	double B = 0.3; //constant inverse of temperature
	//cout << deltaE(2, 0, spin) << endl;
	//vector<vector<int > > news = spin;
	//news[2][0] = (-1) * spin[2][0];
	//cout << abs(Energy(news) - Energy(spin)) << endl;

	for (int sweep = 0; sweep < 10000; sweep++) { //sweep through flipping the spins
		for (int i = 0; i < 100; i++) {  // amount of spin flips per sweep 
			int x = coord(mt);
			int y = coord(mt);
			double ran = prob(mt);

			if (B * exp(-deltaE(x, y, spin)) > ran) {
				spin[x][y] = (-1) * spin[x][y];
			}
			else {
				continue;
			}
		}
		string bit; //the bit to show what configuration the sweep is currently in
		for (int vert = 0; vert < spin.size(); vert++) { //get the bits for each config to later analyze
			for (int hor = 0; hor < spin[vert].size(); hor++) {
				if (spin[hor][vert] == 1) {
					bit += '0';
				}
				else {
					bit += '1';
				}
			}
		}
		print(bit, sweep);
	}
}


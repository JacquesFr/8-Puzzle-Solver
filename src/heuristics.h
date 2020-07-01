#ifndef HEURISTICS_H
#define HEURISTICS_H
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

const vec goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

void next_state(int vector, int &x, int &y) { //euclidian helper
	for(int i = 0; i<3; i++) {					
		for(int j = 0; j<3; j++) {	

			if(goal.at(i).at(j) == vector) { //find next state to work at
				x = i;
				y = j;
				return;	//return puzzle with updated indicies	
			}

		}
	}
}

int eucledian_heruistics(vec vector) { // result = sqrt(pow(x1-y1, 2) + pow(x2-y2, 2))
	int result = 0;

	for (int i = 0; i<3; i++) {					
		for (int j = 0; j<3; j++) {		

			if (vector.at(i).at(j) == 0)
				continue;				//blank space
			

			if (vector.at(i).at(j) != goal.at(i).at(j)) { //incorrect state
				int x = 0;
				int y = 0;

				next_state(vector.at(i).at(j), x, y);	  //get correct index
				x = pow(x - y, 2); //Euclidean Formula!
				y = pow(i - j, 2); //Euclidean Formula!

				while ( (x != 0) || (y != 0) ) {		//calculate distance and make sure not negative
														
					if (x < 0) {
						x = x + 1;
						result++;
					}

					if (x > 0) {
						x = x - 1;
						result++;
					}

					if (y < 0) {
						y = y + 1;
						result++;
					}

					if (y > 0) {
						y = y - 1;
						result++;
					}
					
				}

			}//columns
		}//rows
		
	}
	
	return result;
}

int misplaced_heuristics(vec vector) {
	int result = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (vector.at(i).at(j) == 0)
				continue;

			if (goal.at(i).at(j) != vector.at(i).at(j))
				result++;

		}//columns
	}//rows

	return result;
}

#endif

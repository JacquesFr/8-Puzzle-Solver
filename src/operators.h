#ifndef OPERATORS_H
#define OPERATORS_H
#include <iostream>
#include <vector>

using namespace std;

typedef vector <vector <int>> vec;

vec swap(vec vector, int i, int j, int k, int l) {
	int temp = vector.at(k).at(l);

	vector.at(i).at(j) = temp;
	vector.at(k).at(l) = 0;

	return vector;
}


//Returns vector that is moved left. If zero is in the right column then return the same vector
vec move_left(vec vector) {
	int x = 0;
	int y = 0;

	//check for illegal condition
	for (int i = 0; i < 3; i++) {
		if (vector.at(i).at(2) == 0)
			return vector;
	}
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {

			if (vector.at(i).at(j) == 0) {
				x = i;
				y = j;
			}

		}
	}

	return swap(vector, x, y, x, y+1);
}

//Returns vector that is moved right. If zero is in the left column then return the same vector
vec move_right(vec vector) {
	int x = 0;
	int y = 0;

	//check for illegal condition
	for (int i = 0; i < 3; i++) {
		if (vector.at(i).at(0) == 0)
			return vector;
	}


	for (int i = 0; i < 3; i++) {
		for (int j = 1; j < 3; j++) {

			if (vector.at(i).at(j) == 0) {
				x = i;
				y = j;
			}

		}
	}

	return swap(vector, x, y, x, y-1);
}

//Returns vector that is moved up. If zero is in the bottom row then return the same vector
vec move_up(vec vector) {
	int x = 0;
	int y = 0;

	//check for illegal condition
	for (int i = 0; i < 3; i++) {
		if (vector.at(2).at(i) == 0)
			return vector;
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {

			if (vector.at(i).at(j) == 0) {
				x = i;
				y = j;
			}

		}
	}

	return swap(vector, x, y, x+1, y);
}

//Returns vector that is moved down. If zero is in the top row then return the same vector
vec move_down(vec vector) {
	int x = 0;
	int y = 0;

	//check for illegal condition
	for (int i = 0; i < 3; i++) {
		if (vector.at(0).at(i) == 0)
			return vector;
	}

	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if(vector.at(i).at(j) == 0) {
				x = i;
				y = j;
			}

		}
	}
	return swap(vector, x, y, x-1, y);
}

#endif

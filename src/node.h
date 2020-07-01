#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
using namespace std;
typedef vector <vector <int>> vec;

struct node {
	vec vector;
	int heu_price = 0;
	int uni_price = 0;
	int sum = 0;	

	node *root = NULL;
	node *leaf_0 = NULL;
	node *leaf_1 = NULL;
	node *leaf_2 = NULL;
	node *leaf_3 = NULL;

	node(vec new_vector) {			
		vector = new_vector;
		
		heu_price = 0;
		uni_price = 0;
	};

	node(vec new_vector, int uniform_price) {
		vector = new_vector;
		
		heu_price = 0;
		uni_price = uniform_price;
	};

	node(const node &new_vector) {			
		vector = new_vector.vector;

		heu_price = new_vector.heu_price;
		uni_price = new_vector.uni_price;
		sum = new_vector.sum;

		leaf_0 = new_vector.leaf_0;
		leaf_1 = new_vector.leaf_1;
		leaf_2 = new_vector.leaf_2;
		leaf_3 = new_vector.leaf_3;
		root = new_vector.root;
	}

	void operator=(const node &new_vector) {		
		vector = new_vector.vector;
		
		heu_price = new_vector.heu_price;
		uni_price = new_vector.uni_price;
		sum = new_vector.sum;

		leaf_0 = new_vector.leaf_0;
		leaf_1 = new_vector.leaf_1;
		leaf_2 = new_vector.leaf_2;
		leaf_3 = new_vector.leaf_3;
		root = new_vector.root;
	}

	void print() {				
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << vector.at(i).at(j); 
			}
			if (i < 2) {
				cout << endl; //next row
			}
			else {
				cout << "  ";
			}
		}
	}

};


//Compare nodes values
struct GreaterThan  {  
	bool operator() (const node& left, const node& right)  {  
		bool result;
		result = left.sum > right.sum;

		return result;
	}  
};  

#endif

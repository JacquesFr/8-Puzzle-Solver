#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "operators.h"
#include "node.h"
#include "heuristics.h"

using namespace std;

vector <node> hit;
priority_queue <node, vector<node>, GreaterThan> search_queue;

bool is_hit(vec vector);
void print_nodes(node val, int size, int expanded_nodes);
void graph_search(vec puzzle, string heuristics);

int main() {
	vec puzzle(3, vector<int>(3));
	vector <int> input;
	string heuristic;
	int option = 0;
	int index = 0;

	//Default values
	int i = 1, j = 0, k = 3;
	int l = 4, m = 2, n = 6;
	int o = 7, p = 5, q = 8;

	cout << "Welcome to 862010872 8-puzzle solver." << endl;
	cout << "Type 1 to use a default puzzle, or 2 to enter your own puzzle." << endl;
	cin >> option;
	cout << endl;

	if(option == 2){
		cout << "Enter your puzzle, use a zero to represent the blank" << endl;
		cout << "Enter the first row, use space or tabs between numbers" << endl;
		cin >> i >> j >> k;
		cout << "Enter the second row, use space or tabs between numbers" << endl;
		cin >> l >> m >> n;
		cout << "Enter the third row, use space or tabs between numbers" << endl;
		cin >> o >> p >> q;
	}

	
	input.push_back(i); 
	input.push_back(j); 
	input.push_back(k);
	input.push_back(l); 
	input.push_back(m); 
	input.push_back(n);
	input.push_back(o); 
	input.push_back(p); 
	input.push_back(q);

	//Make our puzzle from the inputs
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			puzzle.at(i).at(j) = input.at(index); //assign the vector index to the input for that index
			cout << puzzle.at(i).at(j); //print out each square
			index++;
		}
		cout << endl;
	}

	cout << endl;
	cout << "Enter your choice of algorithm" << endl;
	cout << "1: Uniform Cost Search" << endl;
	cout << "2: A* with the Misplaced Tile heuristic." << endl;
	cout << "3: A* with the Eucledian distance heuristic." << endl << endl;
	cin >> option;
	cout << endl;

	
	switch (option) {
		case 1:
			heuristic = "Default";
			break;
		
		case 2:
			heuristic = "Misplaced";
			break;

		case 3:
			heuristic = "Eucledian";
			break;

		default:
			heuristic = "Default";
			break;
	}

	graph_search(puzzle, heuristic);

	return 0;
}

bool is_hit(vec vector) {
	bool result = false;
	int size = hit.size();

	for (int i = 0; i < size; i++) {
		if (hit.at(i).vector == vector)
			result = true;
	}

	return result;
}

void print_nodes(node val, int size, int expanded_nodes) {
	node temp = val;
	stack<node> stack;
	stack.push(temp);					//add new node to stack

	while (temp.root != NULL) {			//add nodes to stack, stop at root
		temp = *temp.root;
		stack.push(temp);

	}

	cout << "Expanding state" << endl;
	stack.top().print();
	cout << endl << endl;

	stack.pop();

	while (stack.size() >= 2) { //Expand out every node and explain				
		cout << "The best state to expand with g(n) = " << stack.top().uni_price << " and h(n) = " << stack.top().heu_price << " is..." << endl;
		stack.top().print();
		cout << "Expanding this node ..." << endl << endl;
		stack.pop();
	}

	cout << endl << "Goal!!!" << endl << endl;
	cout << "To solve this problem the search algorithm expanded a total of " << expanded_nodes << " nodes." << endl;
	cout << "The maximum number of nodes in the queue at any one time: " << size << "." << endl;

}

void graph_search(vec puzzle, string heuristics) {
	node curr(puzzle);
	int size = 0;
	int expanded_nodes = 0;

	if (heuristics == "Misplaced") {
		cout << "Using Misplaced Heuristic" << endl << endl;
	}

	else if (heuristics == "Eucledian") {
		cout << "Using Eucledian Heuristic" << endl << endl;
	}

	hit.push_back(curr);					
	search_queue.push(curr);				   

	while (!search_queue.empty()) {				

		node* curr = new node(search_queue.top());

		if (search_queue.top().vector == goal) { 			
			print_nodes(search_queue.top(), size, expanded_nodes);
			break;

		} else {

			hit.push_back(search_queue.top());	//Add to hit list

			int temp = search_queue.size();

			if (temp > size) {			//get max queueueue size
				size = temp;
			}

			search_queue.pop();
			expanded_nodes++;

			//Make our node opeartions
			node* node_right = new node(move_right(curr->vector), curr->uni_price + 1);
			node* node_left = new node(move_left(curr->vector), curr->uni_price + 1);
			node* node_up = new node(move_up(curr->vector), curr->uni_price + 1);
			node* node_down = new node(move_down(curr->vector), curr->uni_price + 1);

			//Get our prices for each operation
			if (heuristics == "Misplaced") {
				node_right->heu_price = misplaced_heuristics(node_right->vector);
				node_left->heu_price = misplaced_heuristics(node_left->vector);
				node_up->heu_price = misplaced_heuristics(node_up->vector);
				node_down->heu_price = misplaced_heuristics(node_down->vector);	
			}

			if (heuristics == "Eucledian") {		
				node_right->heu_price = eucledian_heruistics(node_right->vector);
				node_left->heu_price = eucledian_heruistics(node_left->vector);
				node_up->heu_price = eucledian_heruistics(node_up->vector);
				node_down->heu_price = eucledian_heruistics(node_down->vector);
			}

			//calculate total sum for each operation

			//Get right operation
			node_right->sum = node_right->uni_price + node_right->heu_price;
			//if we havnt hit right node add it to our search queue
			if (!is_hit(node_right->vector)) {		
				curr->leaf_3 = node_right;
				node_right->root = curr;
				search_queue.push(*node_right);
			}

			//Get left operation
			node_left->sum = node_left->uni_price + node_left->heu_price;
			//if we havnt hit left node add it to our search queue
			if (!is_hit(node_left->vector)) {		
				curr->leaf_2 = node_left;
				node_left->root = curr;
				search_queue.push(*node_left);
			}

			//Get up operation
			node_up->sum = node_up->uni_price + node_up->heu_price;
			//if we havnt hit up node add it to our search queue
			if (!is_hit(node_up->vector)) {		
				curr->leaf_1 = node_up;
				node_up->root = curr;
				search_queue.push(*node_up);
			}

			//Get down operation
			node_down->sum = node_down->uni_price + node_down->heu_price;
			//if we havnt hit down node add it to our search queue
			if (!is_hit(node_down->vector)) {		
				curr->leaf_0 = node_down;
				node_down->root = curr;
				search_queue.push(*node_down);
			}
		}
	}

	if (search_queue.empty())
		cout << endl << "No Solution" << endl;
	
}
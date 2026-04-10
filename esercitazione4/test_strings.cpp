#include <iostream>
#include <vector>
#include <string>

#include "sorts.hpp"
using namespace std;

int main(){
	vector<string> strings = {
    "universo", "bussola", "cristallo", "drago", "eclissi", 
    "foresta", "ghiaccio", "nuvola", "oceano", "piramide"
	};
	
	// Test Bubble Sort
	vector<string> v_bubble = strings;
	bubblesort(v_bubble);
	int t_1 = issorted(v_bubble);
	if(t_1 != 0){
		return EXIT_FAILURE;
	}

	// Test Insertion Sort
	vector<string> v_insertion = strings;
	insertionsort(v_insertion);
	int t_2 = issorted(v_insertion);
	if(t_2 != 0){
		return EXIT_FAILURE;
	}

	// Test Selection Sort
	vector<string> v_selection = strings;
	selectionsort(v_selection);
	int t_3 = issorted(v_selection);
	if(t_3 != 0){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
};
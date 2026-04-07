#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "timecounter.h"
#include "randfiller.h"
#include "sorts.hpp"
using namespace std;


template<typename T>
int test_sort(int dimensione, T val_min, T val_max){
	randfiller rf;
	vector<T> v(dimensione);
	rf.fill(v, val_min, val_max);
	
	selectionsort(v);
	int c = issorted(v);
	return c;
}

int main(){
	cout << endl << "Si testa l'algoritmo Selectionsort su 100 vettori di dimensioni randomiche da 1 a 8000 riempiti di valori randomici da -10000 a +10000 interi, double e float." <<endl;
	double tempo=0;
	randfiller rf;
	vector<int> dimensioni(100);
	rf.fill(dimensioni, 1, 8000);
	for(int i=0;i<dimensioni.size();i++){
		timecounter tc;
		tc.tic();
		int t_1 = test_sort<int>(dimensioni[i],-10000, 10000);
		if(t_1 == 1){
			cout << "Selection int Test "<< i+1 << " EXIT FAILURE"<<endl;
			return EXIT_FAILURE;
		}
		int t_2 = test_sort<double>(dimensioni[i],-10000, 10000);
		if(t_2 == 1){
			cout << "Selection double Test "<< i+1 << " EXIT FAILURE"<<endl;
			return EXIT_FAILURE;
		}
		int t_3 = test_sort<float>(dimensioni[i],-10000, 10000);
		if(t_3 == 1){
			cout << "Selection float Test "<< i+1 << " EXIT FAILURE"<<endl;
			return EXIT_FAILURE;
		}
		tempo = tempo + tc.toc();
	}
	cout << endl << "Test concluso positivamente in " << tempo << " secondi." <<endl<<endl;
	return EXIT_SUCCESS;
};
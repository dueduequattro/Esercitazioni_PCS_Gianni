#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#include "randfiller.h"
#include "timecounter.h"
#include "sorts.hpp"
using namespace std;


int main() {
	
	randfiller rf;
    timecounter tc;
    
	vector<double> potenze_due(13);
    for(int i=1;i<14;i++){
	    potenze_due[i-1]=pow(2,i);
    }
	
	
    cout <<endl<<"TEMPI DI ESECUZIONE DI BubbleSort, InsertionSort, SelectionSort, Mergesort, Quicksort AL VARIARE DELLA DIMENSIONE IN POTENZA DI 2"<<endl
	<<"DELTA > 0 ---> funzione Sort di algorithm più veloce" <<endl <<endl;
    
    cout << "\n--- Benchmark Tipo: INTERI ---\n";
    for (int i = 1; i < 14; i++) {
        vector<int> base_vector(potenze_due[i-1]);
        rf.fill(base_vector, 1, 100000);

        vector<int> vec_bubble = base_vector;
        vector<int> vec_insertion = base_vector;
        vector<int> vec_selection = base_vector;
        vector<int> vec_merge = base_vector;
        vector<int> vec_quick = base_vector;
        vector<int> vec_sort = base_vector;


        tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
        tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
        tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
        tc.tic(); mergesort(vec_merge,0,vec_merge.size() -1); double time_merge = tc.toc();
        tc.tic(); quicksort(vec_quick,0,vec_quick.size() -1); double time_quick = tc.toc();
        tc.tic(); sort(vec_sort.begin(), vec_sort.end()); double time_sort = tc.toc();

        cout << "Size: " << potenze_due[i-1]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection
                  << "s | Merge: " << time_merge
                  << "s | Quick: " << time_quick << "s" << endl
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort 
                  << "s | Delta time Merge VS Sort: " << time_merge - time_sort
                  << "s | Delta time Quick VS Sort: " << time_quick - time_sort << "s\n";
    }
    
    cout << "\n--- Benchmark Tipo: DOUBLE ---\n";
    for (int i = 1; i < 14; i++) {
        vector<double> base_vector(potenze_due[i-1]);
        rf.fill(base_vector, 1.0, 100000.0);

        vector<double> vec_bubble = base_vector;
        vector<double> vec_insertion = base_vector;
        vector<double> vec_selection = base_vector;
        vector<double> vec_merge = base_vector;
        vector<double> vec_quick = base_vector;
        vector<double> vec_sort = base_vector;


        tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
        tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
        tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
        tc.tic(); mergesort(vec_merge,0,vec_merge.size() -1); double time_merge = tc.toc();
        tc.tic(); quicksort(vec_quick,0,vec_quick.size() -1); double time_quick = tc.toc();
        tc.tic(); sort(vec_sort.begin(), vec_sort.end()); double time_sort = tc.toc();

        cout << "Size: " << potenze_due[i-1]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection
                  << "s | Merge: " << time_merge
                  << "s | Quick: " << time_quick << "s" << endl
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort 
                  << "s | Delta time Merge VS Sort: " << time_merge - time_sort
                  << "s | Delta time Quick VS Sort: " << time_quick - time_sort << "s\n";
    }
    

	cout << "\n--- Benchmark Tipo: FLOAT ---\n";
    for (int i = 1; i < 14; i++) {
        vector<float> base_vector(potenze_due[i-1]);
        rf.fill(base_vector, 1.0f, 100000.0f);

        vector<float> vec_bubble = base_vector;
        vector<float> vec_insertion = base_vector;
        vector<float> vec_selection = base_vector;
        vector<float> vec_merge = base_vector;
        vector<float> vec_quick = base_vector;
        vector<float> vec_sort = base_vector;
        

        tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
        tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
        tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
        tc.tic(); mergesort(vec_merge,0,vec_merge.size() -1); double time_merge = tc.toc();
        tc.tic(); quicksort(vec_quick,0,vec_quick.size() -1); double time_quick = tc.toc();
        tc.tic(); sort(vec_sort.begin(), vec_sort.end()); double time_sort = tc.toc();

        cout << "Size: " << potenze_due[i-1]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection
                  << "s | Merge: " << time_merge
                  << "s | Quick: " << time_quick << "s" << endl
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort 
                  << "s | Delta time Merge VS Sort: " << time_merge - time_sort
                  << "s | Delta time Quick VS Sort: " << time_quick - time_sort << "s\n";
    }
    

    return 0;
}

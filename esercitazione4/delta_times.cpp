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
	cout <<endl<<"TEMPI DI ESECUZIONE DI BubbleSort, InsertionSort, SelectionSort AL VARIARE DI 5 DIMENSIONI RANDOMICHE SCELTE TRA 1 e 8000"<<endl
	<<"DELTA > 0 ---> funzione Sort di algorithm più veloce" <<endl <<endl;
    
    randfiller rf;
    timecounter tc;
    
    vector<double> potenze_due(13);
    for(int i=1;i<14;i++){
	    potenze_due[i-1]=pow(2,i);
    }

    vector<int> sizes_vec(5);
    rf.fill(sizes_vec, 1, 8000);
    bubblesort(sizes_vec);

    int sizes[5];
    int sizes_count = 5;
    for (int i = 0; i < sizes_count; i++)
        sizes[i] = sizes_vec[i];

    // Benchmark int
    cout << "\n--- Benchmark Tipo: INTERI ---\n";
    for (int i = 0; i < sizes_count; i++) {
        vector<int> base_vector(sizes[i]);
        rf.fill(base_vector, -10000, 10000);

        vector<int> vec_bubble = base_vector;
        vector<int> vec_insertion = base_vector;
        vector<int> vec_selection = base_vector;
        vector<int> vec_sort = base_vector;


        tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
        tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
        tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
        tc.tic(); sort(vec_selection.begin(), vec_selection.end()); double time_sort = tc.toc();

        cout << "Size: " << sizes[i]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection << "s"
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort << "s\n";
    }

    // Benchmark double
    cout << "\n--- Benchmark Tipo: DOUBLE ---\n";
    for (int i = 0; i < sizes_count; i++) {
        vector<double> base_vector(sizes[i]);
        rf.fill(base_vector, -10000.0, 10000.0);

        vector<double> vec_bubble = base_vector;
        vector<double> vec_insertion = base_vector;
        vector<double> vec_selection = base_vector;


        tc.tic(); 
        bubblesort(vec_bubble); 
        double time_bubble = tc.toc();
        
        tc.tic(); 
        insertionsort(vec_insertion); 
        double time_insertion = tc.toc();
        
        tc.tic(); 
        selectionsort(vec_selection); 
        double time_selection = tc.toc();

        tc.tic(); sort(vec_selection.begin(), vec_selection.end()); double time_sort = tc.toc();

        cout << "Size: " << sizes[i]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection << "s"
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort << "s\n";
    }
    
    // Benchmark float
    cout << "\n--- Benchmark Tipo: FLOAT ---\n";
    for (int i = 0; i < sizes_count; i++) {
        vector<float> base_vector(sizes[i]);
        rf.fill(base_vector, -10000.0f, 10000.0f);

        vector<float> vec_bubble = base_vector;
        vector<float> vec_insertion = base_vector;
        vector<float> vec_selection = base_vector;

        tc.tic(); 
        bubblesort(vec_bubble); 
        double time_bubble = tc.toc();
        
        tc.tic(); 
        insertionsort(vec_insertion); 
        double time_insertion = tc.toc();
        
        tc.tic(); 
        selectionsort(vec_selection); 
        double time_selection = tc.toc();

        tc.tic(); sort(vec_selection.begin(), vec_selection.end()); double time_sort = tc.toc();

        cout << "Size: " << sizes[i]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection << "s"
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort << "s\n";
    }
    
    // Sostituisci il blocco della stringa con questo:
	cout << "\n--- Benchmark Tipo: CARATTERI ---\n";
	
	string testo = "ordinamentoastringhe"; 
	vector<char> base_chars(testo.begin(), testo.end()); // Trasforma la stringa in vector
	
	vector<char> v_bubble = base_chars;
	vector<char> v_insertion = base_chars;
	vector<char> v_selection = base_chars;
	vector<char> v_sort = base_chars;
	
	
	tc.tic(); bubblesort(v_bubble); double t_bubble = tc.toc();
	tc.tic(); insertionsort(v_insertion); double t_insertion = tc.toc();
	tc.tic(); selectionsort(v_selection); double t_selection = tc.toc();
	tc.tic(); sort(v_sort.begin(), v_sort.end()); double t_sort = tc.toc();
	
	cout << "Stringa Originale: " << testo << endl;
	cout << "Stringa Ordinata : " << string(v_sort.begin(), v_sort.end()) << endl;
	cout << "Bubble: " << t_bubble << "s | Insertion: " << t_insertion 
		 << "s | Selection: " << t_selection << "s | Built-in sort: " << t_sort << "s" << endl;

    cout << endl <<endl;
    cout << endl <<endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout <<endl<<"TEMPI DI ESECUZIONE DI BubbleSort, InsertionSort, SelectionSort AL VARIARE DELLA DIMENSIONE IN POTENZA DI 2"<<endl
	<<"DELTA > 0 ---> funzione Sort di algorithm più veloce" <<endl <<endl;
    
    cout << "\n--- Benchmark Tipo: INTERI ---\n";
    for (int i = 1; i < 14; i++) {
        vector<int> base_vector(potenze_due[i-1]);
        rf.fill(base_vector, 1, 100000);

        vector<int> vec_bubble = base_vector;
        vector<int> vec_insertion = base_vector;
        vector<int> vec_selection = base_vector;


        tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
        tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
        tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
        tc.tic(); sort(vec_selection.begin(), vec_selection.end()); double time_sort = tc.toc();

        cout << "Size: " << potenze_due[i-1]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection << "s"
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort << "s\n";
    }
    
    cout << "\n--- Benchmark Tipo: DOUBLE ---\n";
    for (int i = 1; i < 14; i++) {
        vector<double> base_vector(potenze_due[i-1]);
        rf.fill(base_vector, 1.0, 100000.0);

        vector<double> vec_bubble = base_vector;
        vector<double> vec_insertion = base_vector;
        vector<double> vec_selection = base_vector;


        tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
        tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
        tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
        tc.tic(); sort(vec_selection.begin(), vec_selection.end()); double time_sort = tc.toc();

        cout << "Size: " << potenze_due[i-1]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection << "s"
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort << "s\n";
    }
    

	cout << "\n--- Benchmark Tipo: FLOAT ---\n";
    for (int i = 1; i < 14; i++) {
        vector<float> base_vector(potenze_due[i-1]);
        rf.fill(base_vector, 1.0f, 100000.0f);

        vector<float> vec_bubble = base_vector;
        vector<float> vec_insertion = base_vector;
        vector<float> vec_selection = base_vector;


        tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
        tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
        tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
        tc.tic(); sort(vec_selection.begin(), vec_selection.end()); double time_sort = tc.toc();

        cout << "Size: " << potenze_due[i-1]
                  << " | Bubble: " << time_bubble
                  << "s | Insertion: " << time_insertion
                  << "s | Selection: " << time_selection << "s"
                  << "" << " ---> Delta time Bubble VS Sort: " << time_bubble - time_sort
                  << "s | Delta time Insertion VS Sort: " << time_insertion - time_sort
                  << "s | Delta time Selection VS Sort: " << time_selection - time_sort << "s\n";
    }
    

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <algorithm>

#include "randfiller.h"
#include "timecounter.h"
#include "sorts.hpp"
using namespace std;

tuple<double, double, double, double, double> media_bub_ins_sel(int dimensione){
	randfiller rf;
    timecounter tc;
    vector<int> base_vector(dimensione);
    rf.fill(base_vector, 1, 100000);
    
    vector<int> vec_bubble = base_vector;
    vector<int> vec_insertion = base_vector;
    vector<int> vec_selection = base_vector;
    vector<int> vec_merge = base_vector;
    vector<int> vec_quick = base_vector;
    vector<int> vec_my = base_vector;
    vector<int> vec_stds = base_vector;


    tc.tic(); bubblesort(vec_bubble); double time_bubble = tc.toc();
    tc.tic(); insertionsort(vec_insertion); double time_insertion = tc.toc();
    tc.tic(); selectionsort(vec_selection); double time_selection = tc.toc();
    tc.tic(); mergesort(vec_merge,0,vec_merge.size() -1); double time_merge = tc.toc();
    tc.tic(); quicksort(vec_quick,0,vec_quick.size() -1); double time_quick = tc.toc();
    
    /*
    tc.tic(); quicksort(vec_my,0,vec_my.size() -1); double time_my = tc.toc();
    tc.tic(); sort(vec_stds.begin(), vec_stds.end()); double time_stds = tc.toc();
    
    cout << "Dimensione: " << dimensione << " - tempi in ordine Bubble, Insertion, Selection, Merge, Quick, MySort, StdSort: " << time_bubble << ", " << time_insertion << ", " << time_selection << ", " << time_merge << ", " << time_quick << ", " << time_my  << ", " << time_stds << endl;
    */
    
    return {time_bubble, time_insertion, time_selection, time_merge, time_quick};
}


int main() {
    
	int N=200;
	vector<int> dim(N-1);
	vector<double> medie_time_bubble(N-1);
	vector<double> medie_time_insertion(N-1);
	vector<double> medie_time_selection(N-1);
	vector<double> medie_time_merge(N-1);
	vector<double> medie_time_quick(N-1);
	double somma_bubble = 0;
	double somma_insertion = 0;
	double somma_selection = 0;
	double somma_merge = 0;
	double somma_quick = 0;
	int controllo = 0;
	for(int i=0;i<N-1;i++){
		if(i==0){
			dim[i]=2;
		} else{
			dim[i]=5*i;
		}
	}
	
	for(int k = 0;k<N-1;k++){
		for(int j=0;j<100;j++){
			auto [time_bubble, time_insertion, time_selection, time_merge, time_quick] = media_bub_ins_sel(dim[k]);
			somma_bubble = somma_bubble + time_bubble;
			somma_insertion = somma_insertion + time_insertion;
			somma_selection = somma_selection + time_selection;
			somma_merge = somma_merge + time_merge;
			somma_quick = somma_quick + time_quick;
		}
		medie_time_bubble[k]=somma_bubble/100;
		medie_time_insertion[k]=somma_insertion/100;
		medie_time_selection[k]=somma_selection/100;
		medie_time_merge[k]=somma_merge/100;
		medie_time_quick[k]=somma_quick/100;
		
		
		if((medie_time_bubble[k]-medie_time_merge[k]>0)&&(medie_time_bubble[k]-medie_time_quick[k]>0)&&(medie_time_insertion[k]-medie_time_merge[k]>0)&&(medie_time_insertion[k]-medie_time_quick[k]>0)&&(medie_time_selection[k]-medie_time_merge[k]>0)&&(medie_time_selection[k]-medie_time_quick[k]>0)){
			controllo = controllo + 1;
		} else{
			controllo = 0;
		}
		
		if(controllo == 5){
			break;
		}
		
	}
	
	cout << endl << "Bubble VS Merge ---> Bubble più veloce fino alla dimensione: ";
    for(int i = 0; i < N-1; i++){
	    if(medie_time_bubble[i]-medie_time_merge[i]>0){
		    cout << 5*i <<endl;
		    break;
	    }
    }
    
    cout<< "Bubble VS Quick ---> Bubble più veloce fino alla dimensione: ";
    for(int i = 0; i < N-1; i++){
	    if(medie_time_bubble[i]-medie_time_quick[i]>0){
		    cout << 5*i <<endl;
		    break;
	    }
    }
    
    cout<<endl<<endl<< "Insertion VS Merge ---> Insertion più veloce fino alla dimensione: ";
    for(int i = 0; i < N-1; i++){
	    if(medie_time_insertion[i]-medie_time_merge[i]>0){
		    cout << 5*i <<endl;
		    break;
	    }
    }
    
    cout<< "Insertion VS Quick ---> Insertion più veloce fino alla dimensione: ";
    for(int i = 0; i < N-1; i++){
	    if(medie_time_insertion[i]-medie_time_quick[i]>0){
		    cout << 5*i <<endl;
		    break;
	    }
    }
    
    cout <<endl<<endl<< "Selection VS Merge ---> Selection più veloce fino alla dimensione: ";
    for(int i = 0; i < N-1; i++){
	    if(medie_time_selection[i]-medie_time_merge[i]>0){
		    cout << 5*i <<endl;
		    break;
	    }
    }
    
    cout<< "Selection VS Quick ---> Selection più veloce fino alla dimensione: ";
    for(int i = 0; i < N-1; i++){
	    if(medie_time_selection[i]-medie_time_quick[i]>0){
		    cout << 5*i <<endl<<endl;
		    break;
	    }
    }
    

    return 0;
}

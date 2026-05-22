#pragma once

#include <optional>
#include <iostream>
#include <vector>
#include <math.h>
//includo string per il controllo a riga 73
#include <string>
using namespace std;

template<typename T>
void bubblesort(vector<T>& vec)
{
    int N = vec.size();
    for (int i = 0; i < N - 1; i++) {
        for (int j = N - 1; j > i; j--) { 
            if (vec[j] < vec[j - 1]) {
                T key = vec[j];
                vec[j] = vec[j - 1];
                vec[j - 1] = key;
            }
        }
    }
}

template<typename T>
void insertionsort(vector<T>& vec)
{
	int N=vec.size();
	for (int j=1;j<N;j++){
		T key = vec[j];
		int i = j-1;
		while(i>=0 && vec[i]>key){
			vec[i+1] = vec[i];
			i=i-1;
		}
		vec[i+1]=key;
	}
}

template<typename T>
void selectionsort(vector<T>& vec)
{
	int N=vec.size();
	for (int i=0;i<N;i++){
		int min = i;
		for(int j = i+1; j<N; j++){
			if(vec[j]<vec[min]){
				min = j;
			}
		}
		
		T key = vec[i];
		vec[i] = vec[min];
		vec[min] = key;
	}
	return;
}

/*
Prima implementazione errata nella gestione del valore "infinito"
template<typename T>
void merge(vector<T>& vec, int p, int q, int r)
{	
	int n1=q-p+1;
	int n2=r-q;
	vector<T> L(n1+1);
	vector<T> R(n2+1);
	for(int i=0; i<n1; i++){
		L[i]=vec[p+i];
	}
	for(int j=0; j<n2; j++){
		R[j]=vec[q+j+1];
	}
	if constexpr (is_same_v<T, std::string>) {
		//Help from Gemini
		L[n1] = "{";
		R[n2] = "{"; 
	} else {
		L[n1] = 100000;
		R[n2] = 100000;
	}
	int i=0;
	int j=0;
	for(int k=p;k<=r;k++){
		if(L[i]<=R[j]){
			vec[k]=L[i];
			i++;
		}else{
			vec[k]=R[j];
			j++;
		}
	}
	return;
}
*/

//Implementazione algoritmo mergesort corretta con triplo ciclo while
template<typename T>
void merge(std::vector<T>& vec, int sx, int centro, int dx) {
    int n_1 = centro - sx + 1;
    int n_2 = dx - centro;
    std::vector<T> L;
    std::vector<T> R;
    L.resize(n_1);
    R.resize(n_2);
    
    for(int j=0; j< n_1; ++j) {
        L[j]=vec[sx + j];
    }
    
    for(int i=0; i<n_2; ++i) {
        //Aggiunto il +1  per partire dalla seconda metà
        R[i]=vec[centro +1 +i]; 
    }
    
    int i=0;
    int j=0;
    int k=sx;
    
    //Inserisco un ciclo wile che si ferma quando uno tra L o R finisce
    while(i<n_1 && j<n_2) {
        if(L[i]<=R[j]) {
            vec[k]=L[i];
            i=i+1;
        } else {
            vec[k]=R[j];
            j=j+1;
        }
        k=k+1;
    }
    
    //Se è avanzato qualcosa in L lo aggiungo (gli elementi di L sono già ordinati)
    while(i < n_1) {
        vec[k]=L[i];
        i=i+1;
        k=k+1;
    }
    
    //Se è avanzato qualcosa in R lo aggiungo (gli elementi di R sono già ordinati)
    while(j<n_2) {
        vec[k]=R[j];
        j=j+1;
        k=k+1;
    }
}


template<typename T>
void mergesort(vector<T>& vec, int left, int right)
{	
	if(left<right){
		int center = floor((left+right)/2);
		mergesort(vec, left, center);
		mergesort(vec, center+1, right);
		merge(vec, left, center, right);
	}
	return;
}

template<typename T>
int partition(vector<T>& vec, int left, int right)
{
	T x = vec[right];
	int i = left-1;
	for(int j=left;j<=right-1;j++){
		if(vec[j]<=x){
			i++;
			T dummy = vec[i];
			vec[i]=vec[j];
			vec[j]=dummy;
		}
	}
	T dummy = vec[i+1];
	vec[i+1]=vec[right];
	vec[right]=dummy;
	return i+1;
}


template<typename T>
void quicksort(vector<T>& vec, int p, int r)
{
	if(p<r){
		int q = partition(vec,p,r);
		quicksort(vec,p,q-1);
		quicksort(vec,q+1,r);
	}
	return;
}

template<typename T>
void insertionsort_edit(vector<T>& vec, int p, int r)
{
	for (int j=p+1;j<=r;j++){
		T key = vec[j];
		int i = j-1;
		while(i>=0 && vec[i]>key){
			vec[i+1] = vec[i];
			i=i-1;
		}
		vec[i+1]=key;
	}
}

template<typename T>
void my_sort(vector<T>& vec, int p, int r)
{
	if((r-p)<285){
		insertionsort_edit(vec, p, r);
	}else {
		if(p<r){
			int q = partition(vec,p,r);
			my_sort(vec,p,q-1);
			my_sort(vec,q+1,r);
		}
	}
	return;
}


template<typename T>
int issorted(const vector<T>& vec)
{
	int N=vec.size();
	for(int i=0;i<N-1;i++){
		if(vec[i]>vec[i+1]){
			return 1;
		}
	}
	return 0;
}
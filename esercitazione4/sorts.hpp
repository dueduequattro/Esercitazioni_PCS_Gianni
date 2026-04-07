#pragma once

#include <optional>
#include <iostream>
#include <vector>
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
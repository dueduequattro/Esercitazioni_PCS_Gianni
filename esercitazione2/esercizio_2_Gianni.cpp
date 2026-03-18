#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int main()
{
	static const int N = 15;
	double arr[N];
	double ordine;
	double minimo;
	double massimo;
	double media = 0;
	double varianza = 0;
	double dev_st;
	bool controllo=true;
	
	for(int i=0;i<N;i++){
		arr[i]=8*i*pow(-1,i);
		media = media + arr[i];
		if(i==0){
			minimo = arr[i];
			massimo = arr[i];
		} else{
			minimo = min(minimo,arr[i]);
			massimo = max(massimo,arr[i]);
		}
	}
	media=media/N;
	
	for(int i=0;i<N;i++){
		varianza = varianza + pow(media-arr[i], 2);
	}
	
	cout << endl << "Il minimo del vettore arr e': " << minimo << endl;
	cout << "Il massimo del vettore arr e': " << massimo << endl;
	cout << "La media del vettore arr e': " << media << endl;
	cout << "La deviazione standard del vettore arr e': " << sqrt(varianza/N) << endl << endl;
	
	cout << "Esercizio facoltativo"<<endl<< "vettore originale: ";
	for(int i=0;i<N;i++){
		cout << arr[i] << " "; 
	}
	cout << endl;
	
	while(controllo){
		controllo = false;
		for(int i=0;i<N-1;i++){
			if(arr[i]>arr[i+1]){
				controllo = true;
				ordine = arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=ordine;
			}
		}
	}
	
	cout << "vettore ordinato con Bubblesort: ";
	for(int i=0;i<N;i++){
		cout << arr[i] << " "; 
	}
	
}
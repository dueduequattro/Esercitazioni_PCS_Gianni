#include "rational.hpp"
#include <iostream>
#include <numeric>

using namespace std;

int main() {
	int a_1;
	int a_2;
	int b_1;
	int b_2;
	cout << "Inserisci il numeratore del primo numero: ";
	cin >> a_1;
	cout << "Inserisci il denominatore del primo numero: ";
	cin >> b_1;
	cout << "Inserisci il numeratore del secondo numero: ";
	cin >> a_2;
	cout << "Inserisci il denominatore del secondo numero: ";
	cin >> b_2;
	cout << "\n";
    rational<int> n_1(a_1,b_1);
    rational<int> n_2(a_2,b_2);
    
    rational<int> somma = n_1 + n_2;
    rational<int> differenza = n_1 - n_2;
    rational<int> prodotto = n_1 * n_2;
    rational<int> divisione = n_1 / n_2;
    
    cout << "Numeratore primo numero: " << n_1.num() << "\n"<< "Denominatore primo numero " << n_1.den() << "\n";
    cout << "Numeratore secondo numero: " << n_2.num() << "\n"<< "Denominatore secondo numero " << n_2.den() << "\n"<< "\n";
    
    if (prodotto.num()==0 && prodotto.den()==0){
	    cout << "Risultato Prodotto: NaN" << "\n";
    } else if (prodotto.num()>0 && prodotto.den()==0){
	    cout << "Risultato Prodotto: +Inf" << "\n";
    } else if (prodotto.num()<0 && prodotto.den()==0){
	    cout << "Risultato Prodotto: -Inf" << "\n";
    } else{
	    cout << "Risultato Prodotto: " << prodotto << "\n";
    }
    
    if (divisione.num()==0 && divisione.den()==0){
	    cout << "Risultato Divisione: NaN" << "\n";
    } else if (divisione.num()>0 && divisione.den()==0){
	    cout << "Risultato Divisione: +Inf" << "\n";
    } else if (divisione.num()<0 && divisione.den()==0){
	    cout << "Risultato Divisione: -Inf" << "\n";
    } else{
	    cout << "Risultato Divisione: " << divisione << "\n";
    }
    
    
    if ((n_1.num()==0 && n_1.den()==0) || (n_2.num()==0 && n_2.den()==0)){
	    cout << "Risultato Somma: NaN" << "\n";
	    cout << "Risultato Differenza: NaN" << "\n";
    } else if ((n_1.num()>0 && n_1.den()==0) && (n_2.num()>0 && n_2.den()==0)){
	    cout << "Risultato Somma: Inf" << "\n";
	    cout << "Risultato Differenza: NaN" << "\n";
    } else if ((n_1.num()<0 && n_1.den()==0) && (n_2.num()<0 && n_2.den()==0)){
	    cout << "Risultato Somma: -Inf" << "\n";
	    cout << "Risultato Differenza: NaN" << "\n";
    }  else if ((n_1.num()>0 && n_1.den()==0) && (n_2.num()<0 && n_2.den()==0)){
	    cout << "Risultato Somma: NaN" << "\n";
	    cout << "Risultato Differenza: +Inf" << "\n";
    } else if ((n_1.num()<0 && n_1.den()==0) && (n_2.num()>0 && n_2.den()==0)){
	    cout << "Risultato Somma: NaN" << "\n";
	    cout << "Risultato Differenza: -Inf" << "\n";
    } else if ((n_1.num()>0 && n_1.den()==0) && n_2.den()!=0){
	    cout << "Risultato Somma: +Inf" << "\n";
	    cout << "Risultato Differenza: +Inf" << "\n";
    } else if ((n_1.num()<0 && n_1.den()==0) && n_2.den()!=0){
	    cout << "Risultato Somma: -Inf" << "\n";
	    cout << "Risultato Differenza: -Inf" << "\n";
    } else if ((n_2.num()>0 && n_2.den()==0) && n_1.den()!=0){
	    cout << "Risultato Somma: +Inf" << "\n";
	    cout << "Risultato Differenza: -Inf" << "\n";
    } else if ((n_2.num()<0 && n_2.den()==0) && n_1.den()!=0){
	    cout << "Risultato Somma: -Inf" << "\n";
	    cout << "Risultato Differenza: +Inf" << "\n";
    } else{
		cout << "Risultato Somma: " << somma << "\n";
		cout << "Risultato Differenza: " << differenza << "\n";
    }
    
    return 0;
}
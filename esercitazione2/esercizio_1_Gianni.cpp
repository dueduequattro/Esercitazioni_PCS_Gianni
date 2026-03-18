#include <iostream>
using namespace std;

int main()
{
double ad[4] = {0.0, 1.1, 2.2, 3.3};
float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
int ai[3] = {0, 1, 2};

int x = 1;
float y = 1.1;

(&y)[1] = 0;

cout << x << "\n"<<"\n";
cout << "Indirizzi del vettore ad: " << "\n";
for (int i=0;i<4;i++){
	cout << &ad[i] << "\n";
}
cout << "\n" << "Indirizzi del vettore af: " << "\n";
for (int i=0;i<8;i++){
	cout << &af[i] << "\n";
}
cout << "\n" << "Indirizzi del vettore ai: " << "\n";
for (int i=0;i<3;i++){
	cout << &ai[i] << "\n";
}
cout << "\n" << "Indirizzo della variabile x: " << "\n";
cout << &x << "\n";
cout << "\n" << "Indirizzo della variabile y: " << "\n";
cout << &y << "\n";

return 0;
}
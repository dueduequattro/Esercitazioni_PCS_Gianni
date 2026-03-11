#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char *argv[]){
	
	string filename;
	if (argc!=2){
		cout << "Errore, inserire il nome di un file." << endl;
		return 1;
		}
	filename = argv[1];
	ifstream ifs(filename);
	
	if (!ifs.is_open()) {
		cout << "Errore: Impossibile aprire il file '" << filename << "'." << endl;
		cout << "Verifica che il nome sia corretto e che il file sia nella cartella del progetto." << endl;
	return 1;
	}

	cout << "File caricato correttamente." << endl << endl;
	if (ifs.is_open()){
		for(int i=0; i<3; i++){
			string location;
			double temp_1;
			double temp_2;
			double temp_3;
			double temp_4;
			double media;
			ifs >> location >> temp_1 >> temp_2 >> temp_3 >> temp_4;
			media=(temp_1+temp_2+temp_3+temp_4)/4;
			cout << "La temperatura media a " << location << " e' " << media << "\n";
		}
	}
	return 0;
}
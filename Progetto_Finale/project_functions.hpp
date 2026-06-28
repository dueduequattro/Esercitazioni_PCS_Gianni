#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <Eigen/Dense>
#include <concepts>
#include <algorithm>
#include <set>
#include <utility>


// Lettura File

struct valor_input {
    double peso;
    int nodo1;
    int nodo2;
};


struct RisultatoLettura {
    std::map<std::string, valor_input> circuito;
	std::vector<std::string> ordine_componenti;
    int resistori;
    bool controllo;
};


RisultatoLettura lettura_file(const int argc, const char *argv[]){
	RisultatoLettura res; //creo mappa per salvare gli elementi del circuito (l'ipotesi di assenza di elementi in parallelo mi permette di usare la stringa R# o V# come chiave)
	res.resistori = 0;
	res.controllo = true;
	  
	if (argc!=2){ //come visto nell'Esercitazione 1 devo ottenere in input una sola stringa unica contente il nome del file e questo si verifica solo se argc=2.
		std::cout << "Errore, inserire il nome di un file.\n";
		res.controllo = false;
		return res;
		}
	
	std::string filename;
	filename = argv[1];
	std::ifstream ifs(filename);
	
	//gestione errore lettura file
	if (!ifs.is_open()) {
		std::cout << "Errore: Impossibile aprire il file '" << filename << "'.\n";
		std::cout << "Verifica che il nome sia corretto e che il file sia nella cartella del progetto.\n";
		res.controllo = false;
	return res;
	}
	
	std::cout << "File caricato correttamente.\n\n";
	
	std::string key;
	valor_input v;
	std::string linea;
	
	while (std::getline(ifs, linea)) {
		
		// Senza queste due linee alla riga 85 viene stampata la stringa, poi linea che finisce con \r, quindi lo stream torna a capo e stampa
		// il carattere ' sovrascrivendo la lettera A.
		if (!linea.empty() && linea.back() == '\r') {
			linea.pop_back();
		}
		
		/* salta righe vuote o con solo spazi, tab o a capo (std::string::npos è una costante speciale di valore -1 che i metodi di std::string restituiscono quando non trovano quello che cercano
		find_dirst_not_of mi restituisce l'indice del primo carattere che non è uno di quelli elencati, se non trova nulla restituisce std::string::npos)*/
		if (linea.empty() || linea.find_first_not_of(" \t\r\n") == std::string::npos) continue;
		
		//std::istringstream è uno stream di input che legge da una stringa (quella passata tra parentesi) invece che da un file o dalla console.
		std::istringstream iss(linea);
		
		if (!(iss >> key >> v.peso >> v.nodo1 >> v.nodo2)) {
			// la riga non è vuota ma il formato è sbagliato
			std::cout << "Attenzione: riga malformata ignorata: '" << linea << "'\n";
			continue;
		}
		
		if (key[0] != 'R' && key[0] != 'V') {
			// accetto solo componenti che iniziano per 'R' o 'V'
			std::cout << "Attenzione: componente sconosciuto '" << key << "' ignorato nella riga: '" << linea << "'\n";
			continue;
		}
		
		res.circuito[key] = {v.peso, v.nodo1, v.nodo2}; //linea corretta
		res.ordine_componenti.push_back(key);
		if (key[0] == 'R') {
			res.resistori++;
		}
	}
	
	return res;
};


// Calcolo Sistema

struct dati_sistema {
	Eigen::MatrixXd B;
	Eigen::MatrixXd R;
	Eigen::VectorXd v;
};


template<typename I> requires std::integral<I>
dati_sistema calcola_sistema(const std::map<std::string, valor_input>& circuito, const std::vector<std::string>& ordine_componenti,
	const std::vector<std::vector<I>>& maglie, int num_resistori, int num_maglie) {
	
	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistori, num_maglie);
	Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistori, num_resistori);
	Eigen::VectorXd v = Eigen::VectorXd::Zero(num_maglie); 
	
	// Calcolo tutti gli archi delle maglie per non doverle ricalcolare ad ogni iterazione
    std::vector<std::set<std::pair<I, I>>> archi_maglie(num_maglie);
    for (int j = 0; j < num_maglie; j++) {
        for (size_t k = 0; k + 1 < maglie[j].size(); k++) {
            archi_maglie[j].insert({maglie[j][k], maglie[j][k+1]});
        }
    }
	
	int i_res = 0; // indice resistore (riga)
	
	for (const std::string& key : ordine_componenti) {
        
		auto valori = circuito.at(key); 
        I n1 = valori.nodo1;
        I n2 = valori.nodo2;
		
		if (key[0] == 'R') {
            // Aggiorno la diagonale di R 
            R(i_res, i_res) = valori.peso;
			
			// Il verso di percorrenza dell’arco è sempre dal nodo di indice minore a quello di indice maggiore
			I r_start = std::min(n1, n2);
			I r_end = std::max(n1, n2);
			
			for (int j = 0; j < num_maglie; j++) { // j indice maglia (colonna)
				
				// Verso concorde al grafo
                if (archi_maglie[j].contains({r_start, r_end})) {
                    B(i_res, j) = 1; 
                }
				
				// Verso discorde al grafo
                else if (archi_maglie[j].contains({r_end, r_start})) {
                    B(i_res, j) = -1;
                }
            }
			
            i_res++;
		}	
	
		else if (key[0] == 'V') {
			for (int j = 0; j < num_maglie; j++) {
			
				// Da - a +
				if (archi_maglie[j].contains({n2, n1})) { 
					v(j) += valori.peso;
				}
               
				// Da + a -
				else if (archi_maglie[j].contains({n1, n2})) { 
					v(j) -= valori.peso;
				}
			}	
		}
	}
	
	dati_sistema risultato;
	risultato.B = B;
	risultato.R = R;
	risultato.v = v;
	
	return risultato;
}


// Stampa

void stampa(const std::vector<std::string>& ordine_componenti, const Eigen::VectorXd& tensioni, const Eigen::VectorXd& correnti) {
	int i_res=0;
	std::cout.precision(4);
	for (const std::string& key : ordine_componenti) {
        if (key[0] == 'R') {
			std::cout << key << ": V = " << tensioni(i_res) << " volts, I = " << correnti(i_res) << " amps.\n";
			i_res++;
		}
	}
}
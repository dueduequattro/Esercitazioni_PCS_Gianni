#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <eigen3/Eigen/Dense>

#include "fifo_and_lifo.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "visita.hpp"
#include "dijkstra.hpp"

struct valor_input {
    double peso;
    int nodo1;
    int nodo2;
};

struct RisultatoLettura {
    std::map<std::string, valor_input> circuito;
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
		
		res.circuito[key] = {v.peso, v.nodo1, v.nodo2}; //linea corretta
		if (key[0] == 'R') res.resistori++;
	}
	
	return res;
};


int main(const int argc, const char *argv[]){
	RisultatoLettura res = lettura_file(argc, argv);
	
	
	if (res.controllo == false){ //termino il programma se ho avuto un errore in fase di lettura/apertura file
		return 1;
	}
	
	Eigen::VectorXd v_res(res.resistori); //costruisco e riempo il vettore v_res contenente i valori delle resistenze per poi poter costruire comodamente la matrice R, inoltre creo il grafo corrispondente al circuito in input
	int indx = 0; 
	undirected_graph<int> grafo_circuito;
	for(const auto& [chiave_1,nodi] : res.circuito){
		if(chiave_1[0]=='R'){
			v_res(indx) = nodi.peso;
        	indx++;
		}
		grafo_circuito.add_edge(nodi.nodo1,nodi.nodo2);
	}
	
	Eigen::MatrixXd R = v_res.asDiagonal();
	//Eigen::MatrixXd B(resistori,c_minimi);
	
	lifo<int> s;
	undirected_graph<int> grafo_circuito_dfs = graph_visit (grafo_circuito, grafo_circuito.all_nodes()[0], s); //visita_dfs del grafo originale
	undirected_graph<int> coalbero = grafo_circuito - grafo_circuito_dfs; //coalbero ottenuto come differenza del grafo originale - visita_dfs
	undirected_graph<int> grafo_maglie = grafo_circuito_dfs; //creo una copia della visita T di G
	
	//riempo con gli archi mancati per ottenere il grafo con le maglie completo
	for(const auto& arco : coalbero.all_edges()){
		grafo_maglie.add_edge(arco.from(), arco.to());
	}
	
	
	std::vector<std::vector<int>> c_minimi = cicli_minimi(grafo_circuito, coalbero);
	
	
	std::cout << "Stampo grafo circuito \n";
	grafo_circuito.print();
	
	std::cout << "\nStampo grafo circuito dfs \n";
	grafo_circuito_dfs.print();
	
	std::cout << "\nStampo coalbero\n";
	coalbero.print();
	
	std::cout << "\nStampo grafo_maglie\n";
	grafo_maglie.print();
	
	std::cout << "\nNumero resistori: " << res.resistori << "\n";
	std::cout << "Matrice Resistori: \n" << R << "\n\n";
	
	return 0;
}
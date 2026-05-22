#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "fifo_and_lifo.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "visita.hpp"

struct valor_input {
    double peso;
    int nodo1;
    int nodo2;
};

int main(int argc, const char *argv[]){
	
	std::string filename;
	//come visto nell'Esercitazione 1 devo ottenere in input una sola stringa unica contente il nome del file e questo si verifica solo se argc=2.  
	if (argc!=2){
		std::cout << "Errore, inserire il nome di un file.\n";
		return 1;
		}
	filename = argv[1];
	//classe ifstream di std per lettura file vista nell'Esercitazione 1
	std::ifstream ifs(filename);
	
	/*
	********************
	DOMANDA DA FARE: dobbiamo gestire eventuali linee vuote nel file di input con sstream?
	********************
	*/
	
	if (!ifs.is_open()) {
		std::cout << "Errore: Impossibile aprire il file '" << filename << "'.\n";
		std::cout << "Verifica che il nome sia corretto e che il file sia nella cartella del progetto.\n";
	return 1;
	}

	std::cout << "File caricato correttamente.\n\n";
	//uso array e non vector perchè gli elementi sono esattamente tre
	std::map<std::string, valor_input> circuito;
	std::string key;
	double v1; 
	int v2, v3;
	
	if (ifs.is_open()) {
		//con questo costrutto al lettura dell'input è robusta a prescindere da quanti spazi ci sono tra i valori. Inoltre il while mi permette di scorrere una riga alla volta.
		while (ifs >> key >> v1 >> v2 >> v3) {
			circuito[key] = {v1, v2, v3};
		}
	}
	
	/*
	PROVA DI STAMPA
	for (const auto& [chiave, vec] : circuito) {
    	std::cout << chiave << ": ";
		for (const double val : vec) {
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
	*/
	
	undirected_graph<int> grafo_circuito;
	for(const auto& [chiave_1,nodi] : circuito){
		grafo_circuito.add_edge(nodi.nodo1,nodi.nodo2);
	}
	std::cout << "Stampo grafo circuito \n";
	grafo_circuito.print();
	
	lifo<int> s;
	undirected_graph<int> grafo_circuito_dfs = graph_visit (grafo_circuito, grafo_circuito.all_nodes()[0], s);
	
	std::cout << "\nStampo grafo circuito dfs \n";
	grafo_circuito_dfs.print();
	
	undirected_graph<int> coalbero = grafo_circuito - grafo_circuito_dfs;
	std::cout << "\nStampo coalbero\n";
	coalbero.print();
	
	//creo una copia della visita T di G
	undirected_graph<int> grafo_maglie = grafo_circuito_dfs;
	//riempo con gli archi mancati per ottenere le maglie
	for(const auto& arco : coalbero.all_edges()){
		grafo_maglie.add_edge(arco.from(), arco.to());
	}
	std::cout << "\nStampo grafo_maglie\n";
	grafo_maglie.print();
	
	return 0;
}
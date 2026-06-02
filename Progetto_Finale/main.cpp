#include <cstdlib>
#include "header.hpp"


int main(const int argc, const char *argv[]){
	
	RisultatoLettura res = lettura_file(argc, argv);
	
	if (res.controllo == false){ //termino il programma se ho avuto un errore in fase di lettura/apertura file
		return 1;
	}
	
	undirected_graph<int> grafo_circuito;
	for(const auto& [chiave_1,nodi] : res.circuito){
		grafo_circuito.add_edge(nodi.nodo1,nodi.nodo2);
	}
		
	lifo<int> s;
	undirected_graph<int> grafo_circuito_dfs = graph_visit(grafo_circuito, grafo_circuito.all_nodes()[0], s); //visita_dfs del grafo originale
	undirected_graph<int> coalbero = grafo_circuito - grafo_circuito_dfs; //coalbero ottenuto come differenza del grafo originale - visita_dfs
	
	std::vector<std::vector<int>> maglie = cicli_minimi(grafo_circuito, coalbero);
	int num_maglie = maglie.size();
	
	dati_sistema dati = calcola_sistema(res.circuito, maglie, res.resistori, num_maglie);
	Eigen::MatrixXd B = dati.B;
	Eigen::MatrixXd R = dati.R;
	Eigen::VectorXd v = dati.v;
	
	Eigen::MatrixXd A = B.transpose() * R * B;
	
	// Soluzione sistema lineare
	risultato_gc esito_sistema = gradiente_coniugato(A, v);
	
	if (!esito_sistema.conv) {
		std::cerr << "Errore: Il metodo del Gradiente Coniugato non ha raggiunto la convergenza (Iterazioni: " << esito_sistema.it << ").\n"
                  << "Verificare la correttezza del grafo.\n";
		return EXIT_FAILURE;
	}
	
	Eigen::VectorXd correnti_maglie = esito_sistema.sol;
	Eigen::VectorXd correnti_resistori = B * correnti_maglie;
	Eigen::VectorXd tensioni_resistori = R * correnti_resistori;
	
	int indice_matrice = 0; 
	for (const auto& [key, valori] : res.circuito) {
		if (key[0] == 'R') {
			std::cout << key << ": V = " << tensioni_resistori(indice_matrice) << " volts, I = " << correnti_resistori(indice_matrice) << " amps.\n";
			indice_matrice++; 
		}
	}
	
	return EXIT_SUCCESS;
}
#include <cstdlib>
#include "grafo.hpp"
#include "project_functions.hpp"
#include "gradiente_coniugato.hpp"
#include "algoritmi_cicli.hpp"


int main(const int argc, const char *argv[]){
	
	RisultatoLettura res = lettura_file(argc, argv);
	
	if (res.controllo == false){ //termino il programma se ho avuto un errore in fase di lettura/apertura file
		return EXIT_FAILURE;
	}
	
	// Algoritmo di De Pina per cicli minimi
	std::vector<std::vector<int>> maglie = algoritmo_depina(res.circuito);
	
	// Algoritmo basato su DFS
	//std::vector<std::vector<int>> maglie = algoritmo_dfs(res.circuito);
	
	int num_maglie = maglie.size();

	dati_sistema dati = calcola_sistema(res.circuito, res.ordine_componenti, maglie, res.resistori, num_maglie);
	Eigen::MatrixXd B = dati.B;
	Eigen::MatrixXd R = dati.R;
	Eigen::VectorXd v = dati.v;
	
	Eigen::MatrixXd A = B.transpose() * R * B;
	
	// Soluzione sistema lineare
	const int it_extra = 0;
	const int it_max = num_maglie + it_extra;
	const double tol = 1.0e-13;
	risultato_gc esito_sistema = gradiente_coniugato(A, v, it_max, tol);
	
	if (!esito_sistema.conv) {
		std::cerr << "Errore: Il metodo del Gradiente Coniugato non ha raggiunto la convergenza (Iterazioni: " << esito_sistema.it << ").\n"
                  << "Verificare la correttezza del grafo.\n";
		return EXIT_FAILURE;
	}

	Eigen::VectorXd correnti_maglie = esito_sistema.sol;
	Eigen::VectorXd correnti_resistori = B * correnti_maglie;
	Eigen::VectorXd tensioni_resistori = R * correnti_resistori;
	
	stampa(res.ordine_componenti, tensioni_resistori, correnti_resistori);
	
	return EXIT_SUCCESS;
}
	
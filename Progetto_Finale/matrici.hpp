#include <eigen3/Eigen/Dense>

struct dati_sistema {
	Eigen::MatrixXd B;
	Eigen::VectorXd v;
}

template<typename I> requires std::integral<I>
dati_sistema matrice_incidenza(const std::map<std::string, valor_input>& circuito, const std::vector<std::vector<I>>, int num_resistori, int num_maglie) {
	
	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistori, num_maglie);
	Eigen::VectorXd v = Eigen::VectorXd::Zero(num_maglie); 
	
	/*
	per ogni ciclo j-
	    ricavo ogni arco nel verso giusto e nel verso opposto
	    per ogni elemento di circuito i
	        se è nel ciclo
	            se è R
		            se è nel verso giusto 
						B[i][j] = 1
					se è nel verso sbagliato
					    B[i][j] = -1
				se è V
					se è nel verso giusto
					    v[j] += peso
					se è nel verso sbagliato
						v[j] -= peso
	*/

	int i = 0;
	int j = 0;
	for (const auto& ciclo : maglie) {
		std::set<std::pair<I, I>> verso_giusto;
		std::set<std::pair<I, I>> verso_opposto;
		
		for (int k=0; i<ciclo.size()-1; k++) {
			I u = ciclo[k];
			I v = ciclo[k+1];
			
			std::pair<I, I> arco_giusto = {u,v};
			std::pair<I, I> arco_giusto = {v,u};
			verso_giusto.insert(arco_giusto);
			verso_opposto.insert(arco_opposto);
		}
		
		for (const auto& [key, valori] : circuito) {
			I from = valori.nodo1;
			I to = valori.nodo2;
			
			std::pair<I,I> arco = {from, to};
			
			if (key[0]=='R') {
				if (verso_giusto.contains(arco)) {
					B[i][j] = 1;
				}
				else if (verso_opposto.contains(arco)) {
					B[i][j] = -1;
				}
				i++;
			}
			
			else if (key[0]=='V') {
				if (verso_giusto.contains(arco)) {
					v[j] += valori.peso;
				}
				else if (verso_opposto.contains(arco)) {
					v[j] -= valori.peso;
				}
			}
		}
		
		j++;
	}
	
	dati_sistema risultato;
	risultato.B = B;
	risultato.v = v;
	
	return risultato;
	
}

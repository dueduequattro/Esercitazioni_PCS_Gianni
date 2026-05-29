#pragma once
#include <iostream>
#include <vector>
#include <cmath> // per std::abs
#include "visita.hpp"
#include "fifo_and_lifo.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "dijkstra.hpp"

template<typename I> requires std::integral<I>
undirected_graph<I> duplica(const undirected_graph<I>& grafo, const std::vector<std::vector<int>>& S, const int i){
	undirected_graph<I> grafo_duplica;
	for(const auto& nodo : grafo.all_nodes()){
		//se ci fosse un nodo zero ci sarebbe un problema: ipotizzo etichetta nodi>=1
		grafo_duplica.add_node(nodo);
		grafo_duplica.add_node(-nodo);
	}
	
	auto archi_grafo_1 = grafo.all_edges();
	
	int idx = 0;
	for(const auto& e_1 : archi_grafo_1){
		if(S[i][idx]==1){
			grafo_duplica.add_edge(e_1.from(),-e_1.to());
			grafo_duplica.add_edge(-e_1.from(),e_1.to());
		} else {
			grafo_duplica.add_edge(e_1.from(),e_1.to());
			grafo_duplica.add_edge(-e_1.from(),-e_1.to());
		}
		
		idx++;
	}
	return grafo_duplica;
}

template<typename I> requires std::integral<I>
std::vector<std::vector<I>> depina(const undirected_graph<I>& grafo, std::vector<std::vector<int>>& S, const int k, const int m){
	std::vector<std::vector<I>> cicli(k);
	
	for(int i = 0; i<k; i++){
		undirected_graph<I> grafo_duplica = duplica(grafo, S, i);
		
		int distanza_minore = 2*(grafo.all_nodes().back());
		I nodo_migliore = grafo.all_nodes()[0];
		std::map<I, std::optional<I>> predecessori;
		
		// Trovo nodo migliore, ovvero il cui cammino minimo da v- a v+ è di lunghezza minore per ogni v
		for(const auto& v : grafo.all_nodes()){
			dijkstra_result<I> r_dij = dijkstra(grafo_duplica, -v);
			int distanza = r_dij.dist[v];
			
			if (distanza < distanza_minore){
				distanza_minore = distanza;
				nodo_migliore = v;
				predecessori = r_dij.pred;
			}
		}
		std::vector<I> nodi_cammino(distanza_minore + 1);
		nodi_cammino[0] = nodo_migliore;
		
		// Recupero ciclo minimo in G'
		// Così leggo il cammino da v+ a v-, ovvero leggo l'esplorazione al contrario. Ai fini dell'esercitazione è indifferente
		for(int step = 1; step <= distanza_minore; step++){
			nodi_cammino[step] = predecessori[nodi_cammino[step-1]].value();
		}
		
		// Prendo i valori assoluti per avere ciclo minimo in G
		for(int step = 0; step <= distanza_minore; step++) {
            nodi_cammino[step] = std::abs(nodi_cammino[step]);
        }
		
		cicli[i] = nodi_cammino;
		
		// Calcolo C_i per aggiornare S
		std::vector<int> C_i(m, 0); 
		
		for(int step = 0; step < distanza_minore; step++) {
			I u = nodi_cammino[step];
			I w = nodi_cammino[step+1];
			
			// Creo l'arco per cercarlo nel grafo originale
			undirected_edge<I> arco_ciclo(u, w);
			
			// Trovo il suo indice in G
			auto opt_idx = grafo.edge_number(arco_ciclo);
			if(opt_idx.has_value()) {
				// Assegno 1 in posizione corretta
				C_i[opt_idx.value()] = 1; 
			}
		}
		
		// Aggiornamento S_j
		for (int j = i+1; j < k; j++) {
			int prod_scalare = 0;
			
			// Calcolo prodotto scalare modulo 2 confrontando C[i] e S[j]
			for (int arco = 0; arco < m; arco++) {
				if (C_i[arco] == 1 && S[j][arco] == 1) {
					prod_scalare++;
				}
			}
			
			// Se è dispari, aggiorno S[j]
			if (prod_scalare % 2 == 1) {
				for (int arco = 0; arco < m; arco++) {
					// Operatore XOR bit a bit
					S[j][arco] = S[j][arco] ^ S[i][arco]; 
				}
			}
		}
	}
	
	return cicli;
}


template<typename I> requires std::integral<I>
std::vector<std::vector<I>> cicli_minimi(const undirected_graph<I>& grafo, const undirected_graph<I>& coalbero){
	int m = grafo.all_edges().size();
	int k = coalbero.all_edges().size();
	
	/* S è un vettore di k = numero archi coalbero vettori di lunghezza m = numero archi grafo originale. 
	Per ogni i in [k] (arco del coalbero) il vettore S_i ha elemento uguale a 1 nella posizione j in [m] (arco del grafo originale) dove j è l'indice dello stesso arco ma rispetto all'ordinamento del grafo originale 
	In altre parole S si può vedere come una matrice dove S_ij = 1 se l'arco in posizione i nel coalbero è l'arco in posizione j nel grafo originale e zero altrimenti.
	*/
	std::vector<std::vector<int>> S(k, std::vector<int>(m));
	
	// superfluo inizializzare a questo punto
	// std::vector<std::vector<int>> C(k, std::vector<int>(m));
	
	int i = 0;
	for(const auto& e : coalbero.all_edges()){
		auto opt_idx = grafo.edge_number(e);
		
		if (opt_idx.has_value()) {
			size_t idx = opt_idx.value();
            S[i][idx] = 1;
		}
		i++;		
	}
	std::vector<std::vector<I>> cicli = depina(grafo, S, k, m);
	return cicli;
};


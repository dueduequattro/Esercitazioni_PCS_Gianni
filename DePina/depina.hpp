#pragma once
#include <iostream>
#include <vector>
#include "visita.hpp"

#include "fifo_and_lifo.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "dijkstra.hpp"

template<typename I> requires std::integral<I>
std::vector<std::vector<I>> depina(const undirected_graph<I>& grafo, const std::vector<I>& S, const int k, const int m){
	for(int i = 0; i<k; i++){
		undirected_graph<I> grafo_duplica = duplica(grafo, S, i);
		
		int distanza_minore = 2*(grafo.all_nodes().back())
		I nodo_migliore = grafo.all_nodes()[0];
		std::map<I, std::optional<I>> predecessori;
		for(const auto& v : grafo.all_nodes()){
			dijkstra_result<int> r_dij = dijkstra(grafo_duplica, -v);
			int distanza = r_dij.dist[v];
			
			if (distanza < distanza_minore){
				distanza_minore = distanza;
				nodo_migliore = v;
				predecessori = r_dij.pred[v];
			}
		}
		std::vector<I> percorso_minimo(distanza_minore);
		percorso_minimo[0] = nodo_migliore;
		for(int i = 1; i<distanza; i++){
			percorso_minimo[i] = predecessori[percorso_minimo[i-1]];
		}
	}
}

template<typename I> requires std::integral<I>
undirected_graph<I> duplica(const undirected_graph<I>& grafo, const std::vector<std::vector<int>>& S, const int i){
	undirected_graph<I> grafo_duplica;
	for(const auto& nodo : grafo.all_nodes()){
		//se ci fosse nu nodo zero ci sarebbe un probelma: ipotizzo etichetta nodi>=1
		grafo_duplica.add_node(nodo);
		grafo_duplica.add_node(-nodo);
	}
	
	archi_grafo_1 = grafo.all_edges();
	
	for(const auto& e_1 : archi_grafo_1){
		auto it = std::find(archi_grafo_1.begin(), archi_grafo_1.end(), e_1);
		int idx = std::distance(archi_grafo_1.begin(), it);
		
		if(S[i][idx)]==1){
			grafo_duplica.add_edge(e_1.from(),-e_1.to());
			grafo_duplica.add_edge(-e_1.from(),e_1.to());
		} else {
			grafo_duplica.add_edge(e_1.from(),e_1.to());
			grafo_duplica.add_edge(-e_1.from(),-e_1.to());
		}
	}
	return grafo_duplica;
}


template<typename I> requires std::integral<I>
std::vector<std::vector<int>> cicli_minimi(const undirected_graph<I>& grafo, const undirected_graph<I>& coalbero){
	int m = grafo.all_edges().size();
	int k = coalbero.all_edges().size();
	
	/* S è un vettore di k = numero archi coalbero vettori di lunghezza m = numero archi grafo originale. 
	Per ogni i in [k] (arco del coalbero) il vettore S_i ha elemento uguale a 1 nella posizione j in [m] (arco del grafo originale) dove j è l'indice dello stesso arco ma rispetto all'ordinamento del grafo originale 
	In altre parole S si può vedere come una matrice dove S_ij = 1 se l'arco in posizione i nel coalbero è l'arco in posizione j nel grafo originale e zero altrimenti.
	*/
	std::vector<std::vector<int>> S(k, std::vector<int>(m));
	std::vector<std::vector<int>> C(k, std::vector<int>(m));
	
	auto archi_grafo = grafo.all_edges();

	int i = 0;
	for(const auto& e : coalbero.all_edges()){
		auto it = std::find(archi_grafo.begin(), archi_grafo.end(), e);
		int idx = std::distance(archi_grafo.begin(), it);
		S[i][idx] = 1;
		++i;
	}
	
	C = depina(grafo, S, k, m);
	return C;
};
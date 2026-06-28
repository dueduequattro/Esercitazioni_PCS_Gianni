#pragma once
#include <vector>
#include <map>
#include <string>
#include <concepts>
#include <set>
#include <optional>
#include "grafo.hpp"


// Algoritmo di De Pina


template<typename I> requires std::integral<I>
undirected_graph<I> duplica(const undirected_graph<I>& grafo, const I M, const std::vector<std::vector<int>>& S, const int i){
	undirected_graph<I> grafo_duplica;
	for(const auto& nodo : grafo.all_nodes()){
		grafo_duplica.add_node(nodo);
		grafo_duplica.add_node(nodo+M);
	}

	auto archi_grafo_1 = grafo.all_edges();

	int idx = 0;
	for(const auto& e_1 : archi_grafo_1){
		if(S[i][idx]==1){
			grafo_duplica.add_edge(e_1.from(),(e_1.to()+M));
			grafo_duplica.add_edge((e_1.from()+M),e_1.to());
		} else {
			grafo_duplica.add_edge(e_1.from(),e_1.to());
			grafo_duplica.add_edge((e_1.from()+M),(e_1.to()+M));
		}
		
		idx++;
	}
	return grafo_duplica;
}


template<typename I> requires std::integral<I>
std::vector<std::vector<I>> depina(const undirected_graph<I>& grafo, std::vector<std::vector<int>>& S, const int k, const int m){
	std::vector<std::vector<I>> cicli(k);
	
	const std::vector<I> nodi_grafo = grafo.all_nodes();
	if (nodi_grafo.empty()) return cicli;
	
	// Calcolo la maggiore etichetta associata al nodo
	I max_nodo = 0;
	for(const auto& v : nodi_grafo){
		if (v > max_nodo) {
			max_nodo = v;
		}
	}
	const I M = max_nodo + 1;
	const I max_id_duplica = M + max_nodo;
	
	for(int i = 0; i<k; i++){
		undirected_graph<I> grafo_duplica = duplica(grafo, M, S, i);
		
		int distanza_minore = 2*(nodi_grafo.back());
		I nodo_migliore = nodi_grafo[0];
		std::vector<std::optional<I>> predecessori;
		
		// Trovo nodo migliore, ovvero il cui cammino minimo da v- a v+ è di lunghezza minore per ogni v
		for(const auto& v : nodi_grafo){
			bfs_result<I> r_bfs = bfs_cammino_minimo(grafo_duplica, v+M, v, max_id_duplica);
			int distanza = r_bfs.dist[v];		
			
			if (distanza < distanza_minore){
				distanza_minore = distanza;
				nodo_migliore = v;
				predecessori = r_bfs.pred;
				
				if (distanza_minore == 3) {	
					break; // Il triangolo è il minore ciclo possibile
				}
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
			if (nodi_cammino[step] >= M) {
				nodi_cammino[step] -= M;
			}
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


std::vector<std::vector<int>> algoritmo_depina(const std::map<std::string, valor_input>& circuito) {
	undirected_graph<int> grafo_circuito;
	for(const auto& [chiave_1,nodi] : circuito){
		grafo_circuito.add_edge(nodi.nodo1,nodi.nodo2);
	}
		
	lifo<int> s;
	undirected_graph<int> grafo_circuito_dfs = graph_visit(grafo_circuito, grafo_circuito.all_nodes()[0], s); //visita_dfs del grafo originale
	undirected_graph<int> coalbero = grafo_circuito - grafo_circuito_dfs; //coalbero ottenuto come differenza del grafo originale - visita_dfs
	
	std::vector<std::vector<int>> maglie = cicli_minimi(grafo_circuito, coalbero);
	
	return maglie;
}


// Algoritmo cicli minimi basato su DFS


template<typename I> requires std::integral<I>
bool findpath(const undirected_graph<I>& albero_dfs, I u, I v, std::vector<I>& percorso, std::set<I>& visited) {
	
	visited.insert(u);
	percorso.push_back(u);
	
	if (u == v) {
		return true;
	}
	
	for (I vicino : albero_dfs.neighbors(u)) {
		if (!visited.contains(vicino)) {
			if (findpath(albero_dfs, vicino, v, percorso, visited)) {
				return true;
			}
		}
	}
	
	percorso.pop_back();
	
	return false;
}

template<typename I> requires std::integral<I>
std::vector<std::vector<I>> cicli_fondamentali_dfs(const undirected_graph<I>& albero_dfs, const undirected_graph<I>& coalbero){

	int k = coalbero.all_edges().size();
	std::vector<std::vector<I>> cicli;
	cicli.reserve(k);
	
	for (const auto& edge : coalbero.all_edges()) {
		I u = edge.from();
		I v = edge.to();

		std::vector<I> percorso;
		std::set<I> visited;
		
		if (findpath(albero_dfs, u, v, percorso, visited)) {
			
			// Aggiungo il nodo u alla fine per chiudere il ciclo
			percorso.push_back(u);
			cicli.push_back(percorso);
		}
		
	}
	
	return cicli;
}


std::vector<std::vector<int>> algoritmo_dfs(const std::map<std::string, valor_input>& circuito) {
	undirected_graph<int> grafo_circuito;
	for(const auto& [chiave_1,nodi] : circuito){
		grafo_circuito.add_edge(nodi.nodo1,nodi.nodo2);
	}
		
	lifo<int> s;
	undirected_graph<int> grafo_circuito_dfs = graph_visit(grafo_circuito, grafo_circuito.all_nodes()[0], s); //visita_dfs del grafo originale
	undirected_graph<int> coalbero = grafo_circuito - grafo_circuito_dfs; //coalbero ottenuto come differenza del grafo originale - visita_dfs
	
	std::vector<std::vector<int>> maglie = cicli_fondamentali_dfs(grafo_circuito_dfs, coalbero);
	
	return maglie;
}	
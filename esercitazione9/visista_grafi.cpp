#include <iostream>
#include <set>
#include <vector>

#include "fifo_and_lifo.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"

template<typename I> requires std::integral<I>
undirected_graph<I> graph_visit (const undirected_graph<I>& grafo, const I& nodo_partenza, auto contenitore){
	std::set<I> reached;
	undirected_graph<I> visita;
	
	contenitore.put(nodo_partenza);
	reached.insert(nodo_partenza);
	while(!contenitore.empty()){
		auto u_b = contenitore.get();
		if (u_b!=std::nullopt) {
			auto u = *u_b;
			for(const I& vicino : grafo.neighbors(u)) {
				if(!reached.contains(vicino)) {
					reached.insert(vicino);
					contenitore.put(vicino);
					visita.add_edge(u,vicino);
				}
    		}
		}
	}
	return visita;
}


template<typename I> requires std::integral<I>
undirected_graph<I> recursive_dfs (const undirected_graph<I>& grafo, const I& nodo_partenza){
	undirected_graph<I> visita_rec;
	std::set<I> reached;
	
	recursive_dfs_fun(grafo, nodo_partenza, reached, visita_rec);
	
	return visita_rec;
}

template<typename I> requires std::integral<I>
void recursive_dfs_fun(const undirected_graph<I>& grafo, const I& u, std::set<I>& reached, undirected_graph<I>& visita) {
    reached.insert(u);
    
    for (const I& vicino : grafo.neighbors(u)) {
        if (!reached.contains(vicino)) {
            visita.add_edge(u, vicino);
            recursive_dfs_fun(grafo, vicino, reached, visita);
        }
    }
}


template<typename T>
std::map<T, T> dijkstra(const undirected_graph<T>& grafo, const T sorgente) {
	std::vector<T> lista_nodi = grafo.all_nodes();
	size_t n_nodi = lista_nodi.size();
	std::map<T,T> mappa_predecessori;
	
	// Uso set distanze di pair ordinati per distanza crescente
	std::set<std::pair<int,T>> set_distanze;
	std::map<T, int> mappa_distanze;
	
	for (const auto& nodo : lista_nodi) {
		std::pair<int, T> distanza;
		if (nodo == sorgente) {
			distanza = {0, nodo};
			mappa_distanze[nodo] = 0;
		}
		else {
			// Usiamo n_nodi + 1 come "infinito", dato che un cammino con archi pesati a 1 può essere lungo al massimo n_nodi - 1
			distanza = {static_cast<int>(n_nodi + 1), nodo};
			mappa_distanze[nodo] = n_nodi + 1;
		}
		set_distanze.insert(distanza);
		mappa_predecessori.insert({nodo, nodo});
	}
	
	while (!set_distanze.empty()) {
		std::pair<int, T> coppia = *set_distanze.begin();
		auto u = coppia.second;
		set_distanze.erase(set_distanze.begin());
		
		std::set<T> la = grafo.neighbors(u); 
		for (const auto& vicino : la) {
			if (mappa_distanze[vicino] > (mappa_distanze[u] + 1)) {
				int distanza_old = mappa_distanze[vicino];
				int distanza_new = mappa_distanze[u] + 1;
				
				mappa_distanze[vicino] = distanza_new;
				mappa_predecessori[vicino] = u;
				
				set_distanze.erase({distanza_old, vicino});
				std::pair<int, T> coppia_dist = {distanza_new, vicino};
				set_distanze.insert(coppia_dist);
			}
		}
	}
	
	std::cout << "Stampo le distanze tra il nodo sorgente e tutti gli altri nodi del grafo: \n";
	for (const auto& [nodo, valore] : mappa_distanze) {
		std::cout << "Il nodo " << nodo << " è a distanza " << valore << " dal nodo sorgente " << sorgente << "\n";
	}
	std::cout << "\n\n";
	
	return mappa_predecessori;
}


int main(){
	//provo con il grafo di prova dato a Esercitazione
	undirected_graph<int> G;
	
	G.add_node(1);
    G.add_node(2);
    G.add_node(3);
    G.add_node(4);
    G.add_node(5);
    G.add_node(6);
    G.add_node(7);
    G.add_node(8);
    G.add_node(9);
    
    G.add_edge(1, 2);
    G.add_edge(1, 3);
    G.add_edge(1, 4);
    G.add_edge(1, 6);
    G.add_edge(2, 5);
    G.add_edge(2, 7);
    G.add_edge(3, 6);
    G.add_edge(4, 6);
    G.add_edge(4, 7);
    G.add_edge(5, 7);
    G.add_edge(6, 7);
    G.add_edge(6, 8);
    G.add_edge(7, 9);
    G.add_edge(8, 9);
	
	std::cout << "\n**--**--**--**--**--**--**--**--**--**--**--**\n";
	std::cout << "\nStampo il grafo originale: \n";
	G.print();
	std::cout << "\n**--**--**--**--**--**--**--**--**--**--**--**\n";
	std::cout << "\n\n";
	
	/* Effettua una visita in profondita' di G, restituendo il risultato in dfsG */
	lifo<int> s;
	undirected_graph<int> dfsG = graph_visit(G, 1, s);
	std::cout << "Stampo il grafo di visita con dfsG: \n";
	dfsG.print();
	std::cout << "\n\n";
	
	/* Effettua una visita in ampiezza di G, restituendo il risultato in bfsG */
	fifo<int> q;
	undirected_graph<int> bfsG = graph_visit(G, 1, q);
	std::cout << "Stampo il grafo di visita con bfsG: \n";
	bfsG.print();
	std::cout << "\n\n";
	
	/* Effettua una visita in profondita di G, restituendo il risultato in recursive dfsG */
	undirected_graph<int> rec_dfsG = recursive_dfs(G, 1);
	std::cout << "Stampo il grafo di visita con recusive dfsG: \n";
	rec_dfsG.print();
	std::cout << "\n\n";
	
	/* Utilizzo il metodo Dijkstra per deterninare le distanze tra i nodi e la mappa predecessori */
	int sorgente = 1;
	std::map<int, int> predecessori = dijkstra(G, sorgente);
	std::cout << "Stampo la mappa dei predecessori del nodo sorgente " << sorgente << " utilizzando il metodo Dijkstra (Nodo -> Il suo predecessore ottimale) \n";
    for (const auto& [nodo, pred] : predecessori) {
        if (nodo == sorgente) {
            std::cout << nodo << " -> [SORGENTE]\n";
        } else {
            std::cout << nodo << " -> " << pred << "\n";
        }
    }
    std::cout << "\n\n";
	return 0;
}
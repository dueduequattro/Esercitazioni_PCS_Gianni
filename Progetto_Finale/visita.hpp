#pragma once
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



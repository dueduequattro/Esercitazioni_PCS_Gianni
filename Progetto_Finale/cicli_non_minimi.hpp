#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "visita.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"


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
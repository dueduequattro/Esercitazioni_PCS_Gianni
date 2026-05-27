#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <concepts>
#include <utility>
#include "undirected_graph.hpp"

template <typename I> requires std::integral<I>
struct dijkstra_result {
    std::map<I, int> dist;
    std::map<I, std::optional<I>> pred;
};

template<typename I> requires std::integral<I>
dijkstra_result<I> dijkstra(const undirected_graph<I>& graph, const I& source) {
    
    dijkstra_result<I> result; 
    
    std::vector<I> nodes = graph.all_nodes();
    size_t n_nodes = nodes.size();
    
    // Set che funge da coda con priorità ordinata per distanza crescente
    std::set<std::pair<int, I>> distance_set;
    
    for (const auto& node : nodes) {
        if (node == source) {
            result.dist[node] = 0;
            distance_set.insert({0, node});
        }
        else {
			// Usiamo n_nodes + 1 come "infinito", dato che un cammino con archi pesati a 1 può essere lungo al massimo n_nodes - 1
            result.dist[node] = static_cast<int>(n_nodes + 1);
            distance_set.insert({static_cast<int>(n_nodes + 1), node});
        }
        result.pred[node] = std::nullopt;
    }
    
    while (!distance_set.empty()) {
        
        std::pair<int, I> nearest_pair = *distance_set.begin();
        auto u = nearest_pair.second;
        distance_set.erase(distance_set.begin());
                
		auto opt_neighbors = graph.neighbors(u);
        
		if (opt_neighbors.has_value()) {
			for (const I& neighbor : opt_neighbors.value()) {
				// La distanza associata ad ogni arco è 1
				int dist_through_u = result.dist[u] + 1; 
				
				if (result.dist[neighbor] > dist_through_u) {
					int old_dist = result.dist[neighbor];
					
					result.dist[neighbor] = dist_through_u;
					result.pred[neighbor] = u;
					
					distance_set.erase({old_dist, neighbor});
					distance_set.insert({dist_through_u, neighbor});
				}
			}
		}
	}
    
    return result;
}
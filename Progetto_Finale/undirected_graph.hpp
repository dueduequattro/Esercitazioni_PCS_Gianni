#pragma once
#include <iostream>
#include <map>
#include <set>
#include <concepts>
//includo optional per poter gestire l'errore in edge_number
#include <optional>
#include <vector>
#include <algorithm> // Per std::find
#include <iterator>  // Per std::distance

#include "undirected_edge.hpp"

template<typename I> requires std::integral<I>
class undirected_graph {
    std::map<I, std::set<I>> adj_list;
    
    //creo il vettore di archi per numerarli. Lo uso nei metodi all_edges, edge_number e edge_at
    std::vector<undirected_edge<I>> edges_vector;

public:
    undirected_graph() = default;
    
    void add_node(I node) {
	    if(adj_list.contains(node)){
		    std::cout << "Errore: il nodo "<< node << " era gia' presente nel grafo.\n";
	    } else{
        	adj_list[node]; 
        }
    }

    void add_edge(const undirected_edge<I>& edge) {
	    I f = edge.from();
		I t = edge.to();
		
	    if(!adj_list.contains(f)){
		    add_node(f);
	    }
	    if(!adj_list.contains(t)){
		    add_node(t);
	    }
		
		if(adj_list[f].contains(t)){
			std::cout << "Errore: l'arco (" << f << ", " << t << ") era gia' presente nel grafo.\n";
		} else{
			//metodo insert implementato in std::set
			adj_list[f].insert(t);
			adj_list[t].insert(f);
			//con il metodo push_back aggiungo l'arco edge al vettore
			edges_vector.push_back(edge);
			std::sort(edges_vector.begin(), edges_vector.end());
		}
    }
    
    void remove_edge(const undirected_edge<I>& edge) {
	    I f = edge.from();
		I t = edge.to();
		
	    if(!adj_list.contains(f) || !adj_list.contains(t) || !adj_list[f].contains(t)){
		    std::cout << "Errore: l'arco (" << f << ", " << t << ") non esiste nel grafo.\n";
	    } else {
		    //metodo erase implementato in std::set
			adj_list[f].erase(t);
			adj_list[t].erase(f);
			
			//rimuovo dal vettore l'arco (find qunado non trova restituisce l'ultimo indice)
			auto it = std::find(edges_vector.begin(), edges_vector.end(), edge);
        	if (it != edges_vector.end()) {
            	edges_vector.erase(it);
            	std::sort(edges_vector.begin(), edges_vector.end());
        	}
		}
	}

    void add_edge(I start, I end) {
        undirected_edge<I> new_edge(start, end);
        add_edge(new_edge);
    }
    
    std::set<I> neighbors(I node) const {
	    if(adj_list.contains(node)){
		    //uso at e non adj_list[node] poiche' voglio evitare la creazione di un nodo (in realta' ho l'if fuori che controlla ma è più corretto cosi')
	    	return adj_list.at(node);
	    } else {
		    std::cout << "Errore: il nodo "<< node << " non e' presente nel grafo.\n";
		    //restituisco set vuoto
		    return {};
	    }
    }
    
    std::vector<I> all_nodes() const{
	    std::vector<I> nodes(adj_list.size());
	    int i = 0;
        for (const auto& [node, neighbors] : adj_list) {
            nodes[i] = node;
            i++;
        }
        
        return nodes;
    }
    
    std::vector<undirected_edge<I>> all_edges() const {
		return edges_vector; 
	}
	
	std::optional<size_t> edge_number(const undirected_edge<I>& edge_T) const {
		//metodo find di std che restituisce l'iteratore dell'elemento cercato (se trovato) altrimenti ritorna l'iteratore di fine
		auto it = std::find(edges_vector.begin(), edges_vector.end(), edge_T);
		if (it != edges_vector.end()) {
			//metodo distance restituisce la distanza tra l'inizio e it, dunque restituisce l'iteratore di it
			return std::distance(edges_vector.begin(), it);
		}
		return std::nullopt;
	}
	
	std::optional<undirected_edge<I>> edge_at(size_t index) const {
		if (index < edges_vector.size()) {
			return edges_vector[index];
		}
		return std::nullopt;
	}
    
    undirected_graph& operator=(const undirected_graph& other) {
        if (this != &other) {
            adj_list = other.adj_list;
            edges_vector = other.edges_vector;
        }
        return *this;
    }
    
    undirected_graph operator-(const undirected_graph& other) const {
	    undirected_graph differenza = *this;
	    for (const auto& edge : other.all_edges()) {
            differenza.remove_edge(edge);
        }
        return differenza;
    }
    
    

    // Stampa
    void print() const {
        for (const auto& [node, neighbors] : adj_list) {
            std::cout << "Nodo [" << node << "] è collegato a: ";
            
            if (neighbors.empty()) {
                std::cout << "(nessuno - nodo isolato)";
            } else {
                for (I neighbor : neighbors) {
                    std::cout << neighbor << " ";
                }
            }
            std::cout << "\n";
        }
    }
};
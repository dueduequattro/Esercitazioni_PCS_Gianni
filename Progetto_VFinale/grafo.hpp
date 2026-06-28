#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <concepts>
#include <algorithm>
#include <set>
#include <optional>
#include <iterator> 
#include <list>


template<typename I> requires std::integral<I>
class undirected_edge {
    I start;
    I end;
    
public:
	//utilizzo delete poichè non voglio un costrutture di default. Devo garantire la struttura (s,e)
    undirected_edge() = delete;
    
    undirected_edge(I s, I e) : start(std::min(s,e)), end(std::max(s,e)) {}
    
    I from() const { return start; }
    I to() const { return end; }
    
    bool operator<(const undirected_edge& other) const {
        if (start != other.start) {
            return start < other.start;
        }
        return end < other.end;
    }
    
    bool operator==(const undirected_edge& other) const {
        return (start == other.start && end == other.end);
    }    
};


template<typename I> requires std::integral<I>
std::ostream& operator<<(std::ostream& os, const undirected_edge<I>& edge) {
    os << "(" << edge.from() << "," << edge.to() << ")";
    return os;
}

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
			
			// lower_bound trova il punto esatto in cui inserire per mantenere il vettore ordinato
			auto it = std::lower_bound(edges_vector.begin(), edges_vector.end(), edge);
			edges_vector.insert(it, edge);		
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
			
			// sfruttiamo il fatto che il vettore è già ordinato per fare una ricerca binaria
			auto it = std::lower_bound(edges_vector.begin(), edges_vector.end(), edge);    
			
			// lower_bound restituisce il primo elemento maggiore o uguale, devo controllare che sia effettivamente uguale
			if (it != edges_vector.end() && *it == edge) {
            	edges_vector.erase(it);
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
		// ricerca binaria, sfrutto il fatto che il vettore è ordinato
		auto it = std::lower_bound(edges_vector.begin(), edges_vector.end(), edge_T);

		// lower_bound restituisce il primo elemento maggiore o uguale, devo controllare che sia effettivamente uguale		
		if (it != edges_vector.end() && *it == edge_T) {
			// metodo distance restituisce la distanza tra l'inizio e it, dunque restituisce l'iteratore di it
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
};



// Contenitori Fifo e Lifo e graph_visit


template<typename T>
class fifo {
    std::list<T> queue;
public:
	fifo() = default;
	
	void put(const T& element){
		queue.push_back(element);
	}
	
	std::optional<T> get(){
		if(queue.empty()){
			return std::nullopt;
		} else {
			T x = queue.front();
			queue.pop_front();
			return x;
		}
	}
	
	bool empty() const {
		return queue.empty();
	}
};

template<typename T>
class lifo {
    std::list<T> stack;
public:
	lifo() = default;
	
	void put(const T& element){
		stack.push_front(element);
	}
	
	std::optional<T> get(){
		if(stack.empty()){
			return std::nullopt;
		} else {
			T x = stack.front();
			stack.pop_front();
			return x;
		}
	}
	
	bool empty() const {
		return stack.empty();
	}
};

template<typename I> requires std::integral<I>
undirected_graph<I> graph_visit (const undirected_graph<I>& grafo, const I& nodo_partenza, auto& contenitore){
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


// BFS

template <typename I> requires std::integral<I>
struct bfs_result {
    std::vector<int> dist;
    std::vector<std::optional<I>> pred;
};

template<typename I> requires std::integral<I>
bfs_result<I> bfs_cammino_minimo(const undirected_graph<I>& graph, const I& source, const I& target, const I max_node_id) {
    
    bfs_result<I> result; 
   
    const int infinito = static_cast<int>(max_node_id + 2);
    
    result.dist.assign(max_node_id + 1, infinito);
    result.pred.assign(max_node_id + 1, std::nullopt);
    
    fifo<I> coda;
    
    result.dist[source] = 0;
    coda.put(source);
    
    while (!coda.empty()) {
        auto u_opt = coda.get();
        if (u_opt == std::nullopt) break;
        
        I u = *u_opt;
        
        // Se raggiungiamo il nodo finale ci fermiamo
        if (u == target) {
            break;
        }
        
        std::set<I> neighbors = graph.neighbors(u);
        
		for (const I& neighbor : neighbors) {
            // Se la distanza è infinito, il nodo non è ancora stato visitato
            if (result.dist[neighbor] == infinito) {
                result.dist[neighbor] = result.dist[u] + 1;
                result.pred[neighbor] = u;
                coda.put(neighbor);
            }
        }
    }
    
    return result;
}

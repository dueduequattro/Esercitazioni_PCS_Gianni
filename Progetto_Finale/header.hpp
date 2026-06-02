#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <eigen3/Eigen/Dense>
#include <concepts>
#include <algorithm>
#include <set>
#include <optional>
#include <vector>
#include <iterator> 
#include <list>
#include <utility>
#include <cmath>



// Lettura File


struct valor_input {
    double peso;
    int nodo1;
    int nodo2;
};


struct RisultatoLettura {
    std::map<std::string, valor_input> circuito;
    int resistori;
    bool controllo;
};


RisultatoLettura lettura_file(const int argc, const char *argv[]){
	RisultatoLettura res; //creo mappa per salvare gli elementi del circuito (l'ipotesi di assenza di elementi in parallelo mi permette di usare la stringa R# o V# come chiave)
	res.resistori = 0;
	res.controllo = true;
	  
	if (argc!=2){ //come visto nell'Esercitazione 1 devo ottenere in input una sola stringa unica contente il nome del file e questo si verifica solo se argc=2.
		std::cout << "Errore, inserire il nome di un file.\n";
		res.controllo = false;
		return res;
		}
	
	std::string filename;
	filename = argv[1];
	std::ifstream ifs(filename);
	
	//gestione errore lettura file
	if (!ifs.is_open()) {
		std::cout << "Errore: Impossibile aprire il file '" << filename << "'.\n";
		std::cout << "Verifica che il nome sia corretto e che il file sia nella cartella del progetto.\n";
		res.controllo = false;
	return res;
	}
	
	// Lo togliamo?
	std::cout << "File caricato correttamente.\n\n";
	
	std::string key;
	valor_input v;
	std::string linea;
	
	while (std::getline(ifs, linea)) {
		
		// Senza queste due linee alla riga 74 viene stampata la stringa, poi linea che finisce con \r, quindi lo stream torna a capo e stampa
		// il carattere ' sovrascrivendo la lettera A.
		if (!linea.empty() && linea.back() == '\r') {
			linea.pop_back();
		}
		
		/* salta righe vuote o con solo spazi, tab o a capo (std::string::npos è una costante speciale di valore -1 che i metodi di std::string restituiscono quando non trovano quello che cercano
		find_dirst_not_of mi restituisce l'indice del primo carattere che non è uno di quelli elencati, se non trova nulla restituisce std::string::npos)*/
		if (linea.empty() || linea.find_first_not_of(" \t\r\n") == std::string::npos) continue;
		
		//std::istringstream è uno stream di input che legge da una stringa (quella passata tra parentesi) invece che da un file o dalla console.
		std::istringstream iss(linea);
		
		if (!(iss >> key >> v.peso >> v.nodo1 >> v.nodo2)) {
			// la riga non è vuota ma il formato è sbagliato
			std::cout << "Attenzione: riga malformata ignorata: '" << linea << "'\n";
			continue;
		}
		
		if (key[0] != 'R' && key[0] != 'V') {
			// accetto solo componenti che iniziano per 'R' o 'V'
			std::cout << "Attenzione: componente sconosciuto '" << key << "' ignorato nella riga: '" << linea << "'\n";
			continue;
		}
		
		res.circuito[key] = {v.peso, v.nodo1, v.nodo2}; //linea corretta
		if (key[0] == 'R') res.resistori++;
	}
	
	return res;
};



// Strutture dati: arco e grafo


template<typename I> requires std::integral<I>
class undirected_edge {
    I start;
    I end;
    
public:
	//utilizzo delete poichè non voglio un costrutture di defalut. Devo garantire la struttura (s,e)
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



// Algoritmo di Dijkstra


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
    
	// Usiamo n_nodes + 1 come "infinito", dato che un cammino con archi pesati a 1 può essere lungo al massimo n_nodes - 1
	const int infinito = static_cast<int>(n_nodes + 1);
	
    // Set che funge da coda con priorità ordinata per distanza crescente
    std::set<std::pair<int, I>> distance_set;
    
    for (const auto& node : nodes) {
        if (node == source) {
            result.dist[node] = 0;
            distance_set.insert({0, node});
        }
        else {
            result.dist[node] = infinito;
            distance_set.insert({infinito, node});
        }
        result.pred[node] = std::nullopt;
    }
    
    while (!distance_set.empty()) {
        
        std::pair<int, I> nearest_pair = *distance_set.begin();
        auto u = nearest_pair.second;
        distance_set.erase(distance_set.begin());
                
		// Se la distanza minima trovata è infinito, fermati
        if (nearest_pair.first >= infinito) {
            break;
        }        
		
		std::set<I> neighbors = graph.neighbors(u);
		for (const I& neighbor : neighbors) {
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
    
    return result;
}



// Algoritmo di De Pina


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
		
		// Per trovare il ciclo minimo ad ogni step non abbiamo calcolato il vettore C_mu, ma abbiamo semplicemente preso il cammino di lunghezza minore.
		// Questo porta allo stesso risultato, gestendo differentemente i casi in cui parto con l'esplorazione da un nodo che non fa parte di alcun ciclo.
		// Nel formalismo matematico, algebra modulo 2 permette di cancellare gli archi che percorro un numero pari di volte, ovvero riesco a cancellare
		// gli archi che non fanno parte del ciclo. Se applicassi l'algoritmo ad un grafo "a lecca lecca", con un nodo u collegato ad un triangolo, il vettore
		// C_mu che ottengo partendo da ciascun nodo è uguale. In questa implementazione, invece, il cammino dal nodo u- a u+ contiene il doppio passaggio
		// per l'arco fuori dal ciclo. In questo caso la lunghezza del cammino trovato partendo da u è 5, mentre se parto da un nodo del ciclo ottengo lunghezza 3:
		// l'algoritmo sceglie correttamente il ciclo. Il nostro criterio, quindi, riesce comunque a discriminare il caso patologico, evitando di costruire vettori
		// ausiliari e risparmiando memoria.
		
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



// Funzione per calcolare matrici e vettori del sistema


struct dati_sistema {
	Eigen::MatrixXd B;
	Eigen::MatrixXd R;
	Eigen::VectorXd v;
};


template<typename I> requires std::integral<I>
dati_sistema calcola_sistema(const std::map<std::string, valor_input>& circuito,	
	const std::vector<std::vector<I>>& maglie, int num_resistori, int num_maglie) {
	
	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_resistori, num_maglie);
	Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistori, num_resistori);
	Eigen::VectorXd v = Eigen::VectorXd::Zero(num_maglie); 
	
	// Calcolo tutti gli archi delle maglie per non doverle ricalcolare ad ogni iterazione
    std::vector<std::set<std::pair<I, I>>> archi_maglie(num_maglie);
    for (int j = 0; j < num_maglie; j++) {
        for (size_t k = 0; k + 1 < maglie[j].size(); k++) {
            archi_maglie[j].insert({maglie[j][k], maglie[j][k+1]});
        }
    }
	
	int i_res = 0; // indice resistore (riga)
	
	for (const auto& [key, valori] : circuito) {
        I n1 = valori.nodo1;
        I n2 = valori.nodo2;
		
		if (key[0] == 'R') {
            // Aggiorno la diagonale di R 
            R(i_res, i_res) = valori.peso;
			
			// Il verso di percorrenza dell’arco è sempre dal nodo di indice minore a quello di indice maggiore
			I r_start = std::min(n1, n2);
			I r_end = std::max(n1, n2);
			
			for (int j = 0; j < num_maglie; j++) { // j indice maglia (colonna)
				
				// Verso concorde al grafo
                if (archi_maglie[j].contains({r_start, r_end})) {
                    B(i_res, j) = 1; 
                }
				
				// Verso discorde al grafo
                else if (archi_maglie[j].contains({r_end, r_start})) {
                    B(i_res, j) = -1;
                }
            }
			
            i_res++;
		}	
		
		else if (key[0] == 'V') {
			
			for (int j = 0; j < num_maglie; j++) {
				
				// Da - a +
                if (archi_maglie[j].contains({n2, n1})) { 
                    v(j) += valori.peso;
                }
                
				// Da + a -
				else if (archi_maglie[j].contains({n1, n2})) { 
                    v(j) -= valori.peso;
                }
            }
			
		}
	}
	
	dati_sistema risultato;
	risultato.B = B;
	risultato.R = R;
	risultato.v = v;
	
	return risultato;
}



// Gradiente coniugato


struct risultato_gc {
	Eigen::VectorXd sol; 
    unsigned int it;     
    double res_rel;         
    bool conv;
};

risultato_gc gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& x,
const unsigned int it_max = 1000, const double res_tol = 1.0e-13) {
		
	// Controllo che le dimensioni combacino ma non se la matrice A 
	// è simmetrica definita positiva, troppo costoso
	
	// A è quadrata? A, b, x hanno dimensioni concordi?
	if (A.rows() != A.cols() || A.rows() != b.size() || x.size() != b.size()) {
		std::cerr << "Errore: dimensione dati incompatibile \n";
		return {x, 0, 0.0, false};
	}
		
	risultato_gc result;
  
	Eigen::VectorXd res = b - A * x;
	Eigen::VectorXd p = res;
	double res_norm_0 = res.norm();
	
	// Se x è già soluzione esci
	if (res_norm_0 == 0.0) {
		return {x,  0, 0.0, true};
	}
	
	unsigned int it = 0;

	while (it < it_max && res.norm() > res_tol * res_norm_0) {
		
		Eigen::VectorXd Ap = A * p;
		auto den = p.dot(Ap);
		
		if (den == 0.0) {
		    break;
		}
		
		const double alpha_k = p.dot(res) / den;		
		x = x + alpha_k * p;
		
		res = res - alpha_k * Ap;
		const double beta_k = (res.dot(Ap))/den;
		p = res - beta_k * p;
		
		it++;
		
	}
	
	result.sol = x;
	result.it = it;
	result.res_rel = res.norm() / res_norm_0;
	result.conv = (res.norm() <= res_tol * res_norm_0);
	
	return result;
}

// Se non si specifica il vettore di partenza si parte dal vettore nullo
risultato_gc gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b,
const unsigned int it_max = 1000, const double res_tol = 1.0e-13) {
	
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(b.size());
	return gradiente_coniugato(A, b, x0, it_max, res_tol);

}

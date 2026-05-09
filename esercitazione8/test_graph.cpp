#include <iostream>
#include <vector>
#include <set>
#include <optional>

#include "undirected_edge.hpp"
#include "undirected_graph.hpp"

int main() {
    std::cout << "=== INIZIO TEST GRAFO NON ORIENTATO (Int) ===\n\n";

    undirected_graph<int> grafo;
    
    //1. Test Inserimento Nodi e Archi

    std::cout << "\n--- Test Inserimento Nodi e Archi ---\n";
    std::cout << "Inserisco i nodi 1,2,3,4.\n\n";
    grafo.add_node(1);
    grafo.add_node(2);
    grafo.add_node(3);
    grafo.add_node(4);
    
    std::cout << "Provo a reinserire il nodo 2 (dovrei ottenere errore poiche' gia' presente).\n";
    grafo.add_node(2);

    std::cout <<"\n"<< "Inserisco gli archi (1,2), (2,3), (3,4), (4,1) con il metodo .add_edge()\n";
    grafo.add_edge(1, 2);
    grafo.add_edge(2, 3);
    grafo.add_edge(3, 4);
    grafo.add_edge(4, 1);
    
    std::cout << "Inserisco l'arco (1,3) passando direttamente una classe undirected_edge.\n";
    undirected_edge<int> arco_diagonale(1, 3);
    grafo.add_edge(arco_diagonale);

    std::cout << "Provo a inserire l'arco (2,1) (dovrei ottenere un errore poiche' (2,1) = (1,2) gia' presente nel grafo).\n";
    grafo.add_edge(2, 1);

    std::cout << "\nStato del grafo dopo gli inserimenti:\n";
    grafo.print();

    // 2. Test esplorazione del grafo
    std::cout << "\n\n--- Test esplorazione Nodi e Archi ---\n";
    
    std::vector<int> nodi = grafo.all_nodes();
    std::cout << "Stampo tutti i nodi del grafo usando il metodo .all_nodes(): ";
    for (int n : nodi) std::cout << n << " ";
    std::cout << "\n";

    std::vector<undirected_edge<int>> archi = grafo.all_edges();
    std::cout << "Stampo tutti gli archi del grafo usando il metodo .all_edges() e l'operatore << introdotto in undirected_edge: ";
    for (const auto& a : archi) std::cout << a << " ";
    std::cout << "\n";

    // 3. Test vicinato
    std::cout << "\n\n--- Test Neighbours ---\n";
    int nodo_test = 1;
    std::set<int> vicini_di_1 = grafo.neighbors(nodo_test);
    std::cout << "Stampo tutti i vicini del nodo " << nodo_test << " con il metodo .neighbors(): ";
    for (int v : vicini_di_1) std::cout << v << " ";
    std::cout << "\n";

    // 4. Test Metodi Indice Archi
    std::cout << "\n\n--- Test Ricerca Archi (edge_number e edge_at) ---\n";
    undirected_edge<int> arco_da_cercare(3, 4);
    std::optional<size_t> indice = grafo.edge_number(arco_da_cercare);
    
    if (indice.has_value()) {
        std::cout << "Cerco l'indice dell'arco (3,4) con il metodo .edge_number() "<<"\n";
        std::cout << "L'arco " << arco_da_cercare << " si trova all'indice: " << indice.value() << "\n";
        
        // MODIFICA QUI: Aggiunto .value() alla fine di edge_at per estrarre l'arco dall'optional
        std::cout << "Verifica la correttezza di tale indice con il metodo .edge_at(" << indice.value() << "): " << grafo.edge_at(indice.value()).value() << "\n";
    } else {
        std::cout << "Arco " << arco_da_cercare << " non trovato.\n";
    }

    // 5. Test Rimozione Archi
    std::cout << "\n\n--- Test Rimozione Archi ---\n";
    std::cout << "Rimuovo l'arco (1,3) con il metodo remove_edge() "<<"\n";
    grafo.remove_edge(arco_diagonale);
    std::cout << "Grafo dopo aver rimosso l'arco " << arco_diagonale << ":\n";
    grafo.print();

    // 6. Test Operatore Sottrazione
    std::cout << "\n\n--- Test Sottrazione tra Grafi (operator-) ---\n";
    std::cout << "Rimuovo dal grafo precedente il grafo formato dai nodi 1,2,3,4 e archi (1,2), (3,4) "<<"\n"<<"\n";
    undirected_graph<int> grafo_da_sottrarre;
    grafo_da_sottrarre.add_edge(1, 2);
    grafo_da_sottrarre.add_edge(3, 4);

    std::cout << "Grafo da sottrarre:\n";
    grafo_da_sottrarre.print();

    undirected_graph<int> grafo_risultato = grafo - grafo_da_sottrarre;
    
    std::cout << "\nRisultato della sottrazione:\n";
    grafo_risultato.print();

    std::cout << "\n=== FINE TEST ===\n";
    return 0;
}
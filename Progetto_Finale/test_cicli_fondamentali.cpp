#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "undirected_graph.hpp"
#include "fifo_and_lifo.hpp"
#include "visita.hpp"
#include "depina.hpp"
#include "cicli_non_minimi.hpp"

int main() {
    // 1. Creazione di una Griglia Piana 2x2 (9 nodi, 12 archi)
    // Nodi disposti come:
    // 1 -- 2 -- 3
    // |    |    |
    // 4 -- 5 -- 6
    // |    |    |
    // 7 -- 8 -- 9
    undirected_graph<int> griglia;
    
    // Archi Orizzontali
    griglia.add_edge(1, 2); griglia.add_edge(2, 3);
    griglia.add_edge(4, 5); griglia.add_edge(5, 6);
    griglia.add_edge(7, 8); griglia.add_edge(8, 9);
    
    // Archi Verticali
    griglia.add_edge(1, 4); griglia.add_edge(2, 5); griglia.add_edge(3, 6);
    griglia.add_edge(4, 7); griglia.add_edge(5, 8); griglia.add_edge(6, 9);

    std::cout << "=== VERTICI E VICINI DEL GRAFO GRIGLIA ===\n";
    griglia.print();

    // 2. Estrazione di Albero e Coalbero usando graph_visit e lifo
    lifo<int> contenitore_lifo;
    std::cout << "\n=== ESTRAZIONE ALBERO TRAMITE GRAPH_VISIT E LIFO ===\n";
    
    // Genera l'albero di copertura DFS partendo dal nodo 1
    undirected_graph<int> albero = graph_visit(griglia, 1, contenitore_lifo);
    
    // Calcola il coalbero sottraendo l'albero al grafo originario
    undirected_graph<int> coalbero = griglia - albero;

    std::cout << "Numero totale di archi in G: " << griglia.all_edges().size() << "\n";
    std::cout << "Numero di archi nell'albero (N-1): " << albero.all_edges().size() << "\n";
    std::cout << "Numero di archi nel Coalbero (k): " << coalbero.all_edges().size() << "\n";

    // 3. Esecuzione della ricerca dei cicli fondamentali su base DFS
    std::cout << "\n=== ESECUZIONE RICERCA CICLI FONDAMENTALI (DFS) ===\n";
    std::vector<std::vector<int>> cicli_dfs = cicli_fondamentali_dfs(albero, coalbero);

    for (size_t i = 0; i < cicli_dfs.size(); ++i) {
        std::cout << "Ciclo fondamentale DFS " << i + 1 << " (sequenza nodi): ";
        for (size_t j = 0; j < cicli_dfs[i].size(); ++j) {
            std::cout << cicli_dfs[i][j] << (j == cicli_dfs[i].size() - 1 ? "" : " -> ");
        }
        std::cout << "\n";
    }

    // 4. Esecuzione dell'algoritmo di De Pina
    std::cout << "\n=== ESECUZIONE ALGORITMO DE PINA (CICLI MINIMI) ===\n";
    std::vector<std::vector<int>> base_cicli_minimi = cicli_minimi(griglia, coalbero);

    for (size_t i = 0; i < base_cicli_minimi.size(); ++i) {
        std::cout << "Ciclo minimo De Pina " << i + 1 << " (sequenza nodi): ";
        for (size_t j = 0; j < base_cicli_minimi[i].size(); ++j) {
            std::cout << base_cicli_minimi[i][j] << (j == base_cicli_minimi[i].size() - 1 ? "" : " -> ");
        }
        std::cout << "\n";
    }

    return 0;
}
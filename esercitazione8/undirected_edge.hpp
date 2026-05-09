#pragma once
#include <iostream>
#include <concepts>
#include <algorithm>


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
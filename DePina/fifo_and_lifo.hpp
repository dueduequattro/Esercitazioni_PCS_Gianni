#pragma once
#include <list>
#include <optional>


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


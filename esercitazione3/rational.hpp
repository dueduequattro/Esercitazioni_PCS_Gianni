#pragma once
#include <iostream>
#include <concepts>
#include <numeric>

template<typename I> requires std::integral<I>
class rational {
    I numerator;
    I denominator;
    
public:
    rational() : numerator(0), denominator(1) {}
    
    rational(I num, I den) : numerator(num), denominator(den) {
        semplifica();
    }
    
    void semplifica(){
	    if (denominator == 0 && numerator > 0) {
            numerator = 1;
        } else if (denominator == 0 && numerator < 0){
	        numerator = -1;
        } else {
	        if (denominator < 0){
		        numerator= -numerator;
		        denominator = -denominator;
		        }
			I comune_divisore = std::gcd(numerator, denominator);
			numerator /= comune_divisore;
			denominator /= comune_divisore;
		}
    }
    
    I num() const { return numerator; }
    I den() const { return denominator; }
    
    rational& operator+=(const rational& other) {
        numerator = (numerator * other.denominator) + (other.numerator * denominator);
        denominator *= other.denominator;
        semplifica();
        return *this;
    }
    
    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret;
    }
    
    rational& operator-=(const rational& other) {
        numerator = (numerator * other.denominator) - (other.numerator * denominator);
        denominator *= other.denominator;
        semplifica();
        return *this;
    }
    
    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    rational& incr(const rational& other) {
        return *this += other;
    }
    
    rational add(const rational& other) const {
        return *this + other;
    }

    rational& operator*=(const rational& other) {
		numerator *= other.numerator;
		denominator *= other.denominator;
		semplifica();
		return *this;
	}

	rational operator*(const rational& other) const {
		rational ret = *this;
		ret *= other;
		return ret;
	}
    
    rational& operator/=(const rational& other) {
		numerator *= other.denominator;
		denominator *= other.numerator;
		semplifica();
		return *this;
	}

	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	}
};


template<typename T> requires std::integral<T>
std::ostream& operator<<(std::ostream& os, const rational<T>& v) {
    os << "(" << v.num() << "/" << v.den() << ")";
    return os;
}
#pragma once
#include <iostream>
#include <Eigen/Dense>

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
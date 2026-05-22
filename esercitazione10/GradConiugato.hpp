#pragma once
#include <iostream>
#include <eigen3/Eigen/Dense>
//Eigen::VectorXd definisce un vettore colonna di dimensione generica X e le cui entrate sono d = double
/*Il simbolo * implementa autonomamente il prodotto matrice - vettore ma non esegue il controllo sulle dimensioni compatibili
dei due fattori, dunque potrebbe generare errore*/

//utilizzo la struct per ritornare più valori contemporaneamente di tipo diverso
struct str_gradcgn_res {
	Eigen::VectorXd x;
	bool fine;
	double tol;
	int iter;
};


str_gradcgn_res gcd(const Eigen::VectorXd& x_0, const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const int k_max, const double tol){
	str_gradcgn_res risultato;
	risultato.iter = 0;
	
	if(x_0.size()!=b.size() || x_0.size()!=A.rows() || A.rows()!=A.cols()){
		std::cout<<"Errore, dimensioni dei dati in input incompatibili. \n";
	} else {
		//Help from Gemini per determinare un controllo sulla simmetria di A
		bool simmetrica = A.isApprox(A.transpose());
		if(!simmetrica){
			std::cout<<"ATTENZIONE, la matrice passata non è simmetrica! \n";
		}
		
		int n = x_0.size();
		int k = 0;
		
		Eigen::VectorXd r = b - A*x_0;
		Eigen::VectorXd p = r;
		Eigen::VectorXd x = x_0;
		//prealloco il vettore Ap dato che il prodotto matrice-vettore è O(n^2) quindi lo voglio fare una sola volta
		Eigen::VectorXd Ap(n);
		
		double alpha;
		double beta;
		
		while(r.norm()>tol && k<k_max){
			Ap = A * p;
			double den = p.dot(Ap);
			if (den!=0){
				alpha = (p.dot(r))/den;
				x = x + alpha*p;
				r = b - A*x;
				//sfrutto la simmetria di A per cui p*(Ar) = p'Ar = (p'A)r = (A'p)'r = (Ap)'r = Ap*r = r*Ap
				beta = (r.dot(Ap))/den;
				p=r-beta*p;
			} else{
				std::cout<<"Errore, divisione per 0 all'iterazione "<<k<<". \n";
				break;
			}
			k++;
		}
		
		risultato.x = x;
		risultato.iter = k;
		risultato.tol = r.norm();
		
		if (k == k_max && r.norm() > tol) {
			//ritorno false quando ho raggiunto il numero massimo di iterazioni ma non la tolleranza
			risultato.fine = false;
		} else {
			risultato.fine = true;
		}
	}
	return risultato;
}
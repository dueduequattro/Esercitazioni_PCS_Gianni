#include <iostream>
#include <eigen3/Eigen/Dense>
#include "GradConiugato.hpp" 

int main() {
    // ==== TEST 1 ====
    Eigen::MatrixXd A(3, 3);
    A << 4.0,  1.0,  0.0,
         1.0,  3.0, -1.0,
         0.0, -1.0,  2.0;

    Eigen::VectorXd x_esatta_1(3);
    x_esatta_1 << 1.0, 1.0, 1.0;
    Eigen::VectorXd b_1 = A * x_esatta_1;

    Eigen::VectorXd x_0_1 = Eigen::VectorXd::Zero(3);

    int k_max = 50;
    double tol = 1e-6;
    
    std::cout <<"****Test 1****\n\n";
    std::cout << "Matrice A:\n" << A << "\n\n";
    std::cout << "Termine noto b_1:\n" << b_1 << "\n\n";
    std::cout << "Soluzione attesa:\n" << x_esatta_1 << "\n\n";

    str_gradcgn_res risultato_1 = gcd(x_0_1, A, b_1, k_max, tol);

    std::cout << "\n=== RISULTATI del GradConiugato ===\n";
    std::cout << "Il metodo si e' interrotto per: ";
    if (risultato_1.fine) {
        std::cout << "tolleranza raggiunta\n";
    } else {
        std::cout << "massimo numero di iterazioni raggiunto.\n";
    }
    std::cout << "Iterazioni impiegate: " << risultato_1.iter << "\n";
    std::cout << "Residuo finale: " << risultato_1.tol << "\n";
    std::cout << "Soluzione calcolata x:\n" << risultato_1.x << "\n";
    
    std::cout << "\n\n\n\n---------------------------------------------------\n\n";


    // ==== TEST 2: Mancata convergenza (k_max raggiunto) ====
    // Creo una matrice mal condizionata
    int n_B = 15;
    Eigen::MatrixXd B(n_B, n_B);
    for (int i = 0; i < n_B; ++i) {
        for (int j = 0; j < n_B; ++j) {
            B(i, j) = 1.0 / (i + j + 1.0); 
        }
    }
         
    Eigen::VectorXd x_esatta_2 = Eigen::VectorXd::Ones(n_B);
    Eigen::VectorXd b_2 = B * x_esatta_2;
    Eigen::VectorXd x_0_2 = Eigen::VectorXd::Zero(n_B);
    
    int k_max_2 = 3;

    std::cout <<"****Test 2****\n\n";
    std::cout << "Matrice B (Hilbert dimensione "<< n_B <<"):\n" << B << "\n\n";
    std::cout << "Termine noto b_2:\n" << b_2 << "\n\n";
    std::cout << "Soluzione attesa:\n" << x_esatta_2 << "\n\n";

    str_gradcgn_res risultato_2 = gcd(x_0_2, B, b_2, k_max_2, tol);

    std::cout << "\n=== RISULTATI del GradConiugato ===\n";
    std::cout << "Il metodo si e' interrotto per: ";
    if (risultato_2.fine) {
        std::cout << "tolleranza raggiunta\n";
    } else {
        std::cout << "massimo numero di iterazioni raggiunto.\n";
    }
    std::cout << "Iterazioni impiegate: " << risultato_2.iter << "\n";
    std::cout << "Residuo finale: " << risultato_2.tol << "\n";
    std::cout << "Soluzione calcolata x:\n" << risultato_2.x << "\n";

    std::cout << "\n\n\n\n---------------------------------------------------\n\n";


    // ==== TEST 3: Dimensioni errate ====
    // Creo un vettore termine noto di dimensione 4 invece di 3
    Eigen::MatrixXd C(3, 3);
    C << 4.0,  1.0,  0.0,
         1.0,  3.0, -1.0,
         0.0, -1.0,  2.0;

    Eigen::VectorXd b_3(4); 
    b_3 << 1.0, 2.0, 3.0, 4.0;
    
    Eigen::VectorXd x_0_3 = Eigen::VectorXd::Zero(3);

    std::cout <<"****Test 3****\n\n";
    std::cout << "Matrice C (3x3):\n" << C << "\n\n";
    std::cout << "Termine noto b_3 (dimensione 4):\n" << b_3 << "\n\n";

    str_gradcgn_res risultato_3 = gcd(x_0_3, C, b_3, k_max, tol);
    
    std::cout << "\n\n\n\n---------------------------------------------------\n\n";
    
    // ==== TEST 4: Matrice non simmetrica ====
    Eigen::MatrixXd D(3, 3);
    D << 4.0,  2.0,  0.0,
         1.0,  3.0, -1.0,
         0.0, -1.0,  2.0;

    Eigen::VectorXd x_esatta_4(3);
    x_esatta_4 << 1.0, 1.0, 1.0;
    Eigen::VectorXd b_4 = D * x_esatta_4;

    Eigen::VectorXd x_0_4 = Eigen::VectorXd::Zero(3);

    std::cout <<"****Test 4****\n\n";
    std::cout << "Matrice D:\n" << D << "\n\n";
    std::cout << "Termine noto b_4:\n" << b_4 << "\n\n";
    std::cout << "Soluzione attesa:\n" << x_esatta_4 << "\n\n";

    str_gradcgn_res risultato_4 = gcd(x_0_4, D, b_4, k_max, tol);

    std::cout << "\n=== RISULTATI del GradConiugato ===\n";
    std::cout << "Il metodo si e' interrotto per: ";
    if (risultato_4.fine) {
        std::cout << "tolleranza raggiunta\n";
    } else {
        std::cout << "massimo numero di iterazioni raggiunto.\n";
    }
    std::cout << "Iterazioni impiegate: " << risultato_4.iter << "\n";
    std::cout << "Residuo finale: " << risultato_4.tol << "\n";
    std::cout << "Soluzione calcolata x:\n" << risultato_4.x << "\n";


    return 0;
}
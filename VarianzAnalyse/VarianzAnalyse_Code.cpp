#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int c = 5;
int n = 16;

//log-Werte der 16 Scheiben, allerdings absteigend geordnet, beginnend bei 15 
/*std::vector<std::vector<double>> M = {
    { 0.60,  0.10,  0.69,  0.17,  0.45,  0.27,  1.74, -0.10, 2.02,  1.25,  1.37, -0.06,  5.03,  0.34,  5.16, -0.03 },
    { 0.92,  0.08,  0.44, -0.00,  0.60,  0.43,  1.67, -0.09, 1.93,  1.62,  1.28, -0.11,  4.90,  0.27,  4.77, -0.05 },
    { 1.12,  0.01,  0.18, -0.07,  0.57,  0.38,  4.38, -0.99, 3.94,  3.74,  3.67, -0.93,  4.43,  0.00,  4.51, -0.76 },
    { 1.46,  0.22,  0.50,  0.17,  1.23,  0.80,  2.35, -0.07, 2.50,  1.78,  1.58, -0.01,  5.12,  0.25,  5.06,  0.01 },
    { 5.40, -0.81,  5.32, -0.56,  5.42, -0.43,  5.42, -0.66, 5.49,  0.03,  5.42, -0.47,  5.42,  0.13,  5.40, -0.61 }
};*/

//log-Werte der 16 Scheiben, aufsteigend geordnet, beginnend bei 0 (also Scheibe 16, weil ja Index usw. :)
std::vector<std::vector<double>> M = {
    { -0.03,  5.16,  0.34,  5.03, -0.06,  1.37,  1.25,  2.02, -0.10,  1.74,  0.27,  0.45,  0.17,  0.69,  0.10,  0.60 },
    { -0.05,  4.77,  0.27,  4.90, -0.11,  1.28,  1.62,  1.93, -0.09,  1.67,  0.43,  0.60, -0.00,  0.44,  0.08,  0.92 },
    { -0.76,  4.51,  0.00,  4.43, -0.93,  3.67,  3.74,  3.94, -0.99,  4.38,  0.38,  0.57, -0.07,  0.18,  0.01,  1.12 },
    {  0.01,  5.06,  0.25,  5.12, -0.01,  1.58,  1.78,  2.50, -0.07,  2.35,  0.80,  1.23,  0.17,  0.50,  0.22,  1.46 },
    { -0.61,  5.40,  0.13,  5.42, -0.47,  5.42,  0.03,  5.49, -0.66,  5.42, -0.43,  5.42, -0.56,  5.32, -0.81,  5.40 }
};

//Testwert, sind die Zahlen einer 16er Scheibe (zweiter Datenblock in Exceltabelle von Scheibe 16)
std::vector<double> x = { 0.63,0.88,1.13,1.44,5.42 };

void print_vector(std::vector<double> vec) {
    for (double x : vec) {
        std::cout << x << " ";
    }
    std::cout << "\n" << std::endl;
}
void print_matrix(std::vector<std::vector<double>> mat) {
    for (std::vector<double> v : mat) {
        std::cout << " ";
        for (double x : v) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n" << std::endl;
}

//berechnet den Mittelwert 
std::vector<double> calc_Mittelwert() {
    std::vector<double> mu(c, 0.0);
    for (int i = 0;i < c;i++) {
        double x_i = 0;
        for (int k = 0;k < n;k++) {
            x_i += M[i][k];
        }
        mu[i] = x_i / n;
    }
    return mu;
}

//berechnet die Varianz je Farbe - also wie stark diese streuen
std::vector<double> calc_Varianz(std::vector<double> mu) {
    std::vector<double> sigma(c, 0.0);
    for (int i = 0;i < c;i++) {
        double sum_i = 0;
        for (int k = 0;k < n;k++) {
            double factor = (M[i][k] - mu[i]);
            sum_i += factor * factor;
        }
        sigma[i] = sum_i / n;
    }
    return sigma;
}
//berechnet den Abstand, allerdings mit Gewichtung (Rücksichtnahme auf Varianz)
std::vector<double> calc_Norm(std::vector<double> sigma) {
    std::vector<double> distance(n, 0.0);
    for (int k = 0;k < n;k++) {
        double sum_k = 0;
        for (int i = 0;i < c;i++) {
            double factor = ((x[i] - M[i][k]) / sigma[i]);
            sum_k += factor * factor;
        }
        distance[k] = std::sqrt(sum_k);
    }
    return distance;
}

//wertet die Distanzen aus (sortiert die Distanzen - je kleiner desto besser)
std::vector<std::vector<double>> findClass(std::vector<double> distance) {
    std::vector<std::vector<double>> distanceIndex(n, std::vector<double>(2));
    for (int k = 0;k < n;k++) {
        distanceIndex[k][0] = distance[k];
        distanceIndex[k][1] = k;
        std::cout << distanceIndex[k][0] << " mit Index " << distanceIndex[k][1] << std::endl;
    }
    std::sort(distanceIndex.begin(), distanceIndex.end(), [](const auto& a, const auto& b) {return a[0] < b[0];});
    return distanceIndex;
}

int main() {
    std::vector<double> mu = calc_Mittelwert();
    std::cout << "mu ";
    print_vector(mu);
    std::vector<double> sigma = calc_Varianz(mu);
    std::cout << "sigma ";
    print_vector(sigma);

    std::vector<double> distance = calc_Norm(sigma);
    std::vector<std::vector<double>> distanceIndex = findClass(distance);
    print_matrix(distanceIndex);
    return 0;
}




#include <iostream>
using namespace std;

template <typename T, int N, int M>
class Matrice {

private:
    T data[N][M];

public:

    // 1. Constructeur par défaut : initialisation à 0
    Matrice() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = 0;
            }
        }
    }

    // 2. Constructeur avec liste d'initialisation
    Matrice(const T (&valeurs)[N][M]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                data[i][j] = valeurs[i][j];
            }
        }
    }

    // 3. Accès à un élément
    T& operator()(int i, int j) {
        return data[i][j];
    }

    // 4. Addition de deux matrices
    Matrice<T, N, M> operator+(const Matrice<T, N, M>& autre) const {

        Matrice<T, N, M> resultat;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                resultat.data[i][j] = data[i][j] + autre.data[i][j];
            }
        }

        return resultat;
    }

    // 5. Multiplication de deux matrices
    template <int P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {

        Matrice<T, N, P> resultat;

        for (int i = 0; i < N; i++) {

            for (int j = 0; j < P; j++) {

                resultat.data[i][j] = 0;

                for (int k = 0; k < M; k++) {
                    resultat.data[i][j] += data[i][k] * autre.data[k][j];
                }
            }
        }

        return resultat;
    }

    // 6. Surcharge de l'opérateur <<
    template <typename U, int L, int C>
    friend ostream& operator<<(ostream& os, const Matrice<U, L, C>& mat);
};


// Définition de l'opérateur <<
template <typename U, int L, int C>
ostream& operator<<(ostream& os, const Matrice<U, L, C>& mat) {

    for (int i = 0; i < L; i++) {

        for (int j = 0; j < C; j++) {
            os << mat.data[i][j] << "\t";
        }

        os << endl;
    }

    return os;
}


// PROGRAMME PRINCIPAL
int main() {

    // TEST 1 : MATRICES D'ENTIERS

    cout << "===== MATRICES INT =====" << endl;

    int valeursA[2][2] = {
        {1, 2},
        {3, 4}
    };

    int valeursB[2][2] = {
        {5, 6},
        {7, 8}
    };

    Matrice<int, 2, 2> A(valeursA);
    Matrice<int, 2, 2> B(valeursB);

    // Addition
    Matrice<int, 2, 2> C = A + B;

    cout << "Addition A + B :" << endl;
    cout << C;

    // Multiplication
    Matrice<int, 2, 2> D = A * B;

    cout << "\nMultiplication A * B :" << endl;
    cout << D;


    // TEST 2 : MULTIPLICATION DE DIMENSIONS DIFFERENTES

    cout << "\n===== MATRICES DE DIMENSIONS DIFFERENTES =====" << endl;

    int valeursX[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int valeursY[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    Matrice<int, 2, 3> X(valeursX);
    Matrice<int, 3, 2> Y(valeursY);

    Matrice<int, 2, 2> Z = X * Y;

    cout << "Resultat X * Y :" << endl;
    cout << Z;


    // TEST 3 : MATRICES DOUBLE

    cout << "\n===== MATRICES DOUBLE =====" << endl;

    double valeursF[2][2] = {
        {1.5, 2.5},
        {3.5, 4.5}
    };

    double valeursG[2][2] = {
        {0.5, 1.5},
        {2.5, 3.5}
    };

    Matrice<double, 2, 2> F(valeursF);
    Matrice<double, 2, 2> G(valeursG);

    Matrice<double, 2, 2> H = F + G;

    cout << "Addition F + G :" << endl;
    cout << H;

    Matrice<double, 2, 2> I = F * G;

    cout << "Multiplication F * G :" << endl;
    cout << I;

    return 0;
}

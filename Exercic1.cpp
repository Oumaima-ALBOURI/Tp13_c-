
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class ArrayDyn {

private:
    T* data;
    size_t capacite;
    size_t taille;

    // Agrandir la capacité du tableau
    void agrandir() {
        size_t nouvelleCapacite = (capacite == 0) ? 1 : capacite * 2;

        T* nouveau = new T[nouvelleCapacite];

        for (size_t i = 0; i < taille; i++) {
            nouveau[i] = data[i];
        }

        delete[] data;

        data = nouveau;
        capacite = nouvelleCapacite;
    }

public:

    // 1. Constructeur par défaut
    ArrayDyn() {
        data = nullptr;
        capacite = 0;
        taille = 0;
    }

    // 2. Constructeur avec capacité initiale
    ArrayDyn(size_t cap) {
        data = new T[cap];
        capacite = cap;
        taille = 0;
    }

    // 3. Constructeur de copie
    ArrayDyn(const ArrayDyn<T>& autre) {
        capacite = autre.capacite;
        taille = autre.taille;

        data = (capacite > 0) ? new T[capacite] : nullptr;

        for (size_t i = 0; i < taille; i++) {
            data[i] = autre.data[i];
        }
    }

    // 4. Opérateur d'affectation
    ArrayDyn<T>& operator=(const ArrayDyn<T>& autre) {

        if (this != &autre) {

            T* nouveau = (autre.capacite > 0)
                         ? new T[autre.capacite]
                         : nullptr;

            for (size_t i = 0; i < autre.taille; i++) {
                nouveau[i] = autre.data[i];
            }

            delete[] data;

            data = nouveau;
            capacite = autre.capacite;
            taille = autre.taille;
        }

        return *this;
    }

    // 5. Destructeur
    ~ArrayDyn() {
        delete[] data;
    }

    // 6. Ajouter un élément
    void push_back(const T& element) {

        if (taille == capacite) {
            agrandir();
        }

        data[taille] = element;
        taille++;
    }

    // 7. Supprimer le dernier élément
    void pop_back() {

        if (taille == 0) {
            throw out_of_range("Le tableau est vide !");
        }

        taille--;
    }

    // 8. Accès avec contrôle des bornes
    T& operator[](size_t indice) {

        if (indice >= taille) {
            throw out_of_range("Indice invalide !");
        }

        return data[indice];
    }

    // 9. Classe interne Iterator
    class Iterator {

    private:
        T* ptr;

    public:

        Iterator(T* p = nullptr) {
            ptr = p;
        }

        // Accéder à l'élément
        T& operator*() const {
            return *ptr;
        }

        // Avancer
        Iterator& operator++() {
            ptr++;
            return *this;
        }

        // Reculer
        Iterator& operator--() {
            ptr--;
            return *this;
        }

        // Comparer deux itérateurs
        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }
    };

    // 10. Début du tableau
    Iterator begin() {
        return Iterator(data);
    }

    // 11. Fin du tableau
    Iterator end() {
        return Iterator(data + taille);
    }

    // Afficher la taille
    size_t getTaille() const {
        return taille;
    }
};


// Classe maison pour le test
class Etudiant {

private:
    string nom;
    int age;

public:
    Etudiant(string n, int a) {
        nom = n;
        age = a;
    }

    void afficher() const {
        cout << nom << " - " << age << " ans" << endl;
    }
};


// Programme principal
int main() {

    // TEST 1 : Tableau d'entiers
    cout << "===== TABLEAU INT =====" << endl;

    ArrayDyn<int> nombres;

    nombres.push_back(10);
    nombres.push_back(20);
    nombres.push_back(30);

    for (auto &e : nombres) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 2 : Tableau de chaines
    cout << "\n===== TABLEAU STRING =====" << endl;

    ArrayDyn<string> noms;

    noms.push_back("Oumaima");
    noms.push_back("Sara");
    noms.push_back("Amine");

    for (auto &e : noms) {
        cout << e << endl;
    }


    // TEST 3 : Tableau d'objets
    cout << "\n===== TABLEAU ETUDIANT =====" << endl;

    ArrayDyn<Etudiant> etudiants;

    etudiants.push_back(Etudiant("Ali", 20));
    etudiants.push_back(Etudiant("Sara", 21));

    for (auto &e : etudiants) {
        e.afficher();
    }


    // TEST 4 : Constructeur de copie
    cout << "\n===== COPIE =====" << endl;

    ArrayDyn<int> copie(nombres);

    for (auto &e : copie) {
        cout << e << " ";
    }

    cout << endl;


    // TEST 5 : Operator[]
    cout << "\n===== ACCES PAR INDICE =====" << endl;

    cout << nombres[1] << endl;


    // TEST 6 : pop_back()
    nombres.pop_back();

    cout << "\n===== APRES POP_BACK =====" << endl;

    for (auto &e : nombres) {
        cout << e << " ";
    }

    cout << endl;

    return 0;
}

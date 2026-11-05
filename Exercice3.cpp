
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// 1. Exception : pile pleine
class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est pleine !";
    }
};

// 2. Exception : pile vide
class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la pile est vide !";
    }
};


// 3. Classe generique Stack
template <typename T>
class Stack {

private:
    unique_ptr<T[]> data;
    size_t capacity;
    size_t top;

public:

    // Constructeur avec capacite par defaut
    Stack(size_t cap = 100)
        : data(make_unique<T[]>(cap)),
          capacity(cap),
          top(0) {

        if (cap == 0) {
            throw invalid_argument("Capacite invalide !");
        }
    }

    // Constructeur avec iterateurs
    template <typename Iterator>
    Stack(Iterator debut, Iterator fin)
        : data(nullptr), capacity(0), top(0) {

        // Compter les elements
        for (Iterator it = debut; it != fin; ++it) {
            capacity++;
        }

        if (capacity == 0) {
            capacity = 1;
        }

        data = make_unique<T[]>(capacity);

        // Copier les elements dans la pile
        for (Iterator it = debut; it != fin; ++it) {
            data[top] = *it;
            top++;
        }
    }

    // Ajouter un element
    void push(const T& element) {

        if (top == capacity) {
            throw StackOverflow();
        }

        data[top] = element;
        top++;
    }

    // Retirer le dernier element
    void pop() {

        if (empty()) {
            throw StackUnderflow();
        }

        top--;
    }

    // Consulter le sommet
    const T& peek() const {

        if (empty()) {
            throw StackUnderflow();
        }

        return data[top - 1];
    }

    // Verifier si la pile est vide
    bool empty() const {
        return top == 0;
    }

    // Afficher les elements
    void afficher() const {

        cout << "Pile : ";

        for (size_t i = 0; i < top; i++) {
            cout << data[i] << " ";
        }

        cout << endl;
    }

    // Obtenir la taille
    size_t size() const {
        return top;
    }

    // Obtenir la capacite
    size_t getCapacity() const {
        return capacity;
    }
};


// 4. Programme principal
int main() {

    try {

        cout << "===== TEST 1 : PILE INT =====" << endl;

        Stack<int> s(3);

        s.push(10);
        s.push(20);
        s.push(30);

        s.afficher();

        cout << "Sommet : " << s.peek() << endl;

        s.pop();

        cout << "Apres pop : ";
        s.afficher();


        cout << "\n===== TEST 2 : STACK OVERFLOW =====" << endl;

        s.push(40);
        s.push(50); // La pile est pleine

    }
    catch (const StackOverflow& e) {
        cout << e.what() << endl;
    }


    try {

        cout << "\n===== TEST 3 : STACK UNDERFLOW =====" << endl;

        Stack<string> noms(2);

        noms.push("Oumaima");
        noms.push("Sara");

        noms.afficher();

        noms.pop();
        noms.pop();

        noms.pop(); // La pile est vide

    }
    catch (const StackUnderflow& e) {
        cout << e.what() << endl;
    }


    cout << "\n===== TEST 4 : ITERATEURS =====" << endl;

    vector<int> nombres = {10, 20, 30, 40};

    Stack<int> s2(nombres.begin(), nombres.end());

    s2.afficher();

    cout << "Sommet : " << s2.peek() << endl;


    cout << "\n===== TEST 5 : GRAND NOMBRE D'ELEMENTS =====" << endl;

    Stack<int> grandePile(100000);

    for (int i = 0; i < 100000; i++) {
        grandePile.push(i);
    }

    cout << "Nombre d'elements : " << grandePile.size() << endl;
    cout << "Sommet : " << grandePile.peek() << endl;

    cout << "Test termine !" << endl;

    return 0;
}

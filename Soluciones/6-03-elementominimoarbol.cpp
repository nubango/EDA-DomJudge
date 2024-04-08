// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

// METODO 1: OPERACION INTERNA
template <class T>
class tree_plus : public bintree<T> {
	using Link = typename bintree<T>::Link;
public:
	T getElemMinimo() const {
		return getElemMinimo(this->raiz);
	}

private:
	static T getElemMinimo(Link raiz) {
		return 0;
	}
};

// METODO 2: OPERACION EXTERNA
template <class T>
T elemMinimo(bintree<T> const& tree) {
	T solucion
		if (tree.empty())
			;
		else
			;
	return solucion;
}

void resuelveCaso() {
	// metodo 1
	tree_plus<int> tree_plus;
	(bintree<int>)tree_plus = leerArbol(-1);
	cout << tree_plus.getElemMinimo() << "\n";

	// metodo 2
	/*
	bintree<int> tree;
	tree = leerArbol(-1);
	cout << elemMinimo(tree) << "\n";
	*/
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}

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
	vector<T> getFrontera() const {
		return getFrontera(this->raiz);
	}

private:
	static vector<T> getFrontera(Link raiz) {
		return nullptr;
	}
};

// METODO 2: OPERACION EXTERNA
template <class T>
vector<T> frontera(bintree<T> const& tree) {
	vector<T> solucion;
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
	vector<int> solucion = tree_plus.getFrontera();

	// metodo 2
	/*
	bintree<int> tree;
	tree = leerArbol(-1);
	vector<int> solucion = frontera(tree);
	*/

	for (int e : solucion)
		cout << e << " ";
	cout << "\n";
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

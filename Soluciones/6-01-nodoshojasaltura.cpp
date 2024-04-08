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
	// árbol vacío
	tree_plus() : this->raiz(nullptr) {}

	// árbol hoja
	tree_plus(T const& e) :
		this->raiz(std::make_shared<TreeNode>(nullptr, e, nullptr)) {}

	// árbol con dos hijos
	tree_plus(tree_plus<T> const& l, T const& e, tree_plus<T> const& r) :
		this->raiz(std::make_shared<TreeNode>(l.raiz, e, r.raiz)) {}

	int getNumNodos() const {
		return getNumNodos_rec(this->raiz);
	}

	int getNumHojas() const {
		return getNumHojas_rec(this->raiz);
	}

	int getAltura() const {
		return getAltura_rec(this->raiz);
	}

private:
	static int getNumNodos_rec(Link a) {
		if (a == nullptr)
			return 0;

		return 1 + getNumNodos_rec(a->left) + getNumNodos_rec(a->right);
	}

	static int getNumHojas_rec(Link a) {
		if (a == nullptr)
			return 0;

		if (a->left == nullptr && a->right == nullptr)
			return 1;

		return getNumHojas_rec(a->left) + getNumHojas_rec(a->right);
	}

	static int getAltura_rec(Link a) {
		if (a == nullptr)
			return 0;

		return 1 + std::max(getAltura_rec(a->left), getAltura_rec(a->right));
	}
};

template <typename T>
inline tree_plus<T> leerArbol_plus(T vacio) {
	T raiz;
	std::cin >> raiz;
	if (raiz == vacio) { // es un árbol vacío
		return {};
	}
	else { // leer recursivamente los hijos
		auto iz = leerArbol(vacio);
		auto dr = leerArbol(vacio);
		return { iz, raiz, dr };
	}
}

// METODO 2: OPERACION EXTERNA
struct Solucion {
	int nodos;
	int hojas;
	int altura;
};

// funcion externa recursiva que recibe como parametro un arbol binario
// devuelve las tres propiedades, recorriendo el arbol una sola vez
template <class T>
Solucion nodosHojasAltura(bintree<T> const& tree) {
	Solucion solucion;
	if (tree.empty())
		solucion = { 0,0,0 };
	else
	{
		Solucion solIz = nodosHojasAltura(tree.left());
		Solucion solDr = nodosHojasAltura(tree.right());

		solucion.nodos = 1 + solIz.nodos + solDr.nodos;
		solucion.hojas = (tree.left().empty() && tree.right().empty()) ? 1 : solIz.hojas + solDr.hojas;
		solucion.altura = 1 + max(solIz.altura, solDr.altura);
	}
	return solucion;
}

void resuelveCaso() {
	// metodo 1
	tree_plus<char> tree_plus;
	tree_plus = leerArbol_plus('.');
	int nodos = tree_plus.getNumNodos();
	int hojas = tree_plus.getNumHojas();
	int altura = tree_plus.getAltura();
	cout << nodos << " " << hojas << " " << altura << "\n";

	// metodo 2
	/*
	bintree<char> tree;
	tree = leerArbol('.');
	Solucion solucion = nodosHojasAltura(tree);
	cout << solucion.nodos << " " << solucion.hojas << " " << solucion.altura << "\n";
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

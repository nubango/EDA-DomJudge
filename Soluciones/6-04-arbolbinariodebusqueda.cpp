// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

// un arbol binario de busqueda es un arbol binario cuyos nodos almacenan valores que se mantienen
// ordenados de la siguiente manera: la raız del arbol contiene un valor que es estrictamente mayor que
// todos los valores en el hijo izquierdo y estrictamente menor que todos los valores en el hijo derecho;
// ademas, ambos hijos son arboles binarios de busqueda
// O(n) donde n es el numero de nodos del arbol tree
bool esABB(const bintree<int>& tree, int& min, int& max) {
	// el arbol vacio es un ABB
	if (tree.empty()) {
		min = 0; max = 0;
		return true;
	}

	int minIz, maxIz, minDr, maxDr;

	// los subarboles deben ser ABB tambien y hay que guardar los valores maximos y minimos para saber si estan ordenados
	bool izABB = esABB(tree.left(), minIz, maxIz);
	bool drABB = esABB(tree.right(), minDr, maxDr);

	// el nodo actual debe cumplir la propiedad del ABB
	// si el hijo izquierdo no esta vacio, el maximo debe ser menor que la raiz del arbol
	// si el hijo derecho no esta vacio, la raiz debe tener un valor menor que el minimo
	bool ordenado = (tree.left().empty() || maxIz < tree.root()) &&
		(tree.right().empty() || tree.root() < minDr);

	// los valores minimos y maximos del subarbol actual se actualizan
	min = tree.left().empty() ? tree.root() : minIz;
	max = tree.right().empty() ? tree.root() : maxDr;

	// si cumple la propiedad de ser un ABB y sus hijos tambien, sera un ABB
	return izABB && drABB && ordenado;
}

bool esABB(const bintree<int>& tree) {
	int min = 0; int max = 0;
	return esABB(tree, min, max);
}

void resuelveCaso() {
	bintree<int> tree;
	tree = leerArbol(-1);

	cout << ((esABB(tree)) ? "SI\n" : "NO\n");
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
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// los valores del vector v se han obtenido aplicando una rotacion sobre un vector ordenado en orden estrictamente creciente
// O(log n) donde n es el numero de elementos del vector v
// la funcion devuelve true si encuentra el elemento elem en el vector v
bool existeElemento(const vector<int>& v, int elem, int ini, int fin) {
	int n = fin - ini;

	// caso base: un elemento
	if (n == 1)
		return v[ini] == elem;

	int mitad = (fin + ini) / 2;

	// si la mitad izquierda esta ordenada (el elemento inicial es menor que el elemento mitad)
	if (v[ini] <= v[mitad]) {
		// si el elemento que buscamos deberia estar en la mitad izquierda, buscamos en esa mitad
		if (elem >= v[ini] && elem < v[mitad])
			return existeElemento(v, elem, ini, mitad);
		else
			return existeElemento(v, elem, mitad, fin);
	}
	// si no, esta "desordenada"
	else {
		if (elem >= v[mitad] && elem < v[ini])
			return existeElemento(v, elem, mitad, fin);
		else
			return existeElemento(v, elem, ini, mitad);
	}
}

bool resuelveCaso() {
	int n;
	int m;
	cin >> n >> m;

	if (n == -1)
		return false;

	vector<int> v(n);
	for (int& e : v)
		cin >> e;

	cout << (existeElemento(v, m, 0, n) ? "SI\n" : "NO\n");

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 

	while (resuelveCaso());

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
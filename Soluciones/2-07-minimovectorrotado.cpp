// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// v es un vector estrictamente decreciente pero con una rotacion de un numero desconocido de elementos
// O(log n) donde n=v.size ya que no se recorre completamente el vector
int minimo(const vector<int>& v, int ini, int fin) {
	int n = fin - ini;
	// caso base: 1 elemento
	if (n == 1)
		return v[ini];

	int mitad = (fin + ini) / 2;
	// si el elemento mitad es menor que el elemento ini, es que a pesar de la rotacion
	// el elemento menor sera la mitad o un elemento a su derecha
	if (v[mitad] < v[ini])
		return minimo(v, mitad, fin);
	// si no, el elemento minimo estara en la mitaz izquierda sin incluir el elemento mitad
	else
		return minimo(v, ini, mitad);
}

bool resuelveCaso() {
	int n;
	cin >> n;

	if (!std::cin)
		return false;

	vector<int> v(n);
	for (int& e : v)
		cin >> e;

	cout << minimo(v, 0, n) << "\n";

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
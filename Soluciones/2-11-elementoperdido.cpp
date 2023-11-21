// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;
// Se tienen dos vectores de enteros ordenados y distintos entre si con n y n-1 elementos respectivamente
// Los elementos de b son los mismos que tiene a excepto uno que falta
// Se pide implementar un algoritmo recursivo eficiente que encuentre ese valor que falta

// devuelve el indice en el que se escuentra el valor de v1 que no existe en v2
// O(log n) donde n es el numero de elementos de v1
int resolver(vector<int> const& v1, vector<int> const& v2, int ini, int fin) {
	int n = fin - ini;
	// hay dos casos base que devuelven el valor ini
	// el caso base en el que v2 no tiene elementos
	// el caso base en el que el elemento distinto es ini
	if (n == 0 || v1[ini] != v2[ini])
		return ini;
	// caso base: v2 tiene un elemento
	if (n == 1)
		return ini + 1;

	int mitad = (fin + ini) / 2;

	// si elemento mitad de v1 es menor que el de v2, el elemento que buscamos esta en la mitad izquierda
	if (v1[mitad] < v2[mitad])
		return resolver(v1, v2, ini, mitad);
	else
		return resolver(v1, v2, mitad, fin);
}

void resuelveCaso() {
	long long int numElementos;
	cin >> numElementos;
	vector<int> v1(numElementos);
	vector<int> v2(numElementos - 1);
	for (int& e : v1) cin >> e;
	for (int& e : v2) cin >> e;
	int sol = resolver(v1, v2, 0, v1.size() - 1);
	cout << v1[sol] << '\n';
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 

	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// diremos que el elemento en posicion i esta bien situado si v[i] == i
// O(log n) donde n=v.size porque no se recorre el vector completo,
// dado el indice mitad, se va eligiendo que mitad del vector se recorre
bool elementoSituado(const vector<int>& v, int ini, int fin) {
	int n = fin - ini;
	// caso base: 0 elementos
	// por definicion, un vector sin elementos no tiene ningun elemento bien situado
	if (n == 0)
		return false;
	// caso base: 1 elemento
	// si el elemento coincide con su indice estara bien situado
	if (n == 1)
		return (v[ini] == ini);

	int mitad = (fin + ini) / 2;

	// si el elemento mitad es mayor que el indice, es que no hay ningun elemento a su derecha bien situado
	if (v[mitad] > mitad)
		return elementoSituado(v, ini, mitad);
	// si el elemento mitad es menor que el indice, puede que haya algun elemento a la derecha bien situado
	else if (v[mitad] < mitad)
		return elementoSituado(v, mitad, fin);
	else // if(v[mitad] = mitad)
		return true;
}

void resuelveCaso() {
	int n;
	cin >> n;

	vector<int> sec(n);
	for (int& e : sec)
		cin >> e;

	cout << (elementoSituado(sec, 0, n) ? "SI\n" : "NO\n");
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

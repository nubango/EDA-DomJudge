// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// estructura auxiliar que devuelve el metodo que resuelve el problema numPicosValles
struct datos {
	int picos;
	int valles;
};

// se recorre el vector una sola vez comprobando tanto picos como valles
// O(n) donde n es v.size()
datos numPicosValles(const vector<int>& v) {
	int picos = 0, valles = 0;

	// si hay dos elementos o menos no puede haber ni picos ni valles
	if (v.size() <= 2)
		return { 0,0 };

	// se recorre el vector empezando en el elemento 1 para poder comparar con el anterior
	for (int i = 1; i < v.size() - 1; i++) {
		// si tanto el elemento anterior como el siguiente a i son mayores que i, i es un valle
		if (v[i - 1] > v[i] && v[i] < v[i + 1])
			valles++;
		// si tanto el elemento anterior como el siguiente a i son menores que i, i es un pico
		else if (v[i - 1] < v[i] && v[i] > v[i + 1])
			picos++;
	}

	return { picos, valles };
}

void resuelveCaso() {
	int n;
	cin >> n;

	vector<int> v(n);

	for (int& e : v)
		cin >> e;

	datos d = numPicosValles(v);

	cout << d.picos << " "  << d.valles << "\n";
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
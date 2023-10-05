// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// diremos que un vector esta parcialmente ordenado si el valor maximo de su mitad derecha es mayor o igual que todos los valores de la mitad izquierda
// y el valor minimo de su mitad izquierda es menor o igual que todos los valores de su mitad derecha
// ademas tanto la mitad izquierda como la derecha cumplen que estan parcialmente ordenadas
// O(n) donde n es el numero de elementos del vector v
bool parcialmenteOrdenado(const vector<int>& v, int ini, int fin, int& min, int& max) {
	int n = fin - ini;
	// si el vector tiene un solo elemento esta ordenado por definicion
	if (n == 1)
		return true;
	// caso base: dos elementos, el de la izquierda debe ser menor o igual que el de la derecha
	if (n == 2)
	{
		min = v[ini];
		max = v[ini + 1];
		return min <= max;
	}

	int mitad = (ini + fin) / 2;
	int minI, minD, maxI, maxD;
	bool ordIz = parcialmenteOrdenado(v, ini, mitad, minI, maxI);
	bool ordDr = parcialmenteOrdenado(v, mitad, fin, minD, maxD);
	min = std::min(minI, minD);
	max = std::max(maxI, maxD);
	// se han de cumplir todos los requisitos de ordenacion de ambas mitades
	return ordIz && ordDr && (maxI <= maxD) && (minI <= minD);
}

bool parcialmenteOrdenado(const vector<int>& v) {
	int min, max;
	// la llamada inicial es recomendable que sea con ini=0 y fin=v.size
	// para que las llamadas recursivas sean desde ini incluido hasta fin sin incluir
	return parcialmenteOrdenado(v, 0, v.size(), min, max);
}

bool resuelveCaso() {
	int e;
	cin >> e;
	if (e == 0)
		return false;

	vector<int> sec;
	while (e != 0) {
		sec.push_back(e);
		cin >> e;
	}
	cout << (parcialmenteOrdenado(sec) ? "SI\n" : "NO\n");
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
#endif

	return 0;
}
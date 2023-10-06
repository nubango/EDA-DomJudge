// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// dados una serie de valores cuyo perfil se ajusta al de una curva concava, 
// siendo estrictamente decrecientes hasta un determinado valor a partir del 
// cual son estrictamente crecientes, se pide encontrar el valor del mınimo
// O(log n) donde n = v.size, ya que no se recorre completamente el vector, si no
// que se decide en que mitad buscar el valor en cada llamada recursiva
int minimo(const vector<int>& sec, int ini, int fin) {
	int n = fin - ini;

	// caso base: un solo elemento
	if (n == 1)
		return sec[ini];

	int mitad = (fin + ini) / 2;

	// si el valor de la mitad es mayor que su anterior, implica que el minimo estara a la izquierda
	if (sec[mitad] > sec[mitad - 1])
		return minimo(sec, ini, mitad);
	// si es valor de la mitad es menor que su valor anterior, puede ser el valor mitad o alguno a su derecha
	else if (sec[mitad] < sec[mitad - 1])
		return minimo(sec, mitad, fin);
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!cin)
		return false;

	vector<int> sec(n);
	for (int& e : sec)
		cin >> e;

	cout << minimo(sec, 0, n) << endl;
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());;

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
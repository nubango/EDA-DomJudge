// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// dado un vector de numeros enteros positivos y consecutivos del que se han eliminado todos los elementos impares menos uno
// encuentre cual es ese numero impar que ha quedado en el vector
// O(log n) donde n es el numero de elementos del vector v
int elementoImpar(const vector<int>& v, int ini, int fin) {
	int n = fin - ini;
	// caso base: un elemento
	if (n == 1)
		return v[ini];

	// caso base: el elemento que buscamos es ini
	if (v[ini] % 2 != 0)
		return v[ini];

	int mitad = (fin + ini) / 2;

	// caso base: el elemento que buscamos es mitad
	if (v[mitad] % 2 != 0)
		return v[mitad];

	// si el elemento mitad es mayor o igual que el elemento que deberia estar
	// en esa posicion (tomando como referencia ini) se busca en la mitad derecha
	if (v[mitad] >= v[ini] + 2 * (mitad - ini))
		return elementoImpar(v, mitad + 1, fin);
	else
		return elementoImpar(v, ini + 1, mitad);
}

bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;

	vector<int> v(n);
	for (int& e : v)
		cin >> e;

	cout << elementoImpar(v, 0, n) << "\n";

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
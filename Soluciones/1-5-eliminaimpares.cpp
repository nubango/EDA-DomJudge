// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// O(n) siendo n = v.size()
void eliminaImpares(vector<long long int>& v) {
	// iterador del "nuevo" vector formado solo por pares
	int elems = 0;
	// i es el iterador del vector completo original
	for (int i = 0; i < v.size(); i++) {
		// si es par necesitamos mantenerlo
		if (v[i] % 2 == 0) {
			// asignamos el par al siguiente hueco disponible marcado por elems
			v[elems] = v[i];
			elems++;
		}
	}
	// el vector ahora tiene 'elems' elementos y se llama a resize
	// resize tiene coste linear en el numero de elementos insertados/eliminados
	// en el caso peor O(n) siendo n v.size() porque seria que todos los elementos del vector fuesen impares y habria que borrarlos todos
	v.resize(elems);
}

void escribeVector(const vector<long long int>& v) {
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "\n";
}

void resuelveCaso() {
	long long int n;
	cin >> n;

	vector<long long int> v(n, 0);

	for (int i = 0; i < v.size(); i++) {
		cin >> n;
		v[i] = n;
	}

	eliminaImpares(v);
	escribeVector(v);
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
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// Solo se recorre una vez el vector v por lo que
// O(n) siendo n = v.size() 
void mejorIntervalo(const vector<int>& v, int t, int& ini, int& fin) {
	// la secuencia solucion
	int maxLongitud = 0;
	// la secuencia actual
	int longActual = 0;

	for (int i = 0; i < v.size(); i++) {
		// si el valor supera el umbral t forma parte de la secuencia que se busca
		if (v[i] > t)
			longActual++;
		// si no, la secuencia termina
		else
			longActual = 0;

		// se comprueba si tenemos una mejor secuencia
		// tiene que ser estrictamente mayor, para en caso de haber dos iguales
		// que sea prioritaria la primera en encontrarse
		if (longActual > maxLongitud) {
			maxLongitud = longActual;
			// se actualizan los valores solucion: posiciones de inicio y final de la secuencia
			ini = i - maxLongitud + 1;
			fin = i;
		}
	}
}

void resuelveCaso() {
	int n, t;
	cin >> n >> t;
	vector<int> v(n, 0);

	for (int i = 0; i < v.size(); i++) {
		cin >> n;
		v[i] = n;
	}

	int ini, fin;
	mejorIntervalo(v, t, ini, fin);
	cout << ini << " " << fin << "\n";
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
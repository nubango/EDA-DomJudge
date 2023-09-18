// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// se recorre una vez el vector
// O(n) donde n es v.size()
bool bienDividido(const vector<int>& v, int p) {
	// si el valor p es el ultimo del vector, se considera que esta bien dividido
	if (p == v.size() - 1)
		return true;

	// se inicializan con el primer y el ultimo elemento del vector 
	int maxIz = v[0], minDr = v[v.size() - 1];

	// dada la incializacion se ajustan los recorridos de los fors (i=1, i<=p, i=p+1, i<size-1)
	for (int i = 1; i <= p; i++) {
		// se actualiza para saber que valor es el mayor hasta p
		if (v[i] > maxIz)
			maxIz = v[i];
	}
	for (int i = p + 1; i < v.size() - 1; i++) {
		// se actualiza para saber que valor es el menor desde p hasta el final
		if (v[i] < minDr)
			minDr = v[i];
	}

	// si el maximo izquierdo es menor que el minimo derecho es que esta bien ordenado
	return maxIz < minDr;
}

void resuelveCaso() {
	int n, p;
	cin >> n >> p;

	vector<int> v(n);

	for (int i = 0; i < v.size(); i++) {
		cin >> n;
		v[i] = n;
	}

	if (bienDividido(v, p))
		cout << "SI\n";
	else
		cout << "NO\n";
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
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// se recorre una vez completo el vector
// O(n) donde n es v.size
bool esDalton(const vector<int>& v) {
	int i = 0;
	bool creciente = true, decreciente = true;

	// hasta size-1 porque accedemos al elemento siguiente dentro del bucle
	while (i < v.size() - 1)
	{
		// si el elemento i es mayor o igual que su siguiente no sera creciente
		if (creciente && v[i] >= v[i + 1])
			creciente = false;
		// su el elemento i es menor o igual que su siguiente no sera decreciente
		if (decreciente && v[i] <= v[i + 1])
			decreciente = false;

		i++;
	}

	// si es creciente o decreciente sera dalton
	return creciente || decreciente;
}

bool resuelveCaso() {
	int n;
	cin >> n;

	if (n == 0)
		return false;

	vector<int> v(n);

	for (int i = 0; i < n; i++) {
		int d;
		cin >> d;
		v[i] = d;
	}

	if (esDalton(v))
		cout << "DALTON\n";
	else
		cout << "DESCONOCIDOS\n";

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
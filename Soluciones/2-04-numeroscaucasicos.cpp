// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// un vector de enteros es caucasico si el valor absoluto de la diferencia entre el 
// numero de elementos pares de sus mitades es, a lo sumo, 2 y cada mitad tambien es caucasica
// un vector con un elemento es caucasico
// el coste es O(n*log n) donde n=v.size
// ya que se realizan operaciones lineales para contar elementos pares en cada division del vector
bool esCaucasico(const vector<int>& v, int ini, int fin, int& nPar) {
	int n = fin - ini;

	if (n == 1) {
		if (v[ini] % 2 == 0)
			nPar = 1;
		else
			nPar = 0;

		return true;
	}

	int mitad = (fin + ini) / 2;
	int nParIz, nParDr;
	bool caucIz = esCaucasico(v, ini, mitad, nParIz);
	bool caucDr = esCaucasico(v, mitad, fin, nParDr);

	nPar = nParIz + nParDr;

	return caucDr && caucIz && abs(nParIz - nParDr) <= 2;
}

bool esCaucasico(const vector<int>& v) {
	int nPar = 0;
	return esCaucasico(v, 0, v.size(), nPar);
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)
		return false;

	vector<int> sec(n);
	for (int& e : sec)
		cin >> e;

	cout << ((esCaucasico(sec)) ? "SI\n" : "NO\n");
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
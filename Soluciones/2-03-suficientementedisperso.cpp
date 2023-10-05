// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// se considera suficientemente disperso si la diferencia entre el primer valor que se saca
// y el ultimo sea mayor o igual que una cantidad K
// tambien la diferencia entre el primer valor y el ultimo tanto de la primera mitad como de la segunda
// sea mayor que K y ademas cada una de sus mitades sea tambien suficientemente dispersa
// O(n) donde n es la longitud del vector
bool suficienteDisperso(const vector<int>& v, int ini, int fin, int k) {
	int n = fin - ini;
	// si solo tiene un elemento se considera suficientemente disperso por definicion
	if (n == 1)
		return true;
	// caso base: dos elementos
	if (n == 2)
	{
		// la diferencia absoluta entre los valores tiene que ser mayor o igual que k
		int dif = abs(v[ini + 1] - v[ini]);
		return dif >= k;
	}

	int mitad = (ini + fin) / 2;
	bool dispIz = suficienteDisperso(v, ini, mitad, k);
	bool dispDr = suficienteDisperso(v, mitad, fin, k);
	int dif = abs(v[fin - 1] - v[ini]);
	// ambas mitades deben cumplir la condicion asi como el primer y ultimo elemento de la seccion
	return dispIz && dispDr && dif >= k;
}

bool suficienteDisperso(const vector<int>& v, int d) {
	return suficienteDisperso(v, 0, v.size(), d);
}

bool resuelveCaso() {
	int n;
	int d;
	cin >> n >> d;

	if (!std::cin)
		return false;

	vector<int> v(n);

	for (int& e : v)
		cin >> e;

	cout << (suficienteDisperso(v, d) ? "SI\n" : "NO\n");

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
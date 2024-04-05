// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

void imprimeSolucion(const vector<char>& sol) {
	for (char s : sol)
		cout << s;
	cout << '\n';
}

// tupla solucion: {c0,... ci, ... cn} donde n sera la longitud de la secuencia y ci sera una letra desde 'a' hasta 'a' + m;
void variacionesConRepeticion(vector<char>& sol, int k, int n, int m) {
	for (char c = 'a'; c < 'a' + m; c++) {
		sol[k] = c;
		if (k == n - 1) // es solucion: si llega al final
			imprimeSolucion(sol);
		else
			variacionesConRepeticion(sol, k + 1, n, m);
	}
}

bool resuelveCaso() {
	int m, n; // m primeras letras del alfabeto, longitud n de las secuencias
	cin >> m >> n;

	if (!std::cin)
		return false;

	vector<char> sol(n);

	variacionesConRepeticion(sol, 0, n, m);

	cout << '\n';

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
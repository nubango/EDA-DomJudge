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
void variacionesSinRepeticion(vector<char>& sol, int k, int n, int m, vector<bool>& usadas) {
	for (char c = 'a'; c < 'a' + m; c++) {
		sol[k] = c;
		if (!usadas[c - 'a']) { // lo primero se comprueba la tabla de apariciones para evitar repeticiones
			if (k == n - 1) // es solucion: si llega al final
				imprimeSolucion(sol);
			else {
				usadas[c - 'a'] = true; // marcado
				variacionesSinRepeticion(sol, k + 1, n, m, usadas);
				usadas[c - 'a'] = false; // desmarcado
			}
		}
	}
}

bool resuelveCaso() {
	int m, n; // m primeras letras del alfabeto, longitud n de las secuencias
	cin >> m >> n;

	if (!std::cin)
		return false;

	vector<char> sol(n);
	vector<bool> usadas(m, false); // tabla de apariciones de las m letras

	variacionesSinRepeticion(sol, 0, n, m, usadas);

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
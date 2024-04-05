// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// comprueba que no este en la misma columna
// para comprobar si no esta en la misma diagonal: si estas a las mismas filas y columnas de distancia en valor absoluto
bool esValida(vector<int>& sol, int& k) {
	int fila = 0;
	while (fila < k) {
		if ((sol[fila] == sol[k]) || ((k - fila) == abs(sol[k] - sol[fila])))
			return false;
		else
			fila++;
	}
	return true;
}

// tupla solucion: {C0, ... Ci, ... Cn-1} siendo Ci la columna en la que se coloca la reina en la fila i y n el numero de reinas y n*n el tam del tablero
void nReinas(vector<int>& sol, int k, int n, int& nSol) {
	for (int col = 0; col < n; col++) {
		sol[k] = col;
		if (esValida(sol, k)) {
			if (k == n - 1) // es solucion: si llega al final
				nSol++;
			else
				nReinas(sol, k + 1, n, nSol);
		}
	}
}

void resuelveCaso() {
	int n;
	cin >> n;

	vector<int> sol(n);

	int nSol = 0;

	nReinas(sol, 0, n, nSol);

	cout << nSol << "\n";
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
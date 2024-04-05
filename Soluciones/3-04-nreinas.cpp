// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// usando la tecnica de marcado: se comprubea que cada columna y cada diagonal esten ocupadas por una reina
// se usan dos vectores de booleanos que dicen que columnas y que diagonales ya estan ocupadas

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
void nReinas(vector<int>& tablero, int k, int n, int& numSoluciones, vector<bool>& colOcupadas, vector<bool>& diagAscOcupadas, vector<bool>& diagDesOcupadas) {
	for (int col = 0; col < n; col++) {
		tablero[k] = col;
		// comprueba las marcas lo primero
		if (!colOcupadas[col] && !diagAscOcupadas[k + col] && !diagDesOcupadas[k - col + n - 1]) {
			if (esValida(tablero, k)) {
				if (k == n - 1) // es solucion: si llega al final
					numSoluciones++;
				else {
					// marcado
					colOcupadas[col] = true;
					diagAscOcupadas[k + col] = true;
					diagDesOcupadas[k - col + n - 1] = true;

					nReinas(tablero, k + 1, n, numSoluciones, colOcupadas, diagAscOcupadas, diagDesOcupadas);

					// desmarcado
					colOcupadas[col] = false;
					diagAscOcupadas[k + col] = false;
					diagDesOcupadas[k - col + n - 1] = false;
				}
			}
		}
	}
}

void resuelveCaso() {
	int n;
	cin >> n;

	vector<int> tablero(n);

	int nSol = 0;

	// vectores auxiliares para las marcas (las marcas trabajan con coste constante)
	vector<bool> columnasOcupadas(n, false);
	vector<bool> diagonalesAscendentesOcupadas(2 * n - 1, false);
	vector<bool> diagonalesDescendentesOcupadas(2 * n - 1, false);

	nReinas(tablero, 0, n, nSol, columnasOcupadas, diagonalesAscendentesOcupadas, diagonalesDescendentesOcupadas);

	cout << nSol << '\n';
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
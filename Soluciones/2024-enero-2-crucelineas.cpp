/*
Nombre completo: Nuria Bango Iglesias
Usuario del juez: VJ05
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


// se hace uso de la tecnica divide y venceras para la resolucion de este problema
// O(log n) donde n es el numero de elementos de cualquiera de los vectores porque han de medir lo mismo
// es log n ya que se elige uno de los caminos respecto a la mitad y nunca se recorre completamente el vector
bool cruceFunciones(const vector<int>& asc, const vector<int>& desc, int ini, int fin, int& posA, int& posD) {
	int n = fin - ini;

	// en el enunciado se especifica que n > 1 siempre
	// caso base: 1 elemento
	if (n == 1) {
		// si los valores son iguales, ese sera el cruce
		if (asc[ini] == desc[ini])
		{
			posA = posD = ini;
			return true;
		}
		else {
			// el cruce se producira despues de estos valores
			if (asc[ini] < desc[ini])
			{
				posA = ini;
				posD = ini + 1;
			}
			// el cruce se produce antes de estos valores
			else {

				posA = ini - 1;
				posD = ini;
			}
			return false;
		}
	}

	int mitad = (fin + ini) / 2;

	// caso base especial: si los elementos mitad son iguales
	// no es imprescindible pero ahorra busquedas ya que tenemos que acceder si o si a este elemento
	if (asc[mitad] == desc[mitad]) {
		posA = posD = mitad;
		return true;
	}

	if (asc[mitad] < desc[mitad])
		return cruceFunciones(asc, desc, mitad, fin, posA, posD);
	else
		return cruceFunciones(asc, desc, ini, mitad, posA, posD);

}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0) return false;
	vector<int> secAsc(n), secDesc(n);
	for (int& e : secAsc) cin >> e;
	for (int& e : secDesc) cin >> e;

	int posA = -1;
	int posB = 0;
	bool sol = cruceFunciones(secAsc, secDesc, 0, n, posA, posB);

	if (sol)
		cout << "SI " << posA << "\n";
	else
		cout << "NO " << posA << " " << posB << "\n";

	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("input2.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// Dado vector ordenado de n elementos en el que los elementos aparecen repetidos dos veces
// excepto uno que solamente aparece una vez, devuelve la posicion de dicho elemento
// O(log n) donde n=v.size ya que no se recorre el vector entero
// en cada llamada a la recurrencia se decide que mitad explorar
int posNoRepetido(const vector<int>& v, int ini, int fin) {
	int n = fin - ini;

	// caso base: un elemento
	if (n == 1)
		return ini;

	int mitad = (fin + ini) / 2;

	// si el elemento mitad esta en una posicion par
	if (mitad % 2 == 0) {
		// si el elemento mitad es igual a su anterior, estara en la mitad izquierda
		if (v[mitad] == v[mitad - 1])
			return posNoRepetido(v, ini, mitad - 1);// mitad-1 porque ya sabemos que ese elemento tiene pareja
		// si no, podrá ser el propio elemento mitad o uno a su derecha
		else
			return posNoRepetido(v, mitad, fin);
	}
	// si el elemento mitad esta en una posicion impar
	else {
		// si el elemento mitad es igual a su anterior, estará a su derecha
		if (v[mitad] == v[mitad - 1])
			return posNoRepetido(v, mitad + 1, fin); // mitad+1 porque ya sabemos que ese elemento tiene pareja
		// si no, estará a su izquierda
		else
			return posNoRepetido(v, ini, mitad);
	}
}

void resuelveCaso() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int& e : v)
		cin >> e;

	cout << posNoRepetido(v, 0, n) << "\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
#endif

	return 0;
}

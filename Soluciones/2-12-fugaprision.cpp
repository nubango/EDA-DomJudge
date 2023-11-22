// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// Se utilizan letras consecutivas y se conoce la primera y la última letra utilizada (prim y ult)
// Los presos se colocan en línea de manera ordenada y hay que encontrar al preso que falta
// Se utiliza la tecnica de divide y venceras por lo que el coste es
// O(log n) donde n es el numero de elementos del vector sec
char resolver(const vector<char>& sec, int ini, int fin, char prim, char ult) {
	int n = fin - ini;
	// caso base: el vector tiene un solo elemento
	if (n == 1)
		return (sec[ini] == prim) ? sec[ini] + 1 : sec[ini] - 1;

	// caso base especial: el elemento buscado esta en el extremo izquierdo
	if (sec[ini] != prim)
		return prim;

	// caso base especial: el elemento buscado esta en el extremo derecho
	if (sec[fin - 1] != ult)
		return ult;

	int mitad = (ini + fin) / 2;

	// si la letra que esta en la mitad no coincide con el indice que deberia tener mitad, es que esta en la mitad izquierda
	if (sec[mitad] - sec[ini] != mitad - ini)
		return resolver(sec, ini, mitad, prim, sec[mitad - 1]);
	else
		return resolver(sec, mitad, fin, sec[mitad], ult);

}

void resuelveCaso() {
	char prim, ult, n;
	cin >> prim >> ult;
	n = ult - prim;
	vector<char> sec(n);
	for (char& e : sec) cin >> e;
	cout << resolver(sec, 0, n, prim, ult) << '\n';
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
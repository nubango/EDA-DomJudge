// Nuria Bango Iglesias
// VJ07

/*
	-Operacion ⊆ sobre el TAD Set-
 Implementa la relacion de inclusion del TAD Set mediante el metodo bool operator<=(const Set<T>& set) const
 Se valorara la complejidad del algoritmo implementado, la cual debes indicar mediante un comentario justo delante del metodo anadido.

 Instrucciones de entrega:
 Debes subir al juez online los ficheros Set.h, incluyendo las nuevas operaciones, y el Main.cpp (o el nombre que tenga) con la funcion main, etc

 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "Set.h"


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n, e;
	Set<int> set1, set2;

	cin >> n;
	if (!cin) return false;

	for (int i = 0; i < n; i++) {
		cin >> e; set1.add(e);
	}

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> e; set2.add(e);
	}

	cout << (set1 <= set2) << endl;

	return true;

}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	while (resuelveCaso());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

// estructura para el manejo de datos de la solucion de forma mas compacta
struct Solucion {
	int tramosNavegables;
	int caudalTotal;
};

// funcion externa a la clase bintree que explore el arbol calculando el numero de tramos navegables
// O(n) donde n es el numero de nodos del arbol
// el algoritmo pasa por cada nodo máximo dos veces, una a la bajada y otra a la subida -> 2n -> O(n)
// con un arbol equilibrado tendriamos dos llamadas recursivas con tamaño mitad, a=2, b=2 y k=0 en la plantilla de division -> O(n) 
// si el arbol no es equilibrado y estan todos los nodos a un lado entonces tendriamos a=1, b=1 y k=0 en la plantilla por sustracción -> O(n)
Solucion tramosNavegables(const bintree<int>& arbol) {
	if (arbol.empty())
		return { 0,0 };

	if (arbol.left().empty() && arbol.right().empty())
		return { 0,1 };

	Solucion solIz = tramosNavegables(arbol.left());
	Solucion solDr = tramosNavegables(arbol.right());

	if (solIz.caudalTotal >= 3) solIz.tramosNavegables++;
	if (solDr.caudalTotal >= 3) solDr.tramosNavegables++;

	int caudalTramo = solIz.caudalTotal + solDr.caudalTotal - arbol.root();
	if (caudalTramo < 0) caudalTramo = 0;

	return { solIz.tramosNavegables + solDr.tramosNavegables, caudalTramo };
}

void resuelveCaso() {
	bintree<int> arb;
	arb = leerArbol(-1); // -1 es la repr. de arbol vacio

	Solucion sol = tramosNavegables(arb);

	cout << sol.tramosNavegables << "\n";
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


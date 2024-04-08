// Nuria Bango Iglesias
// VJ07

/*
	-Los k numeros menores usando el TAD Set-
 Dada una serie de numeros enteros positivos, queremos encontrar los k elementos distintos menores. En concreto, se pide lo siguiente:

 1. Extiende la clase Set vista en clase (y disponible en el CV) anadiendo los metodos getMax, removeMax, getMin y removeMin,
 que obtienen/borran el maximo y el mınimo elemento del conjunto respectivamente. Indica la complejidad de los metodos implementados
 (como comentario junto a ellos en el codigo).

 2. Escribe una funcion (fuera del TAD) que dada una serie de n numeros enteros (en un array o vector), encuentre los k elementos menores
 distintos, haciendo uso para ello de un conjunto auxiliar. El algoritmo disenado debe ser eficiente y no debe en ningun caso ordenar toda
 la serie (por tanto no puede insertar todos los elementos en el conjunto).

 3. Justifica la complejidad del algoritmo implementado. Se espera que esta dependa tambien de k y no solo de n.

 Instrucciones de entrega:
 Debes subir al juez online los ficheros Set.h, incluyendo las nuevas operaciones, y el Main.cpp (o el nombre que tenga) con la funcion del
 segundo apartado y la funcion main. El corrector automatico del juez solo comprobara la validez de la funcion correspondiente al segundo
 apartado (ver abajo la descripcion de E/S esperadas).

 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#include "Set.h"

// O(n log k) donde n es el tamano del vector y k el tamano del set o numero de elementos que se piden
void kMenoresElementos(int k, const vector<int>& v) {
	Set<int> set;
	set.add(v[0]);

	// O(n), n es el tamano del vector
	for (int i = 1; i < v.size(); i++)
	{
		// si hay hueco se anade el elemento
		if (set.size() + 1 <= k)
			set.add(v[i]);
		// si el set ya tiene K elementos
		else
		{
			// si el elemento es menor que el mayor (y distinto del menor ya incluido) 
			// o es menor que el menor actual, es un numero util
			if (v[i] < set.getMax() && v[i] != set.getMin() || v[i] < set.getMin()) {
				// se le hace hueco y se añade
				// O(log k) donde k es el numero de elementos del set
				set.removeMax();
				set.add(v[i]);
			}
		}
	}

	// O(k), k es el tamano del set
	for (int i = 0; i < set.size(); i++)
	{
		cout << *(set.toArray() + i) << " ";
	}
}

bool resuelveCaso() {
	int K;
	cin >> K;

	if (K == 0)
		return false;

	int n;
	vector<int> v;
	cin >> n;
	while (n != -1) {
		v.push_back(n);
		cin >> n;
	}

	kMenoresElementos(K, v);
	cout << "\n";

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
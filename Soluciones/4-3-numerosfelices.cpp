// Nuria Bango Iglesias
// VJ07

/*
	-Numeros felices-
 Decimos que un numero entero es feliz si al aplicar repetidamente el proceso de sumar los cuadrados de sus dıgitos se termina llegando al
 numero 1. En caso contrario (se entra en un ciclo que no incluye el 1), se dice que el numero es infeliz. Por ejemplo:
 • el 7 es feliz: 7 → 49 → 97 → 130 → 10 → 1
 • el 38 es infeliz: 38 → 73 → 58 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58
 Se pide escribir una funcion esFeliz que determine si un numero dado n (0 <= n < 1000) es o no feliz.
 La funcion debe utilizar un conjunto (clase Set disponible en el CV o clase set de la STL de C++) como estructura auxiliar.
 Se recomienda probar distintas alternativas.
 Justifica tambien (mediante un comentario delante de la funcion) la complejidad en tiempo y en espacio del algoritmo implementado.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
using namespace std;

// El coste en espacio adicional es dependiente del tamano del set
// El coste en tiempo es O(n log n) donde n es el tamano del set
bool esFeliz(int n) {
	set<int> s;

	cout << n << " ";
	// insert tiene coste O(log n) en el caso medio
	s.insert(n);

	while (n != 1) {
		int aux, step = 0;

		while (n != 0) {
			aux = n % 10;
			step = step + aux * aux;
			n /= 10;
		}

		n = step;
		cout << step << " ";

		// find devuelve end si no encuentra el elemento
		// find tiene coste O(log n) donde n es el num de elementos del set
		if (s.find(step) != s.end())
			return false;

		s.insert(step);
	}

	return true;
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (!cin)
		return false;

	cout << (esFeliz(n) ? "1\n" : "0\n");

	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso());


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
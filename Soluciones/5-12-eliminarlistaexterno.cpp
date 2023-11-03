// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;

// funcion externa al TAD List que elimina todas las apariciones de un elemento 'elem'
// no crea memoria (llamando a push_back ni push_front)
// O(n) donde n=l.size() ya que recorre una unica vez la lista con iteradores
void eliminaElemento(list<int>& l, int elem) {
	list<int>::iterator it = l.begin();

	while (it != l.end()) {
		// (*it) -> el elemento apuntado por it
		// erase devuelve el iterador tras eliminar el elemento apuntado por el iterador pasado por argumento
		if ((*it) == elem)
			it = l.erase(it);
		else
			++it;
	}
}

void resuelveCaso() {

	int n;
	cin >> n;

	list<int> l;
	while (n != -1) {
		l.push_back(n);
		cin >> n;
	}

	cin >> n;

	for (int e : l) {
		cout << e << " ";
	}
	cout << '\n';

	eliminaElemento(l, n);

	// Le damos una vuelta para comprobar que la lista está bien formada
	for (int i = 0; i < l.size(); ++i) {
		n = l.back();
		l.pop_back();
		l.push_front(n);
	}

	// Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
	while (!l.empty()) {
		std::cout << l.front() << " ";
		l.pop_front();
	}

	std::cout << "\n";
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

// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;

template <class T>
class list_plus : public list<T> {
	using Nodo = typename list<T>::Nodo;

public:
	// adelanta un numero de posiciones newPos, un segmento de longitud length que se encuentra en la posicion pos
	// se trabaja con punteros a nodos para no crear ni destruir memoria, ni usar estructuras auxiliares
	// ademas solo se recorre la lista para colocar los punteros en sus posiciones correspondientes por lo que
	// tiene coste O(n) donde n es el numero de elementos de la lista (nelems)
	void adelantar(int pos, int length, int newPos) {
		// si la lista es vacia
		// si la posicion de origen o destino del segmento no es valida
		// o si lon = 0 o k = 0
		if (this->empty() || pos >= this->nelems || pos == 0 || newPos > pos || newPos == 0 || length == 0)
			return;

		// si el segmento se sale de la lista, es decir, si pos + lon > n se tomara el segmento de los ultimos n − pos elementos
		if (pos + length > this->nelems)
			length = this->nelems - pos;

		// encontrar los nodos de inicio del segmento y de la nueva posición
		Nodo* iniSegmento = this->fantasma->sig;
		Nodo* nuevaPos = this->fantasma->sig;

		for (int i = 0; i < pos; i++)
			iniSegmento = iniSegmento->sig;

		for (int i = 0; i < pos - newPos; i++)
			nuevaPos = nuevaPos->sig;

		// el final del segmento se calcula a partir del inicio
		Nodo* finSegmento = iniSegmento;
		for (int i = 1; i < length; i++)
			finSegmento = finSegmento->sig;

		// conectar los nodos antes y despues del segmento
		iniSegmento->ant->sig = finSegmento->sig;
		finSegmento->sig->ant = iniSegmento->ant;

		// insertar el segmento en la nueva posición
		iniSegmento->ant = nuevaPos->ant;
		nuevaPos->ant->sig = iniSegmento;
		nuevaPos->ant = finSegmento;
		finSegmento->sig = nuevaPos;
	}
};

void resuelveCaso() {
	char e;
	int n, pos, length, dif;
	list_plus<char> l;

	// leer los datos de la entrada
	cin >> n >> pos >> length >> dif;
	for (int i = 1; i <= n; ++i) {
		cin >> e;
		l.push_back(e);
	}

	l.adelantar(pos, length, dif);

	// Le damos una vuelta para comprobar que la lista está bien formada
	for (int i = 0; i < l.size(); ++i) {
		e = l.back();
		l.pop_back();
		l.push_front(e);
	}

	// Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
	while (!l.empty()) {
		cout << l.front() << " ";
		l.pop_front();
	}
	cout << endl;
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

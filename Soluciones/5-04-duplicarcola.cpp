// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;


template <class T>
class queue_plus : public queue<T> {
	using Nodo = typename queue<T>::Nodo;
	// Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult
public:
	// Duplica todos los elementos de la cola sin destruir memoria
	// Crea nodos nuevos y modifica los enlaces entre ellos
	// O(n) donde n=nelems*2
	void duplica() {
		if (this->nelems == 0)
			return;

		Nodo* act = this->prim; // indice que apunta al nodo actual
		Nodo* dup = nullptr;
		while (act != nullptr) {
			dup = new Nodo(act->elem, act->sig); // el elemento duplicado apunta al mismo sig que apuntaba el original y tambien tiene el mismo elem
			this->nelems++; // un elemento mas
			act->sig = dup; // cambiamos el sig del elemento a copiar a su duplicado
			act = dup->sig; // el indice avanza dos elementos, porque ahora apunta al siguiente del duplicado
		}
		this->ult = dup; // se actualiza el nodo ult, que ahora sera el ultimo nodo dup creado
	}
};


bool resuelveCaso() {
	int n;
	queue_plus<int> q;
	cin >> n;
	if (!cin) return false;
	while (n != 0) {
		q.push(n);
		cin >> n;
	}

	q.duplica();

	// escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
	for (int i = 0; i < q.size(); ++i) {
		n = q.front();
		q.pop();
		q.push(n);
	}
	// ahora imprimimos la cola y de paso la dejamos vacía
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}

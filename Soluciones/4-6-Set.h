//  Implementación del TAD Set con array dinámico ordenado y sin repeticiones

#ifndef SET_H
#define SET_H

#include <utility>    // std::move

template <class T>
class Set {
protected:
	static const int TAM_INICIAL = 10; // tamaño inicial del array dinámico

	// número de elementos del array
	int nelems;

	// tamaño del array
	int capacidad;

	// puntero al array que contiene los elementos ordenados (redimensionable)
	T* array;

public:

	// constructor: conjunto vacío
	Set() : nelems(0), capacidad(TAM_INICIAL), array(new T[capacidad]) {}

	// destructor
	~Set() {
		libera();
	}

	// constructor por copia
	Set(Set<T> const& other) {
		copia(other);
	}

	// operador de asignación
	Set<T>& operator=(Set<T> const& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	// Añadir un elemento
	void add(T const& elem) {
		bool found;
		int pos;
		binSearch(elem, found, pos);
		if (!found) {
			shiftRightFrom(pos + 1);
			array[pos + 1] = elem;
			++nelems;
			if (nelems == capacidad)
				amplia();
		}
	}

	void remove(T const& elem) {
		bool found;
		int pos;
		binSearch(elem, found, pos);
		if (found) {
			shiftLeftFrom(pos);
			--nelems;
		}
	}

	bool contains(T const& x) const {
		bool found;
		int pos;
		binSearch(x, found, pos);
		return found;
	}

	// consultar si el conjunto está vacío
	bool empty() const {
		return nelems == 0;
	}

	// consultar el tamaño del array (que no tiene por que ser el tamaño del conjunto en realidad!)
	int size() const {
		return nelems;
	}

	// Devuelve el puntero del array para poder consultar desde fuera su contenido (por ej. para imprimirlo)
	const T* toArray() const {
		return array;
	}

	// Operador contenido set1 ⊆ set2
	// O(n), donde n es nelems
	bool operator<=(const Set<T>& set) const {
		// el conjunto vacio esta contenido en todos los conjuntos
		if (empty())
			return true;

		int i = 0;
		int j = 0;
		while (i < nelems && j < set.nelems)
		{
			// if (!set.contains(array[i]) // DEPRECATED: O(log n) donde n es nelems, porque contains utiliza busqueda binaria	

			// Si mi elemento es mayor que el de other puedo buscar en el other+1
			// Se aumenta el indice que recorre other (j)
			if (array[i] > set.array[j])
				j++;
			// Si son iguales se aumentan los dos indices
			else if (array[i] == set.array[j]) {
				i++;
				j++;
			}
			// Si es menor o distinto no se encontrara en el set a partir de ahi
			else // if (array[i] != set.array[j])
				return false;
		} // fin while
		// Si se termina de recorer other, pero no this es que no esta contenido
		if (j >= set.nelems && i < nelems)
			return false;

		// Si se termina de recorrer esta contenido
		return true;
	}

protected:

	void libera() {
		delete[] array;
	}

	// this está sin inicializar
	void copia(Set const& other) {
		capacidad = other.nelems + TAM_INICIAL;
		nelems = other.nelems;
		array = new T[capacidad];
		for (int i = 0; i < nelems; ++i)
			array[i] = other.array[i];
	}

	void amplia() {
		T* viejo = array;
		capacidad *= 2;
		array = new T[capacidad];
		for (int i = 0; i < nelems; ++i)
			array[i] = std::move(viejo[i]);
		delete[] viejo;
	}

	void binSearch(const T& x, bool& found, int& pos) const {
		// Pre: los size primeros elementos de array están ordenados
		//      size >= 0

		pos = binSearchAux(x, 0, nelems - 1);
		found = (pos >= 0) && (pos < nelems) && (array[pos] == x);

		// Post : devuelve el mayor índice i (0 <= i <= nelems-1) que cumple
		//        array[i] <= x
		//        si x es menor que todos los elementos de array, devuelve -1
		//        found es true si x esta en array[0..nelems-1]
	}

	int binSearchAux(const T& x, int a, int b) const {
		// Pre: array está ordenado entre 0 .. nelems-1
		//      ( 0 <= a <= nelems ) && ( -1 <= b <= nelems ) && ( a <= b+1 )
		//      todos los elementos a la izquierda de 'a' son <= x
		//      todos los elementos a la derecha de 'b' son > x

		int p, m;

		if (a == b + 1)
			p = a - 1;
		else if (a <= b) {
			m = (a + b) / 2;
			if (array[m] <= x)
				p = binSearchAux(x, m + 1, b);
			else
				p = binSearchAux(x, a, m - 1);
		}
		return p;

		// Post: devuelve el mayor índice i (0 <= i <= nelems-1) que cumple
		//       array[i] <= x
		//       si x es menor que todos los elementos de array, devuelve -1
	}

	void shiftRightFrom(int i) {
		for (int j = nelems; j > i; j--)
			array[j] = array[j - 1];
	}

	void shiftLeftFrom(int i) {
		for (; i < nelems - 1; i++)
			array[i] = array[i + 1];
	}

};

#endif //SET_H

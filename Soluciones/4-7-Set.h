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

	// Obtiene el maximo elemento del conjunto
	// Tiene cose lineal O(1) ya que la unica operacion es de acceso a una posicion del array
	int getMax() const {
		return array[nelems - 1];
	}

	// Borra el maximo elemento del conjunto
	// Tiene coste O(log n) donde n es el numerp de elementos del conjunto
	// El coste es debido a la busqueda binaria que se realiza en remove
	void removeMax() {
		remove(getMax());
	}

	// Obtiene el minimo elemento del conjunto
	// Tiene cose lineal O(1) ya que la unica operacion es de acceso a una posicion del array
	int getMin() const {
		return array[0];
	}

	// Borra el minimo elemento del conjunto
		// Tiene coste O(log n) donde n es el numerp de elementos del conjunto
	// El coste es debido a la busqueda binaria que se realiza en remove
	void removeMin() {
		remove(getMin());
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

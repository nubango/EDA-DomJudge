// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
using namespace std;

// clave: palabra, valor: lista con lineas en las que aparece
// el map es ordenado por clave porque la salida se pide en orden alfabetico
using TablaRefs = map<string, list<int>>;

void referencias(int numLineas, TablaRefs& refs) {
	string palabra;
	char c;
	for (int numLinea = 1; numLinea <= numLineas; numLinea++) {
		cin.get(c);
		while (c != '\n') {
			cin.unget(); // Se vuelve a dejar c en cin (por si era la 1ª letra de la linea)
			cin >> palabra;

			// solo tiene en cuenta las palabras de mas de dos caracteres
			if (palabra.size() > 2) {

				// convierte la palabra a minusculas
				for (auto& c : palabra)
					c = tolower(c);

				// si es la primera vez que se va a insertar la palabra
				if (!refs.count(palabra)) {
					list<int> l;
					l.push_back(numLinea);
					refs.insert({ palabra, l });
				}
				else // si ya esta la palabra en el diccionario
				{
					// hay que comprobar si es la primera aparicion de esa palabra en la linea
					if (refs[palabra].back() != numLinea)
						refs[palabra].push_back(numLinea);
				}
			}
			cin.get(c);
		}
	}
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	char c;
	cin >> n;
	cin.get(c); // Me salto el \n de detrás del N
	if (n == 0)
		return false;

	TablaRefs refs;
	referencias(n, refs);

	// par: <string, int>
	for (auto par : refs) {
		cout << par.first << " ";

		for (auto l : par.second)
			cout << l << " ";

		cout << "\n";
	}

	cout << "---\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso())
		;

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}
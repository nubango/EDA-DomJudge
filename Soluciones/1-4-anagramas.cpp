// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// se han de recorrer los dos strings completos
// y en el caso peor se recorrer los dos vectores a la vez de tamaño 25 aux1 y aux2
// O(n+m+25), siendo n cad1.size, m cad2.size y 25 el tam del vector aux
// como cad1 y cad2 tienen el mismo tam pude quedar como
// O(n), donde n es el tam de las cadenas
bool anagramas(const string& cad1, const string& cad2) {
	// si las cadenas no tienen el mismo tam no pueden ser anagramas
	if (cad1.size() != cad2.size())
		return false;

	vector<int> aux1(25, 0); // hay 25 letras ('a'->'z')
	vector<int> aux2(25, 0); // hay 25 letras ('a'->'z')

	// la letra cad1[i] equivale en el vector aux1 a su valor char menos el de la primera letra 'a'
	// asi el primer valor del vector es 'a' y el ultimo 'z' (0, 24)
	// vamos sumando las apariciones de todas las letras de la cadena cad1 a nuestro vector abecedario
	for (int i = 0; i < cad1.size(); i++)
		aux1[cad1[i] - 'a']++;

	// hacemos lo mismo con la cadena2 y su vector abecedario aux2
	for (int i = 0; i < cad2.size(); i++)
		aux2[cad2[i] - 'a']++;

	// se han de comparar los dos vectores abecedario para comprobar que se usan las mismas letras y el mismo numero de letras
	int i = 0;
	bool iguales = true;
	while (i < aux1.size() && iguales) {
		if (aux1[i] != aux2[i])
			iguales = false;
		i++;
	}

	return iguales;
}

void resuelveCaso() {
	string word1, word2;
	cin >> word1 >> word2;
	cout << (anagramas(word1, word2) ? "SI\n" : "NO\n");
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
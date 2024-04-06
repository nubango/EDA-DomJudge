// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <deque>
using namespace std;

bool esConsonante(char letra) {
	letra = tolower(letra);
	string vocales = "aeiou";
	for (char c : vocales) {
		if (letra == c)
			return false;
	}
}

string decodifica(deque<char>& q) {
	string decodificado = "";

	while (q.size() > 1) {
		if (esConsonante(q.front()) && esConsonante(q.back())) {
			decodificado.push_back(q.back());
			decodificado.push_back(q.front());
			q.pop_back(); q.pop_front();
		}
		else
		{
			decodificado.push_back(q.front());
			decodificado.push_back(q.back());
			q.pop_front(); q.pop_back();
		}
	}
	if (!q.empty()) {
		decodificado.push_back(q.front());
		q.pop_front();
	}

	return decodificado;
}

bool resuelveCaso() {
	string line;
	getline(cin, line);

	if (!cin)
		return false;

	deque<char> q;

	for (char c : line)
		q.push_back(c);

	cout << decodifica(q) << "\n";

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

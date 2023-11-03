// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>
using namespace std;


// O(n) donde n es la longitud del string line
// el uso de la pila es exclusivamente para los parentesis mencionados en el enunciado
// todos se meten en la pila excepto si es un parentesis de cerrar que comprueba si 
// en la cima esta su pareja para directamente sacarla
// si tras recorrer toda la linea, la pila esta vacia, los parentesis estan equilibrados
// si aun quedan elementos en la pila, es que hay parentesis sin pareja
bool equilibrados(string& line) {
	stack<char> pila;

	for (char c : line) {
		if (c == '(' || c == '[' || c == '{')
			pila.push(c);
		else if (c == ')')
		{
			if (!pila.empty() && pila.top() == '(')
				pila.pop();
			else
				pila.push(c);
		}
		else if (c == ']')
		{
			if (!pila.empty() && pila.top() == '[')
				pila.pop();
			else
				pila.push(c);
		}
		else if (c == '}')
		{
			if (!pila.empty() && pila.top() == '{')
				pila.pop();
			else
				pila.push(c);
		}
	}

	return pila.empty();
}

bool resuelveCaso() {
	string line;
	getline(cin, line);

	if (!cin)
		return false;

	equilibrados(line) ? cout << "SI\n" : cout << "NO\n";

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

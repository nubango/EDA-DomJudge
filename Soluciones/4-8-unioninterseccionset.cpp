// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"

using namespace std;

bool resuelveCaso() {
	int n, e;
	Set<int> set1, set2;



	cin >> n;
	if (!cin)
		return false;

	for (int i = 0; i < n; i++) {
		cin >> e;
		set1.add(e);
	}

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> e;
		set2.add(e);
	}

	cout << (set1 || set2) << '\n' << (set1 && set2) << '\n';

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
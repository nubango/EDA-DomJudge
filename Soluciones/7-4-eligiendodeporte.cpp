// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <fstream>
#include <cctype>
#include <map>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

// clave: nombre del deporte, valor: numero de alumnos apuntados al deporte
// es una map ordenado porque la salida se pide por orden de demanda
using DeportesMap = map<string, int>;

struct infoAlumno {
	string primerDeporte = ""; // primer deporte al que se ha apuntado
	bool esValido = true; // true: solo se ha apuntado a un deporte
};
// clave: nombre de alumno, valor: infoAlumno
using AlumnosMap = unordered_map<string, infoAlumno>;

void resolver(string const& primerDeporte, DeportesMap& deportes, AlumnosMap& alumnos) {
	string deporte, alumno;
	deporte = primerDeporte;
	while (deporte != "_FIN_") {
		deportes.insert({ deporte, 0 });
		cin >> alumno;
		// si esta en mayusculas no es un deporte, es un alumno
		while (!isupper(alumno[0]) && alumno != "_FIN_") {
			if (!alumnos.count(alumno)) {
				alumnos.insert({ alumno, {deporte, true} });
				deportes[deporte]++;
			}
			else {
				auto& refAlumno = alumnos[alumno];

				if (refAlumno.esValido && refAlumno.primerDeporte != deporte) {
					refAlumno.esValido = false;
					deportes[refAlumno.primerDeporte]--;
				}
			}
			cin >> alumno;
		}
		deporte = alumno;
	}
}

bool myfunction(const pair<string, int>& d1, const pair<string, int>& d2) {
	if (d1.second == d2.second)
		return d1.first < d2.first;

	return d1.second > d2.second;
}

bool resuelveCaso() {
	string primerDeporte;
	cin >> primerDeporte;
	if (!cin)
		return false;

	DeportesMap deportes;
	AlumnosMap alumnos;
	resolver(primerDeporte, deportes, alumnos);

	vector<pair<string, int>> solucion;
	for (auto par : deportes)
		solucion.push_back(par);

	sort(solucion.begin(), solucion.end(), myfunction);

	for (auto par : solucion)
		cout << par.first << " " << par.second << "\n";

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
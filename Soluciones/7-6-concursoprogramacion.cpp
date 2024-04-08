// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

using Equipo = string;
using Problema = string;

struct DatosSolucion {
	string nombreEquipo;
	int numCorrectos;
	int tiempoTotal;
};
using Solucion = vector<DatosSolucion>;

//-------------------------------------------

struct DatosProblema {
	bool correct = false; // true cuando este correcto el problema
	int numIntentos = 0; // numero de intentos incorrectos antes del primer correct
};

struct InfoEquipo {
	unordered_map<Problema, DatosProblema> problemas;
	int tiempoTotal = 0; // tiempo total de todos los problemas correctos del equipo (incluidas sanciones)
	int numCorrectos = 0;
};

//-------------------------------------------

void procesaEnvios(Solucion& resultados) {
	string equipo, problema, veredicto;
	int minuto;

	unordered_map<Equipo, InfoEquipo> equipos; // ESTRUCTURA PRINCIPAL: unordered_map (operaciones con coste O(1))

	cin >> equipo;
	// O(E) siendo E el numero de envios
	while (equipo != "FIN") {
		cin >> problema >> minuto >> veredicto;

		// si es la primera vez que lo añadimos nos devolvera la posicion en la que se añade
		// si ya esta añadido nos devuelve la posicion en la que esta
		auto& refEquipo = equipos[equipo]; // O(1)
		auto& refProblema = refEquipo.problemas[problema]; // O(1)

		// no se tienen en cuenta envios despues del primer correct
		if (!refProblema.correct) {
			// si el veredicto es correcto
			if (veredicto == "AC") {
				refProblema.correct = true; // se marca como correcto el problema
				refEquipo.numCorrectos++; // se actualiza el numero total de problemas correctos
				refEquipo.tiempoTotal += (refProblema.numIntentos * 20) + minuto; // se añade el minuto en el que se consigue correct al problema mas la penalizacion al tiempo total
			}
			// si es incorrecto se suma un intento incorrecto a ese problema
			else
				refProblema.numIntentos++;
		}
		cin >> equipo;
	}

	// una vez que ya esta rellenada la estructura con la informacion
	// se recorre para volcar la solucion a la estrcutura resultados
	// O(n) donde n es el numero de equipos distintos
	for (auto equipo : equipos)
		resultados.push_back({ equipo.first, equipo.second.numCorrectos , equipo.second.tiempoTotal });
}

// El criterio principal para ordenar a los equipos es el numero de problemas resueltos
// Cuantos mas problemas se resuelvan, mejor sera el puesto en la clasificacion
// A igualdad de problemas resueltos, los equipos que hayan tardado menos tiempo se clasifican primero
// Si dos equipos resuelven el mismo n´umero de problemas en el mismo tiempo, seran ordenados por su nombre de menor a mayor.
bool myFunction(const DatosSolucion& datos1, const DatosSolucion& datos2) {
	if (datos1.numCorrectos == datos2.numCorrectos) {
		if (datos1.tiempoTotal == datos2.tiempoTotal)
			return datos1.nombreEquipo < datos2.nombreEquipo;
		else
			return datos1.tiempoTotal < datos2.tiempoTotal;
	}
	else
		return datos1.numCorrectos > datos2.numCorrectos;
}

// O(E + T log T) siendo E el numero de envios y T el numero de equipos
// En el caso de que haya muchos envios, O(E)
// Si el numero de equipos es pequeño en comparacion al numero de envios, que seria lo normal en este problema: O(n log n)
void resuelveCaso() {
	Solucion resultados;
	procesaEnvios(resultados);

	// O(n log n) siendo n el numero de elementos de resultados que es el numero de equipos distintos
	sort(resultados.begin(), resultados.end(), myFunction);

	for (auto r : resultados)
		std::cout << r.nombreEquipo << " " << r.numCorrectos << " " << r.tiempoTotal << "\n";

	std::cout << "---\n";
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
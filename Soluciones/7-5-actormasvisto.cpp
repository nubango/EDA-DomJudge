// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

using Pelicula = string;
using Actor = string;

// clave: nombre del actor, valor: minutos en pantalla del actor en esa pelicula
using Reparto = unordered_map<Actor, int>;

// estructura principal: clave: nombre del actor, valor: informacion de los actores de esa pelicula
using RepartosPeliculas = unordered_map<Pelicula, Reparto>;

// almacena toda la informacion de los repartos de todas las peliculas en el segundo parametro
// O(n*m) siendo n el numero de peliculas y m el numero de actores
void leerRepartos(int numPeliculas, RepartosPeliculas& peliculas) {
	Pelicula peli; int numActores;
	Actor actor; int minutos;
	for (int i = 0; i < numPeliculas; ++i) {
		cin >> peli; cin >> numActores;
		peliculas.insert({ peli, {} }); // insercion de una nueva pelicula con reparto vacio
		for (int j = 0; j < numActores; ++j) {
			cin >> actor >> minutos;
			peliculas[peli].insert({ actor,minutos }); // insercion del actor con sus minutos en la pelicula correspondiente
		}
	}
}

// calcula la informacion solicitada a partir de los repartos de las peliculas y la secuencia de emisiones
// O(m*e) donde m es el numero de actores y e el numero de emisiones
void procesarEmisiones(RepartosPeliculas const& repartos, vector<string> const& secEmisiones) {
	// clave: nombre de la pelicula, valor: numero de veces emitida
	unordered_map<Pelicula, int> peliculasEmitidas;
	int maxEmisiones = 0; // numero de veces que se emite la peli mas emitida
	string peliculaTop = ""; // nombre de la pelicula mas vista

	// clave: nombre del actor, valor: minutos totales en television
	// ordered map porque se piden ls nombres de los actores en orden alfabetico
	map<Actor, int> minutosActores;
	int maxMinutos = 0; // maximo de minutos que aparece un actor

	// se recorre la secuencia de emisiones
	for (const auto& itPelicula : secEmisiones) {
		// si no existe se crea, si ya existe le suma uno a su valor de emisiones
		peliculasEmitidas[itPelicula]++;
		auto& refEmision = peliculasEmitidas[itPelicula];

		// se actualiza la pelicula con mas emisiones (sera la ultima emitida si dos tienen el mismo num)
		if (refEmision >= maxEmisiones) {
			maxEmisiones = refEmision;
			peliculaTop = itPelicula;
		}

		// se rellena la estructura minutosActores
		auto itReparto = repartos.find(itPelicula);
		if (itReparto != repartos.end()) {
			for (const auto& actorMinutos : itReparto->second) {
				minutosActores[actorMinutos.first] += actorMinutos.second; // suma los minutos de cada actor al total
				maxMinutos = max(maxMinutos, minutosActores[actorMinutos.first]); // actualiza el maximo de minutos de un actor en pantalla
			}
		}
	}

	// SALIDA: numero de veces maximo que se emite una pelicula y el nombre de la misma (la ultima emitida en caso de empate)
	cout << maxEmisiones << " " << peliculaTop << "\n";

	// SALIDA: numero maximo de minutos que aparece un actor en pantalla durante todas las emisiones
	cout << maxMinutos << " ";

	// SALIDA: nombre de todos los actores que aparecen maxMinutos en pantalla por orden alfabetico porque es un map
	for (const auto& actorMinutos : minutosActores) {
		if (actorMinutos.second == maxMinutos)
			cout << actorMinutos.first << " ";
	}

	cout << "\n";
}

// O(P * A + E * A + A * log A) siendo P el numero de Peliculas, A el numero de Actores y E el numero de emisiones
bool resuelveCaso() {
	int numPelis, numEmisiones;
	cin >> numPelis;
	if (numPelis == 0)
		return false;

	// Lectura de los repartos de las peliculas
	RepartosPeliculas repartos;
	leerRepartos(numPelis, repartos);

	// Lectura de la secuencia de peliculas emitidas en vector<string>
	cin >> numEmisiones;
	vector<string> secEmisiones(numEmisiones);
	for (string& s : secEmisiones) cin >> s;

	procesarEmisiones(repartos, secEmisiones);

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
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

using Estado = string;
using Partido = string;

struct infoEstado {
	int nCompromisarios = 0; // numero de compromisarios
	Partido ganador = "NULL"; // partido mas votado del Estado
	// clave: nombre del partido, valor: numero de votos
	unordered_map<Partido, int> partidos; // mapa no ordenado del listado de partidos con sus votos
};

class ConteoVotos {
private:
	// clave: nombre del estado, valor: informacion del estado
	unordered_map<Estado, infoEstado> estados; // mapa no ordenado del listado de estados del pais -> ESTRUCTURA PRINCIPAL
	// clave: nombre del partido, valor: numero de compromisarios de ese partido
	map<Partido, int> compromisariosXpartido; // mapa ordenado del recuento total de compromisarios de cada partido -> ESTRUCTURA SOLUCION
public:

	// registra un nuevo estado en el sistema, con el nombre y el numero de compromisarios pasados por parametro
	// si ya existia ese nombre se lanza una excepcion
	// se puede suponer que numCompromisarios > 0
	void nuevo_estado(const Estado& nombre, int numCompromisarios) {
		if (estados.find(nombre) == estados.end()) // O(E) donde E es el numero de Estados
			estados[nombre].nCompromisarios = numCompromisarios; // O(E) donde E es el numero de Estados
		else
			throw std::domain_error("Estado ya existente");
	}

	// suma numVotos a la cantidad de votos del partido pasado por parametro del "estado"
	// si el estado no estaba registrado, se lanza una excepcion
	// se puede suponer que numVotos > 0
	// O(E * P * log P) donde E es el numero de Estados y P el numero de Partidos
	void sumar_votos(const Estado& estado, const Partido& partido, int numVotos) {
		auto itEstado = estados.find(estado); // O(E) donde E es el numero de Estados
		if (itEstado == estados.end()) // O(1)
			throw std::domain_error("Estado no encontrado");
		else {
			// IMPORTANTE: Por referencia para que los cambios se mantengan 
			auto& itPartido = itEstado->second.partidos[partido]; // O(P) donde P es el numero de Partidos en un Estado
			itPartido += numVotos;
			if (itEstado->second.ganador == "NULL") {
				itEstado->second.ganador = partido;
				compromisariosXpartido[partido] += itEstado->second.nCompromisarios; // O(log P) donde P es el numero de Partidos
			}
			// su el partido actual es distinto del ganador de ese estado Y es ganador porque tiene mas votos que el actual ganador
			else if (itEstado->second.ganador != partido && itPartido > itEstado->second.partidos[itEstado->second.ganador]) {
				// actualizamos la estructura de compXpart restando los compromisarios de este estado del partido
				compromisariosXpartido[itEstado->second.ganador] -= itEstado->second.nCompromisarios; // O(log P) donde P es el numero de Partidos
				// en caso de que al restar se queden sin compromisarios entre todos los estados, se elimina de la estructura
				if (compromisariosXpartido[itEstado->second.ganador] <= 0) // O(log P) donde P es el numero de Partidos
					compromisariosXpartido.erase(itEstado->second.ganador); // O(log P) donde P es el numero de Partidos
				// se actualiza, ahora si, el partido ganador de este estado
				itEstado->second.ganador = partido;
				// y se suman los compromisarios a la estructura compXpart
				compromisariosXpartido[partido] += itEstado->second.nCompromisarios; // O(log P) donde P es el numero de Partidos
			}
		}
	}

	// devuelve el nombre del partido que mas votos ha obtenido en el estado indicado
	// se puede suponer que algun partido tiene al menos un voto y 
	// que el partido mas votado tiene un numero de votos estrictamente mayor al del resto (no hay empates)
	// si el estado no estaba registrado, se lanza una excepcion
	Partido ganador_en(const Estado& estado) const {
		auto itEstado = estados.find(estado); // O(E) donde E es el numero de Estados
		if (itEstado == estados.end())
			throw std::domain_error("Estado no encontrado");
		else
			return itEstado->second.ganador;
	}

	// devuelve una lista de los partidos que han obtenido al menos un compromiso en alguno de los estados
	// cada elemento de la lista es un par {nombre, numCompromisarios}
	// la lista debe estar ordenada alfabeticamente por nombre del partido
	// se puede suponer que todos los estados registrados tienen un partido ganador (no hay empates)
	vector<pair<Partido, int>> resultados() const {
		vector<pair<Partido, int>> solucion;

		// recorre la estructura compromXpartido ya creada y rellena, metiendo los pares de elementos en el vector salida
		for (auto& itSol : compromisariosXpartido) // O(P) donde P es el numero de Partidos
			solucion.push_back({ itSol.first, itSol.second });

		return solucion;
	}
};

// O(max(N, E * P * log P)) donde N es el numero de envios, E el numero de Estados, P el numero de Partidos
bool resuelveCaso() {
	string comando;
	cin >> comando;
	if (!cin) return false;

	ConteoVotos elecciones;

	while (comando != "FIN") {
		try {
			if (comando == "nuevo_estado") {
				Estado estado;
				int num_compromisarios;
				cin >> estado >> num_compromisarios;
				elecciones.nuevo_estado(estado, num_compromisarios);
			}
			else if (comando == "sumar_votos") {
				Estado estado;
				Partido partido;
				int num_votos;
				cin >> estado >> partido >> num_votos;
				elecciones.sumar_votos(estado, partido, num_votos);
			}
			else if (comando == "ganador_en") {
				Estado estado;
				cin >> estado;
				Partido ganador = elecciones.ganador_en(estado);
				cout << "Ganador en " << estado << ": " << ganador << "\n";
			}
			else if (comando == "resultados") {
				for (const auto& par : elecciones.resultados()) {
					cout << par.first << " " << par.second << "\n";
				}
			}
		}
		catch (std::exception& e) {
			cout << e.what() << "\n";
		}
		cin >> comando;
	}

	cout << "---\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}

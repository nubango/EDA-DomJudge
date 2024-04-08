/*
Nombre completo: Nuria Bango Iglesias
Usuario del juez: VJ05

Todas las operaciones internas estan hechas, me queda la duda de qué pasa si hay un villano y un heroe que se llaman igual, que dara error, ya que las comprobaciones en los
ataques con la cola de turnos solo se hacen respecto al nombre (se podria añadir un campo de villano/heroe para solucionarlo)

Por falta de tiempo para depuracion, el programa da error de ejecucion que no he depurado pero supongo que tiene que ver con la lista de turnos ya que es lo ultimo
que he añadido en las operacioens y como se eliminan los elementos de ella
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

using Heroe = string;
using Villano = string;

class SistemaBatallas {
private:

	struct infoVillano {
		int vida = 0;
		int damg = 0;
		list<pair<string, int>>::iterator it; // puntero a la lista de turnos
	};

	unordered_map<Villano, infoVillano> villanos; // mapa no ordenado con la informacion de todos los villanos

	struct infoHeroe {
		int vida = 0;
		// <nombre ataque, daño ataque>
		map<string, int> ataques; // mapa ordenado para que mostrar_ataques no tenga que hacer sort cada vez que es llamado
		list<pair<string, int>>::iterator it; // puntero a la lista de turnos
	};

	unordered_map<Heroe, infoHeroe> heroes; // mapa no ordenado con la informacion de todos los heroes

	list<pair<string, int>> turnos; // cola para saber el orden de los turnos

public:

	// Coste: O(1) 
	void aparece_villano(Villano const& v, int puntos, int valor) {

		if (villanos.find(v) != villanos.end())
			throw invalid_argument("Personaje ya existente");
		else
		{
			turnos.push_back({ v, puntos }); // se añade su turno a la cola
			villanos[v].vida = puntos;
			villanos[v].damg = valor;
			villanos[v].it = --turnos.end();
		}
	}

	// Coste: O(1)
	void aparece_heroe(Heroe const& h, int puntos) {
		if (heroes.find(h) != heroes.end())
			throw invalid_argument("Personaje ya existente");
		else
		{
			turnos.push_back({ h, puntos }); // se añade su turno a la cola
			heroes[h].vida = puntos; // el operador [] inserta si no existe
			heroes[h].it = --turnos.end();
		}
	}

	// Coste: O(log n) pirque se hace una busqueda con find en un map
	void aprende_ataque(Heroe const& h, string const& ataque, int valor) {
		if (heroes.find(h) == heroes.end()) // O(1)
			throw invalid_argument("Heroe inexistente");

		auto& atqH = heroes[h].ataques; // mapa ordenado de ataques del heroe
		if (atqH.find(ataque) != atqH.end()) // log(n)
			throw invalid_argument("Ataque repetido");


		atqH[ataque] = valor;
	}

	// Coste: O(n) donde n es el numero de ataques registrados para ese heroe h
	vector<pair<string, int>> mostrar_ataques(Heroe const& h) {
		if (heroes.find(h) == heroes.end()) // O(1)
			throw invalid_argument("Heroe inexistente");

		vector<pair<string, int>> res;
		auto ataquesH = heroes[h].ataques; // mapa ordenado

		for (auto& atqH : ataquesH) // recorrer mapa ordenado
			res.push_back({ atqH.first, atqH.second }); // insertar en vector

		return res;
	}

	// Coste: O(n) donde n son los elementos de la lista turnos
	vector<pair<string, int>> mostrar_turnos() {
		vector<pair<string, int>> res;

		for (auto it : turnos) { // recorrido con iteradores de la lista
			res.push_back({ it.first, it.second });
		}
		return res;
	}

	// Coste: O(1)
	// Con el uso de iteradores nos ahorramos bucles de busqueda
	bool villano_ataca(Villano const& v, Heroe const& h) {
		auto villano = villanos.find(v); // O(1)
		if (villano == villanos.end())
			throw invalid_argument("Villano inexistente");
		auto heroe = heroes.find(h); // O(1)
		if (heroe == heroes.end())
			throw invalid_argument("Heroe inexistente");
		// si el nombre del villano no es el primero de la lista de turnos, no es su turno
		if (v != turnos.front().first)
			throw invalid_argument("No es su turno");

		turnos.pop_front();
		(*heroe).second.vida -= (*villano).second.damg;// el heroe h pierde vida segun el daño del villano
		(*heroe).second.it->second = (*heroe).second.vida; // se actualiza la vida tambien en la lista de turnos
		turnos.push_back({ v,(*villano).second.vida }); // pide turno de nuevo
		(*villano).second.it = --turnos.end();

		// si el heroe es completamente derrotado se elimina de la batalla
		if ((*heroe).second.vida <= 0) {

			// se elimina de la lista de turnos
			turnos.erase((*heroe).second.it);

			// se elimina del diccionario de heroes
			heroes.erase(heroe); // teniendo el iterador ya al heroe, coste constante

			return true;
		}

		return false;
	}

	// Coste: similar al villano_ataca, añadiendo que se ha de buscar el ataque "ataque" y se trata de un diccionario ordenado, por lo que esa busqueda es logaritmica
	// Por lo tanto O(log n) donde n es el numero de ataques del heroe h
	bool heroe_ataca(Heroe const& h, string const& ataque, Villano const& v) {
		auto villano = villanos.find(v); // O(1)
		if (villano == villanos.end())
			throw invalid_argument("Villano inexistente");
		auto heroe = heroes.find(h); // O(1)
		if (heroe == heroes.end())
			throw invalid_argument("Heroe inexistente");
		// si el nombre del heroe no es el primero de la lista de turnos, no es su turno
		if (h != turnos.front().first)
			throw invalid_argument("No es su turno");


		auto ataqueHeroe = (*heroe).second.ataques.find(ataque);
		// si no tiene el ataque aprendido
		if (ataqueHeroe == (*heroe).second.ataques.end()) // O(log n) porque es ordenado
			throw invalid_argument("Ataque no aprendido");

		turnos.pop_front();

		(*villano).second.vida -= (*ataqueHeroe).second; // el villano v pierde vida segun el daño del ataque ataqueHeroe
		(*villano).second.it->second = (*villano).second.vida; // se actualiza la vida en la lista de turnos

		turnos.push_back({ h,(*heroe).second.vida }); // pide turno de nuevo
		(*heroe).second.it = --turnos.end();

		// si el villano es completamente derrotado se elimina de la batalla
		if ((*villano).second.vida <= 0) {

			// se elimina de la lista de turnos
			turnos.erase((*villano).second.it);

			// se elimina del diccionario de villanos
			villanos.erase(villano); // teniendo el iterador, coste constante

			return true;
		}

		return false;
	}
};

bool resuelveCaso() { // No tacar nada de esta función!
	string comando;
	cin >> comando;
	if (!cin) return false;

	SistemaBatallas sistema;
	Villano v; Heroe h;
	string ataque; int ptos; int valor;
	while (comando != "FIN") {
		try {
			if (comando == "aparece_villano") {
				cin >> v >> ptos >> valor;
				sistema.aparece_villano(v, ptos, valor);
			}
			else if (comando == "aparece_heroe") {
				cin >> h >> ptos;
				sistema.aparece_heroe(h, ptos);
			}
			else if (comando == "aprende_ataque") {
				cin >> h >> ataque >> valor;
				sistema.aprende_ataque(h, ataque, valor);
			}
			else if (comando == "mostrar_ataques") {
				cin >> h;
				auto ataques = sistema.mostrar_ataques(h);
				cout << "Ataques de " << h << endl;
				for (auto& [ataque, valor] : ataques) {
					cout << ataque << " " << valor << "\n";
				}
			}
			else if (comando == "mostrar_turnos") {
				cout << "Turno: " << endl;
				auto turnos = sistema.mostrar_turnos();
				for (auto& [pers, puntos] : turnos) {
					cout << pers << " " << puntos << "\n";
				}
			}
			else if (comando == "villano_ataca") {
				cin >> v >> h;
				bool derrotado = sistema.villano_ataca(v, h);
				cout << v << " ataca a " << h << endl;
				if (derrotado) cout << h << " derrotado" << endl;
			}
			else if (comando == "heroe_ataca") {
				cin >> h >> ataque >> v;
				bool derrotado = sistema.heroe_ataca(h, ataque, v);
				cout << h << " ataca a " << v << endl;
				if (derrotado) cout << v << " derrotado" << endl;
			}
		}
		catch (std::exception& e) {
			cout << "ERROR: " << e.what() << "\n";
		}
		cin >> comando;
	}

	cout << "---\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
	ifstream in("input3.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso()) {}

#ifndef DOMJUDGE 
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}

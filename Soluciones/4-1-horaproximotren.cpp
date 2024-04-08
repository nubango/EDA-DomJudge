// Nuria Bango Iglesias
// VJ07

/*
	-A que hora pasa el proximo tren-
 Todo el que ha estado alguna vez esperando que llegue el tren se ha planteado lo que podrıa haber hecho si hubiese sabido a que
 hora pasarıa. Es entonces cuando envidiamos a los usuarios que lo utilizan con frecuencia y son capaces de llegar a la estacion con solo
 un minuto de antelacion. Por que siempre confiamos en la suerte y no comprobamos a que hora pasara antes de vernos ya en el anden?

 Hoy, al llegar a la estacion y ver que de nuevo tendras que esperar, has decidido hacer una aplicacion que te permita saber en cualquier
 momento a que hora pasara el proximo tren. Para empezar, en el tiempo que has estado esperando ya has conseguido el horario de los
 trenes de las estaciones que utilizas a menudo. Ahora, ya sera muy facil calcular cuando pasara el proximo tren.

 Requisitos de implementacion
 Se debe utilizar una clase horas con la representacion que se considere mas oportuna. Como mınimo se debe implementar la sobrecarga del
 operador < como funcion miembro de la clase. La sobrecarga de los operadores de insercion (<<) y extraccion (>>) de las horas se hara con
 funciones externas a la clase.
 El constructor de la clase debe comprobar que los datos son correctos (0 ≤ horas ≤ 23; 0 ≤ minutos, segundos ≤ 59) y lanzar una excepcion
 si no lo son.

 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <vector>
using namespace std;

class Horas
{
private:
	int horas;
	int minutos;
	int segundos;

	bool horaCorrecta() const {
		return (horas >= 0 && horas <= 23 && minutos >= 0 && minutos <= 59 && segundos >= 0 && segundos <= 59);
	}

public:
	Horas() : horas(0), minutos(0), segundos(0) {}
	Horas(int h, int m, int s) : horas(h), minutos(m), segundos(s) {
		if (!horaCorrecta()) throw domain_error("ERROR\n");
	}
	Horas(const Horas& hora) : horas(hora.horas), minutos(hora.minutos), segundos(hora.segundos) {
	}
	bool operator<(const Horas& h) const {
		return ((horas < h.horas) ||
			(horas == h.horas) && (minutos < h.minutos) ||
			(horas == h.horas) && (minutos == h.minutos) && (segundos < h.segundos));
	}

	friend ostream& operator<<(ostream& out, const Horas& h);
	friend istream& operator>>(istream& in, Horas& h);
};

// Funciones externas a la clase Horas
ostream& operator<<(ostream& out, const Horas& h) {
	// Comprobaciones extra para formateo correcto de digitos menores de 10
	if (h.horas < 10)
		out << "0";
	out << h.horas << ":";
	if (h.minutos < 10)
		out << "0";
	out << h.minutos << ":";
	if (h.segundos < 10)
		out << "0";
	out << h.segundos;
	return out;
}

istream& operator>>(istream& in, Horas& h) {
	char c;
	int horas, minutos, segundos;
	in >> horas >> c >> minutos >> c >> segundos;
	h = Horas(horas, minutos, segundos);

	return in;
}

// Dado el vector de horarios de trenes horas y la hora a la que se consulta, devuelve la hora del proximo tren sol si es posible
// Si no existe hora posible la funcion devuelve false
bool primerTren(const vector<Horas>& horas, Horas& consulta, Horas& sol) {
	int i = 0;
	while (i < horas.size()) {
		if (consulta < horas[i]) {
			sol = horas[i];
			return true;
		}
		i++;
	}
	return false;
}

bool resuelveCaso() {
	// T: trenes que salen de la estacion
	// H: horas a consultar
	int T, H;
	cin >> T >> H;

	if (T == 0 && H == 0)
		return false;

	// T trenes en formato Horas (HH:MM:SS), en orden creciente
	vector<Horas> horas(T);
	for (Horas& h : horas) std::cin >> h;

	Horas consulta, sol;
	for (int i = 0; i < H; i++) {
		try { // try-catch error de formato de hora
			std::cin >> consulta;
			// sol: hora de salida
			if (primerTren(horas, consulta, sol))
				cout << sol << "\n";
			else // si no existe solucion: NO
				cout << "NO\n";
		}
		catch (const std::exception& e)
		{
			std::cout << e.what(); // ERROR si la hora de consulta es incorrecta
		}
	}

	cout << "---\n";

	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

	while (resuelveCaso());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
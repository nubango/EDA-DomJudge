// Nuria Bango Iglesias
// VJ07

/*
	-Una tarde de sabado-
 Me han llamado unos amigos para ver una pelıcula en el cine este sabado. Entre todos han elaborado una lista con sus preferencias y me
 han dicho que decida cual de ellas vamos a ver. Como ya he quedado el sabado para cenar con otros amigos tengo que elegir una pelıcula
 que termine antes de la hora de la cena. Al mirar la cartelera, he visto que solo pone la hora de comienzo y la duracion de la pelıcula,
 pero no la hora en que termina. Como no quiero equivocarme le he pedido a mi hermano que me ayude a hacer un programa que lo calcule.
 Me ha dicho que si le doy la hora a la que empieza cada pelıcula y lo que dura me mostrara una lista de todas las pelıculas ordenadas por
 la hora a la que terminan. De esta forma podre ver facilmente cuales son las que puedo ir a ver y el tiempo que me quedara libre con cada una.
 Requisitos de implementacion.
 En la implementacion del problema se debe utilizar la clase horas implementada en el problema anterior. Se le anadira el operador suma (+),
 que lanzara una excepcion cuando la suma de las horas exceda del dia actual.
 Se utilizara una clase pelicula que guardara los datos relativos a las pelıculas. Esta clase necesita el operador menor para poder ordenar,
 por tiempo de finalizacion, el vector que almacenara las pelıculas.
 El vector se puede ordenar utilizando la funcion sort de la librerıa algorithm.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

	Horas operator+(const Horas& hora) const {
		Horas resultado;
		int h, m, s;
		s = hora.segundos + segundos;
		m = hora.minutos + minutos + (s / 60);
		h = hora.horas + horas + (m / 60);

		resultado.segundos = s % 60;
		resultado.minutos = m % 60;
		resultado.horas = h;

		if (h > 24) throw domain_error("ERROR\n");

		return resultado;
	}

	bool operator==(const Horas& h) const {
		return(horas == h.horas && minutos == h.minutos && segundos == h.segundos);
	}

	friend ostream& operator<<(ostream& out, const Horas& h);
	friend istream& operator>>(istream& in, Horas& h);
};

class Pelicula {
private:
	string nombre;
	Horas fin;

public:
	Pelicula() : nombre(""), fin(Horas()) {}
	Pelicula(const string& n, const Horas& ini, const Horas& duracion) : nombre(n), fin(ini + duracion) {}
	Pelicula(const Pelicula& pelicula) : nombre(pelicula.nombre), fin(pelicula.fin) {}

	Horas getFin() {
		return fin;
	}

	string getNombre() {
		return nombre;
	}

	bool operator<(const Pelicula& p) const {
		return ((fin < p.fin) || (fin == p.fin && nombre < p.nombre));
	}
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

//-------------------------------------

bool resuelveCaso() {
	int n;
	std::cin >> n;
	if (n == 0)
		return false;

	Horas inicio, duracion;
	string nombre;
	Pelicula pelicula;
	vector<Pelicula> peliculas;

	for (int i = 0; i < n; i++)
	{
		cin >> inicio >> duracion;
		getline(cin, nombre);
		pelicula = Pelicula(nombre, inicio, duracion);
		peliculas.push_back(pelicula);
	}

	sort(peliculas.begin(), peliculas.end());

	for (Pelicula& p : peliculas)
		cout << p.getFin() << " " << p.getNombre() << "\n";

	std::cout << "---\n";

	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


	while (resuelveCaso());


	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
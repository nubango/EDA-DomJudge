// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*
Cuestion: Si los listados no viniesen ordenados, ¿Cual seria el menor orden de complejidad posible del algoritmo correspondiente? 
Justifica la respuesta. Ten en cuenta que ordenar un vector con n elementos puede hacerse en complejidad O(n ∗ log(n))

Respuesta: El algoritmo una vez ordenados tiene coste O(n) y la ordenacion es coste O(n*log n), por lo que el coste final sera el maximo 
de ambos, que en este caso es O(n*log n)
*/

// El algoritmo recorre una vez cada vector, por lo que es un algoritmo lineal
// O(n + m) donde n = num elementos del vector eda y m num elementos del vector tpv
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
	vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv) {

	// estos iteradores recorren de manera independiente los vectores eda y tpv
	int i = 0; // iterador para eda
	int j = 0; // iterador para tpv

	// el bucle recorre hasta la longitud de los vectores
	while (i < eda.size() && j < tpv.size()) {
		// si coinciden los elementos, son comunes
		if (eda[i] == tpv[j]) {
			comunes.push_back(eda[i]);
			i++; j++;
		}
		// si no coinciden, hay que ver cual es el elemento menor para procesar ese
		else {
			if (eda[i] < tpv[j]) {
				soloEda.push_back(eda[i]);
				i++;
			}
			else {
				soloTpv.push_back(tpv[j]);
				j++;
			}
		}
	}

	// si el bucle anterior termina y quedan elementos en alguno de los vectores eda o tpv
	// seran elementos que solo pertenecen a soloEda o soloTpv respectivamente
	while (i < eda.size()) {
		soloEda.push_back(eda[i]);
		i++;
	}
	while (j < tpv.size()) {
		soloTpv.push_back(tpv[j]);
		j++;
	}
}

void resuelveCaso() {
	int n;
	cin >> n;
	vector<string> eda(n);
	vector<string> comunes;
	vector<string> soloEda;
	vector<string> soloTpv;
	for (string& e : eda) cin >> e;
	cin >> n;
	vector<string> tpv(n);
	for (string& e : tpv) cin >> e;
	comparaListados(eda, tpv, comunes, soloEda, soloTpv);
	for (string& e : comunes) cout << e << " ";
	cout << endl;
	for (string& e : soloEda) cout << e << " ";
	cout << endl;
	for (string& e : soloTpv) cout << e << " ";
	cout << endl;
}

int main() {
#ifndef DOMJUDGE
	ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
#endif

	return 0;
}
// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// un digito es complementario de otro si la suma de ambos es 9
// O(1)
int digComp(int n) {
	return 9 - n;
}

// dado un numero entero, devuelve el numero formado por los digitos complementarios
// O(p) donde p es el numero de digitos del numero n
int complementario(int n) {
	// caso base: un solo digito
	if (n <= 9)
		return digComp(n);

	// se llama a la recurrencia con n/10 para quitar el digito mas a la derecha
	// y que comience por el digito mas a la izquierda a calcular el complementario
	int r = complementario(n / 10);
	// se multiplica el resultado de la llamada recursiva por 10 y se le suma el complementario del
	// ultimo digito para recombinar los complementarios de los digitos y formar el complementario 
	// del numero entero original
	return r * 10 + digComp(n % 10);
}

// dado un numero entero, devuelva el inverso del numero formado por los digitos complementarios
// O(p) donde p es el numero de digitos del numero n
pair<int, int> complementarioInverso(int n) {
	// caso base: un solo digito
	if (n <= 9)
		return { digComp(n), 10 };

	auto result = complementarioInverso(n / 10);
	int r = result.first; // complementario parcial calculado
	int p = result.second; // posicion del lugar del digito
	return { digComp(n % 10) * p + r, p * 10 };
}

void resuelveCaso() {
	int n;
	cin >> n;
	cout << complementario(n) << " " << complementarioInverso(n).first << "\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 

	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
		resuelveCaso();

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
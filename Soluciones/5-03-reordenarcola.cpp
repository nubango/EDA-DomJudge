// Nuria Bango Iglesias
// VJ04

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

void reordena(queue<int>& cola) {
	stack<int> negativos; // LIFO
	queue<int> positivos; // FIFO

	while (!cola.empty()) {
		int front = cola.front();
		cola.pop();

		if (front < 0)
			negativos.push(front);
		else
			positivos.push(front);
	}

	while (!negativos.empty()) {
		cola.push(negativos.top());
		negativos.pop();
	}

	while (!positivos.empty())
	{
		cola.push(positivos.front());
		positivos.pop();
	}
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)
		return false;

	queue<int> q;
	int j;
	for (int i = 0; i < n; i++) {
		cin >> j;
		q.push(j);
	}

	reordena(q);

	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << '\n';
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

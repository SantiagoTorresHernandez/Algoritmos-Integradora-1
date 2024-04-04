/*

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Funcion para leer archivos y retorna el contenido
// Complejidad: 
string readFile(const string &filename) {
	ifstream file(filename);
	if (file.fail()) {
		cerr << "Error al abrir el archivo: " << filename << endl;
		exit(1);
	}
	string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	return content;
}

// Funcion para procesar el LPS: longest proper prefix which is also suffix
// Complejidad: 
vector<int> lps(string p) {
	int n = p.size();
	vector<int> lpsv(n, 0);

	//implementacion lps
	int j = 0;
	int i = 0;

	while (i < n) {
		if (p[i] == p[j]) {
			lpsv[i++] = j + 1;
		}
		else {
			if (j == 0) {
				lpsv[i] = 0;
				i++;
			}
			else {
				j = lpsv[j - 1];
			}
		}
	}
	return lpsv;
}

// Funcion para calcular el kmp
vector<int> kmp(string texto, string patron) {
	vector<int> posMatch;
	vector<int> lpsv = lps(patron);

	//implementacion de kmp
	int n = texto.size();
	int m = patron.size();
	int i = 0;
	int j = 0;

	while (i < n) {
		if (texto[i] == patron[i]) {
			j++;
			i++;
			if (j == m) {
				posMatch.push_back(i - m);
				j = lpsv[j - 1];
			}
		}
		else {
			if (j == 0) {
				i++;
			}
			else {
				j = lpsv[j - 1];
			}
		}
	}

	return posMatch;
}

int main() {
	// archivos
	string t1 = readFile("transmission1.txt");
	string mcode1 = readFile("mcode1.txt");

	vector<string> mcode;
	mcode.push_back(mcode1);

	vector<string> transmissions;
	transmissions.push_back(t1);

	vector<int> posMatch = kmp(t1, mcode1);

	if (posMatch.size() == 0) {
		cout << "No hay match" << endl;
	}
	else {
		for (int i = 0; i < posMatch.size(); i++) {
			cout << posMatch[i] << " ";
		}
		cout << endl;
	}

	return 0;
}

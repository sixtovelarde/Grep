#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// Función para resaltar coincidencias en color
void colorear(string palabra) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsola, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << palabra;
    SetConsoleTextAttribute(hConsola, FOREGROUND_BLUE);
}

// Función para buscar coincidencias en un archivo
void buscarCoincidencias(const string& archivo, const string& palabra) {
    ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    int numLineas = 0;
    int numCoincidencias = 0;

    while (getline(archivoEntrada, linea)) {
        numLineas++;
        size_t pos = linea.find(palabra);
        while (pos != string::npos) {
            numCoincidencias++;
            colorear(linea.substr(pos, palabra.length()));
            pos = linea.find(palabra, pos + 1);
        }
        cout << " (" << numLineas << ")" << linea << endl;
    }

    cout << "Total de líneas con coincidencias: " << numLineas << endl;
    cout << "Total de coincidencias encontradas: " << numCoincidencias << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <archivo> <palabra>" << endl;
        return 1;
    }

    string archivo = argv[1];
    string palabra = argv[2];

    buscarCoincidencias(archivo, palabra);

    return 0;
}

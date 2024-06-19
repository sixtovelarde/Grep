#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

// Función para resaltar coincidencias en color
void colorear(const string& palabra) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsola, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << palabra;
    SetConsoleTextAttribute(hConsola, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// Función para buscar coincidencias en un archivo
void buscarCoincidencias(const string& archivo, const string& palabra) {
    ifstream archivoEntrada(archivo, fstream::in); // Cambio para usar el parámetro 'archivo'
    if (!archivoEntrada.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    int numLineas = 0;
    int numCoincidencias = 0;

    while (getline(archivoEntrada, linea)) {
        size_t pos = linea.find(palabra);
        while (pos != string::npos) {
            numCoincidencias++;
            cout << linea.substr(0, pos); // Imprime el texto antes de la coincidencia
            colorear(linea.substr(pos, palabra.length())); // Resalta la coincidencia
            linea = linea.substr(pos + palabra.length()); // Actualiza la línea para continuar la búsqueda
            pos = linea.find(palabra); // Busca la siguiente coincidencia
        }
        cout << linea << endl; // Imprime el resto de la línea
        numLineas++;
    }
    cout << "Total de lineas con coincidencias: " << numLineas << endl;
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

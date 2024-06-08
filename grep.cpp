#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstring>
#include<cstdio>
#include<windows.h>

using namespace std;

const int maxpalabus = 10;

//Habilitar colores en la consola
void colorear(int color){
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsola, color);
}
//colorear
void ColorPalabra(string& texto, const string palcoloreadas[maxpalabus], int numpalabras){

    size_t pos = 0;
    size_t encontradas;

    while ((encontradas = texto.find_first_of(" \n\t", pos)) != string::npos){

        string palabra = texto.substr(pos, encontradas - pos);
        bool resaltar = false;

        for (int i=0; i < numpalabras; i++){

            if (palabra == palcoloreadas[i]){

                resaltar = true;
                break;
            }
        }

        if (resaltar){
            colorear(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
            cout << palabra;
            colorear(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }
        else {
            cout << palabra;
        }
        cout << texto[encontradas];
        pos = encontradas + 1;
    }
    cout << texto.substr(pos);
}

void grep(const char* pal, const char* name_pal){

    ifstream carpeta(name_pal);
    char cadena[1000];
    int linea=0;

    if (carpeta){

        carpeta.getline(cadena, 1000);
        linea++;

        if (carpeta && strstr(cadena, pal)){

            cout<<name_pal<<"("<<linea<<")"<<cadena<<endl;
        }
    }

}

int main (int argc, char* argv[]) {
 
    if (argc < 3) {
        cout << "Uso: grep <palabra a buscar> <carpeta1> [carpetas...]" << endl;
        return -1;
    } 
    
    else {
        for (int i = 2; i < argc; i++) {
            grep(argv[1], argv[i]);
        }
    }


    return 0;

}
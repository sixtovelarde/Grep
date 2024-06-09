#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<windows.h>

#define rainbow SetConsoleTextAttribute

using namespace std;

const int maxpalabus = 10;
int num=0;

//Habilitar pigmentos en la consola
void colorear(int pigmentos){
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    rainbow(hConsola, pigmentos);
}


//colorear palabras
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

//buscar la palabra
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
 
int main () {

    //volver a habilitar los pigmentos en consola pero dentro del main
    int pigmentos;
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    rainbow(hConsola, pigmentos);

    rainbow(hConsola, 1);

    ifstream archivobusq("../archivo_busqueda.txt");

    if (!archivobusq.is_open()){

        cout<<"Error abrir el archivo"<<endl;
        return 1;
    }

    stringstream datos;
    datos<<archivobusq.rdbuf();
    string texto = datos.str();

    archivobusq.close();

    cout<<"Ingrese la palabra que desea resaltar: "<<endl;
    string palcoloreadas;
    cin >> palcoloreadas;

    ColorPalabra(texto, &palcoloreadas, 1);

    rainbow(hConsola, 2);
    
    return 0;

}
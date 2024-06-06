#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdio>

using namespace std;

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
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>

using namespace std;

//Imprmir instrucciones de uso
void print_usage(const char *grep){

    cout << "\n\033[1;31mUso: \033[1;33m" << grep << "\n\033[1;31m   INTRODUCIR LO SIGUIENTE EN EL ORDEN ESPECIFICO\n\n\033[1;36m  \033[1;31m1ro-\033[1;36m g++ -o main ../(nombrearchivo).cpp \033[1;35mSOLO SI ES LA 1RA VEZ QUE EJECUTAS EL PROGRAMA\033[1;36m"<<endl;
    cout << "\n  \033[1;31m2do-\033[1;36m ./main.exe (ruta COMPLETA del archivo) (palabra a buscar) (sensibilidad a mayusculas) (color resaltado)" << endl;
    cout << "       \033[1;31m\nSensibilidad a mayusculas:\033[1;36m 1 para distinguir entre mayusculas y minusculas, 0 para ignorar" << endl;
    cout << "       \033[1;31mColor resaltado:\033[1;36m (opciones: rojo, verde, azul, amarillo, magenta, cian)\n\033[1;35m     \nRecuerda cambiar los slags de la ruta del archivo donde vas a buscar a '\033[1;33m/\033[1;35m'\033[0m\n" << endl;
}

//declarar colores
string declararColores(const string &color){

    unordered_map<string, string> tonos = {

        {"rojo", "\033[1;31m"},
        {"verde", "\033[1;32m"},
        {"azul", "\033[1;34m"},
        {"amarillo", "\033[1;33m"},
        {"magenta", "\033[1;35m"},
        {"cian", "\033[1;36m"}
        };

    if (tonos.find(color) != tonos.end()){
        return tonos[color];
    }

    else{

        cout << "Color no valido. Usando color rojo por defecto." << endl;
        return "\033[1;31m";
    }
}


//colorear palabras
void PonerlecolorPals(const string &line, const string &word, bool case_sensitive, const string &color_code){
    regex_constants::syntax_option_type flag = case_sensitive ? regex_constants::ECMAScript : regex_constants::icase;
    regex word_regex("(" + word + ")", flag);
    string result = regex_replace(line, word_regex, color_code + "$&\033[0m");
    cout << result << endl;
}

int main(int argc, char *argv[]){

    if (argc != 5){
        print_usage(argv[0]);
        return 1;
    }

    //opciones para los argumentos
    string file_path = argv[1];
    string search_word = argv[2];
    bool case_sensitive = stoi(argv[3]);
    string color = argv[4];
    string color_code = declararColores(color);

    ifstream file(file_path);

    if (!file.is_open()){

        cout << "Error: No se pudo abrir el archivo " << file_path << endl;
        return 1;
    }

    string line;
    int nrodelineas = 0;
    int total_coincidencias = 0;
    int lineasCon_coincidencias = 0;

    while (getline(file, line)){

        nrodelineas++;
        regex_constants::syntax_option_type flag = case_sensitive ? regex_constants::ECMAScript : regex_constants::icase;
        regex word_regex(search_word, flag);

        if (regex_search(line, word_regex)){

            PonerlecolorPals(line, search_word, case_sensitive, color_code);
            total_coincidencias++;
            lineasCon_coincidencias++;
        }
    }

    cout << "\n\033[1;31mTotal de coincidencias: \033[0m" << total_coincidencias << endl;
    cout << "\033[1;31mTotal de lineas con coincidencias: \033[0m" << lineasCon_coincidencias << endl;
    file.close();

    return 0;
}
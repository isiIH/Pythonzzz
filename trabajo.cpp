#include <iostream>
#include <fstream>
using namespace std;

void leerArchivo(string text);

int main(int argc, char **argv){

    leerArchivo("english.100MB");
	return EXIT_SUCCESS;
}

void leerArchivo(string text){

    ifstream archivo;
    archivo.open("archivos/" + text,ios::in);
    string linea;

    if(archivo.fail()){
        cout << "Error" << endl;
        exit(1);
    }
    while(!archivo.eof()){
        getline(archivo,linea);
        cout << linea << endl;
    }
    archivo.close();
}
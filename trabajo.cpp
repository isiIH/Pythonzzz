#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <algorithm>
#include "huffman.h" 
#include "shannon.h" 
using namespace std;

void leerArchivo(string text);

int main(int argc, char **argv){

    /* ifstream archivo;
    archivo.open("archivos/prueba.txt",ios::in);
    char letra;

    if(archivo.fail()){
        cout << "Error" << endl;
        exit(1);
    }
    while(!archivo.eof()){
        archivo >> letra;

    }
    archivo.close(); */

    string texto = "prueba.txt";
    vector<Node> v = obtenerProb(texto);
	return EXIT_SUCCESS;
}

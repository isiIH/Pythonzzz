#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "huffman.h" 
#include "shannon.h" 
using namespace std;

void leerArchivo(string text);

int main(int argc, char **argv){

    if(argc != 2){
		cout << "Error. Debe ejecutarse como ./trabajo archivo" << endl;
		exit(EXIT_FAILURE);
	}

    string file = argv[1];
    vector<Node> v;
    ifstream archivo;
    archivo.open("archivos/" + file, ios::in);
    string linea;
    string texto = "";

    if(archivo.fail()){
        cout << "Error" << endl;
        exit(1);
    }
    while(!archivo.eof()){
        getline(archivo, linea);
        texto += linea;
    }
    archivo.close();

    clock_t start = clock();
    obtenerProb(v, texto);
    clock_t end = clock();
    cout << "Tiempo de ejecución obtenerProb: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    sort(v.begin(), v.end(), [] (Node &x, Node &y) { return x.probabilidad > y.probabilidad; });

    int l = 0;
    int r = v.size() - 1;
    start = clock();
    asignaCodigos(v, l, r);
    end = clock();
    cout << "Tiempo de ejecución asignaCodigos: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;

    imprimirSimbolos(v);
    start = clock();
    encode(v, texto);
    end = clock();
    cout << "Tiempo de ejecución encode: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;

    /* leerArchivo(texto); */
	return EXIT_SUCCESS;
}

void leerArchivo(string text) {
    ifstream archivo;
    archivo.open("archivos/" + text, ios::in);
    string linea;

    if(archivo.fail()){
        cout << "Error" << endl;
        exit(1);
    }

    while(getline(archivo, linea)){
        cout << linea << endl;
    }
    archivo.close();
}
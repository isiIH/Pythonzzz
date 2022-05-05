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
/*     imprimirSimbolos(v);
    cout << endl; */
    sort(v.begin(), v.end(), [] (Node &x, Node &y) { return x.probabilidad > y.probabilidad; });
    imprimirSimbolos(v);

    int l = 0;
    int r = v.size() - 1;
    particion(v, &l, &r, v[l].probabilidad, v[r].probabilidad);
    cout << "l: " << l << ", r: " << r << endl;
	return EXIT_SUCCESS;
}

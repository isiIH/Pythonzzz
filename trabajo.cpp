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

    string texto = "pr.txt";
    vector<Node> v;

    obtenerProb(v, texto);
    sort(v.begin(), v.end(), [] (Node &x, Node &y) { return x.probabilidad > y.probabilidad; });

    int l = 0;
    int r = v.size() - 1;
    encode(v, l, r);

    imprimirSimbolos(v);
    crearCodificado(v, texto);

	return EXIT_SUCCESS;
}

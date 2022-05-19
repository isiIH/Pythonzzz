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
    vector<Simbolo> F;
    vector<PosCodificado> P;
    ifstream archivo;
    archivo.open("archivos/" + file, ios::in);
    string linea, textoCod;
    string texto = "";
    double total = 0.0;

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
    obtenerProb(F, texto);
    clock_t end = clock();
    cout << "Tiempo de ejecución obtenerProb: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    total += (double(end - start))/(CLOCKS_PER_SEC);
    sort(F.begin(), F.end(), [] (Simbolo &x, Simbolo &y) { return x.probabilidad > y.probabilidad; });

    int l = 0;
    int r = F.size() - 1;
    start = clock();
    asignaCodigos(F, l, r);
    end = clock();
    cout << "Tiempo de ejecución asignaCodigos: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    total += (double(end - start))/(CLOCKS_PER_SEC);

    imprimirSimbolos(F);
    
    start = clock();
    textoCod = encode(F, texto);
    /* textoCod = encode2(F, P, texto); */
    end = clock();
    cout << "Tiempo de ejecución encode: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    total += (double(end - start))/(CLOCKS_PER_SEC);

    start = clock();
    decode(F, textoCod);
    /* decode2(F, textoCod, 2); */
    /* decode3(F, P, 1, 20, textoCod); */
    end = clock();
    cout << "Tiempo de ejecución decode: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    total += (double(end - start))/(CLOCKS_PER_SEC);

    cout << "Tiempo total: " << total << endl;

    /* imprimirPosiciones(P); */
    /* leerArchivo("decodificado.txt"); */
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
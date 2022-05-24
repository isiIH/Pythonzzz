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
    string texto = "", textoCod, textoDecod;
    double total = 0.0;
    char letra;

    if(archivo.fail()){
        cout << "Error" << endl;
        exit(1);
    }
    while(archivo >> noskipws >> letra) {
        if(int(letra) < 256 && int(letra)>=0){
            texto += letra;
        }
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
    textoDecod = decode(F, textoCod);
    /* textoDecod = decode2(F, textoCod, 7, texto.size());
    textoDecod = decode3(F, P, 1, 20, textoCod); */
    end = clock();
    cout << "Tiempo de ejecución decode: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    total += (double(end - start))/(CLOCKS_PER_SEC);

    cout << "Tiempo total: " << total << "s" << endl;

    /* imprimirPosiciones(P); */
    /* leerArchivo("decodificado.txt"); */

    cout << "\n" << "Tamaño Simbolo: " << sizeof(struct Simbolo) << " bytes" << endl;
    cout << "Tamaño PosCodificado: " << sizeof(struct PosCodificado) << " bytes" << endl;
    cout << "Tamaño F: " << (F.size() * double(sizeof(struct Simbolo)))/1048576 << " MB" << endl;
    cout << "Tamaño P: " << (P.size() * double(sizeof(struct PosCodificado)))/1048576 << " MB" << endl;
    cout << "Tamaño texto original: " << (double(texto.length()))/1048576 << " MB" << endl;
    cout << "Tamaño texto codificado: " << ( (double(textoCod.length()))/1048576 )/8 << " MB" << endl;
    cout << "Tamaño texto decodificado: " << (double(textoDecod.length()))/1048576 << " MB" << endl;
    /* cout << texto << endl;
    cout << textoCod << endl;
    cout << textoDecod << endl; */
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
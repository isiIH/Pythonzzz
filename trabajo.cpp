#include <iostream>
#include <string> 
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <unordered_map> 
#include "huffman.h"
#include "shannon.h" 
using namespace std;

void readFile(string *text);
void ejecutarShannon(string texto);
void ejecutarHuffman(string texto);

//--------------------------------------------------------------------------------------------

int main(int argc, char **argv){
    
    if(argc != 2){
		cout << "Error. Debe ejecutarse como ./trabajo archivo" << endl;
		exit(EXIT_FAILURE);
	}

    string file = argv[1];
    ifstream archivo;
    archivo.open("archivos/" + file, ios::in);
    string texto = "";
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

    ejecutarShannon(texto);
    /* ejecutarHuffman(texto); */

	return EXIT_SUCCESS;
}

//----------------------------------------------------------------------------------------------

void readFile(string *text){


    ifstream archivo;
    string texto;
    archivo.open("archivos/english.100MB",ios::in);

    if(archivo.fail()){

        cout << "Error" << endl;
        exit(1);
    }
    while(!archivo.eof()){

        getline(archivo,*text);

    }
    archivo.close();



    // string texto = "";
    // ifstream archivo;

    // archivo.open("archivos/prueba.txt",ios::in);

    // if (archivo.is_open()) {
    //     while (getline(archivo, texto)) {
    //         //cout << texto << endl;
    //         *text =  *text + texto;
    //     }
    //     archivo.close();
    // } else {
    //     cout << "No se pudo abrir el archivo";
    // }
    
    //cout << *text << endl; 

    
}

void ejecutarShannon(string texto) {
    vector<Simbolo> F;
    vector<PosCodificado> P;
    string textoCod, textoDecod;
    double total = 0.0;

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
}

void ejecutarHuffman(string texto) {
    
    double totalT = 0.0;
    vector<Node> F;
    Node s; 
    string binario; 

    
    //crea una cola de prioridad para guardar los nodos del arbol 
    priority_queue<Node* ,vector<Node*>, comp> pq; 
    unordered_map<char, string> CodeHuffman;
    string textodeco = "";
    //readFile(&text);

    //cuenta cuantas veces aparece el simbolo en el texto 


    clock_t start = clock();
    CuentaFrecuencia(F,texto,s);
    clock_t end = clock();
    cout << "Tiempo de ejecución  de contar las frecuencias: " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    totalT += (double(end - start))/(CLOCKS_PER_SEC);

    start = clock();
    Node* root =GeneradorArbol(F,pq);
    end = clock();
    cout << "Tiempo de ejecución de Generar arbol  : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    totalT += (double(end - start))/(CLOCKS_PER_SEC);
    
    start = clock();
    encode(root, "", CodeHuffman); 
    end = clock();
    cout << "Tiempo de ejecución de encode  : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    totalT += (double(end - start))/(CLOCKS_PER_SEC);
    //imprimirCodeHuffman(CodeHuffman);

    start = clock();
    codigoBinario(CodeHuffman, texto, &binario);
    end = clock();
    cout << "Tiempo de ejecución de pasar code a binario   : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    totalT += (double(end - start))/(CLOCKS_PER_SEC);

    cout << "empieza decode "<< endl;
    start = clock();
    decode(root, binario, textodeco);
    end = clock(); 
    cout << "Tiempo de ejecución de decode   : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
    totalT += (double(end - start))/(CLOCKS_PER_SEC);


    if(0){
        for(int j = 0; j<textodeco.size(); j++)
            cout << textodeco[j];
    }

    cout << " tiempo total: " << totalT <<"s" << endl; 
}
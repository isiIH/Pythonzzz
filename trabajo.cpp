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

void ejecutarShannon(string texto);
void ejecutarHuffman(string texto);

//--------------------------------------------------------------------------------------------

int main(int argc, char **argv){
    
    if(argc != 3){
		cout << "Error. Debe ejecutarse como ./trabajo archivo  1 (Shannon) o 0 (Huffman)  " << endl;
		exit(EXIT_FAILURE);
	}

    string file = argv[1];
    int condicion = atoi( argv[2]); // si es 1 ejecuta Shannon, si es 0 ejecuta Huffman
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


    if(condicion == 1)
        ejecutarShannon(texto);
    else 
        if (condicion == 0 )
            ejecutarHuffman(texto); 

	return EXIT_SUCCESS;
}

//----------------------------------------------------------------------------------------------

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
    //sort(F.begin(), F.end(), [] (Simbolo &x, Simbolo &y) { return x.probabilidad > y.probabilidad; });

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
    // PARA CALCULAR P DESCOMENTAR LA SIGUIENTE LINEA (esto para que funcione decode3)
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
    vector<PosCodificadoH> P;
    Node s;  
    string binario, codigobinario2; 
    string textdecode2 , textdecode3; 


    
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

    if(1){                    // si el if = 0  es con la experimentacion  2 , si es 1 el huffman normal.   
       

        start = clock();
        codigoBinario(CodeHuffman, texto, &binario);
        end = clock();
        cout << "Tiempo de ejecución de pasar code a binario   : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
        totalT += (double(end - start))/(CLOCKS_PER_SEC);


        
        cout << "empieza decode "<< endl;
        start = clock();
        decode(root, binario, textodeco);
        //textodeco = decode2(root, binario,  100, binario.size());   //para la experimentacion  1 
        end = clock(); 
        cout << "Tiempo de ejecución de decode   : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
        totalT += (double(end - start))/(CLOCKS_PER_SEC);



    }else{
        cout<<" "<<endl;
        cout<<" "<<endl;
        cout<<" encode 2 y decode 3 parte de la experimentacion 2  "<<endl;

        start = clock();
        codigobinario2 = encode2(CodeHuffman,P,texto); // traspasa a binario los codigo de huffman
        end = clock();
        cout << "Tiempo de ejecución de encode 2  es    : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
        totalT += (double(end - start))/(CLOCKS_PER_SEC);    

        start = clock();
        textdecode3=decode3(root,P, 1,20, codigobinario2);
        end = clock();
        cout << "Tiempo de ejecución de decode  3  es    : " << (double(end - start))/(CLOCKS_PER_SEC) << "s" << endl;
        totalT += (double(end - start))/(CLOCKS_PER_SEC);


    }

    cout << " tiempo total: " << totalT <<"s" << endl; 
}
#include <iostream>
#include <string> 
#include <fstream> 
#include <ctime>
#include "huffman.h" 
#include "shannon.h" 
#include <unordered_map> 
#include <vector>


using namespace std;

void readFile(string *text);

//--------------------------------------------------------------------------------------------

int main(int argc, char **argv){

    double totalT = 0.0;
    vector<Node> F;
    ifstream archivo;
    archivo.open("archivos/english.100MB",ios::in);
    char letra;
    string texto = "" ;
    Node s; 
    string binario; 

    
    //crea una cola de prioridad para guardar los nodos del arbol 
    priority_queue<Node* ,vector<Node*>, comp> pq; 
    unordered_map<char, string> CodeHuffman;
    string textodeco = "";
    //readFile(&text);
    
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
    
    // //cout << *text << endl; 
 

    
}
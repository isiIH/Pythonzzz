#include <iostream>
#include <string> 
#include <fstream> 
#include "huffman.h" 
#include "shannon.h" 
#include <unordered_map> 
#include <vector>
using namespace std;

void readFile(string *text);

//--------------------------------------------------------------------------------------------

int main(int argc, char **argv){
    
    vector<Node> F;
    ifstream archivo;
    archivo.open("archivos/english.100MB",ios::in);
    char letra;
    string texto = "" ;
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
    
    Node s; 
    string binario; 
    //crea una cola de prioridad para guardar los nodos del arbol 
    priority_queue<Node* ,vector<Node*>, comp> pq; 
    unordered_map<char, string> CodeHuffman;
    string textodeco = "";
    

    //cuenta cuantas veces aparece el simbolo en el texto 
    CuentaFrecuencia(F,texto,s);

    


    Node* root =GeneradorArbol(F,pq);
    
    encode(root, "", CodeHuffman); 

    imprimirCodeHuffman(CodeHuffman);

    codigoBinario(CodeHuffman, texto, &binario);
    
    
    cout << "empieza decode "<< endl;
    decode(root, binario, textodeco); 

    for(int j = 0; j<textodeco.size(); j++){

        cout << textodeco[j];

    }
    


    
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
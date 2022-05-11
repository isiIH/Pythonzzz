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
    
   
    string text = "" ;
    readFile(&text);
    

    createArbol(&text);
    
	return EXIT_SUCCESS;
}

//----------------------------------------------------------------------------------------------

void readFile(string *text){


    // ifstream archivo;
    // string texto;
    // archivo.open("archivos/prueba.txt",ios::in);

    // if(archivo.fail()){

    //     cout << "Error" << endl;
    //     exit(1);
    // }
    // while(!archivo.eof()){

    //     getline(archivo,*text);
    //      cout << *text << endl; 
    // }
    // archivo.close();



    string texto = "";
    ifstream archivo;

    archivo.open("archivos/prueba.txt",ios::in);

    if (archivo.is_open()) {
        while (getline(archivo, texto)) {
            //cout << texto << endl;
            *text =  *text + texto;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo";
    }
    
    //cout << *text << endl; 
 

    
}
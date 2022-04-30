#include <iostream>
#include <string> 
#include <queue> 
#include <unordered_map> 


using namespace std;

struct Node{               // genera el tipo de dato node 
    char symbol;
    int frequency;
    Node *left, *right;
};

struct comp{                               // objeto que sirve para ordenar la pila 
    bool operator()(Node* l, Node* r){
        return l -> frequency > r -> frequency;
    }
};

Node*  getNode(char symbol, int frequency,  Node *left , Node *right){  //asigna un nodo al arbol 
    Node* nodo = new Node();
    nodo -> symbol = symbol;
    nodo -> frequency = frequency;
    nodo -> left = left; 
    nodo -> right = right;

    return nodo; 
}


void encode(Node* root, string str, unordered_map<char,string> &CodeHuffman){

    if (root == nullptr)
        return;
    if(!root -> left && !root -> right){
        CodeHuffman[root  -> symbol] = str;
    }
    encode(root-> left , str + '0', CodeHuffman);
    encode(root-> right , str + '1', CodeHuffman);
}

void decode(Node* root, int &index, string str){    // edesceodifica los simbolos codificados 
    if (root == nullptr){
        return; 
    }
    if (!root -> left && !root -> right ){

        cout<< root->symbol; 
        return;
    } 
    index++;
    if(str[index] == '0')
        decode(root-> left, index, str);
    else 
        decode(root-> right, index,str);

}

void createArbol(string text ){

    unordered_map<char, int> frequency;
    for(char symbol : text){
        frequency[symbol]++; 
    }

    priority_queue<Node* ,vector<Node*>, comp> pq; 
    
    for(auto pair : frequency ){ // agrega a la cola de prioridad los nodos de cada simbolo 

        pq.push(getNode(pair.first, pair.second, nullptr,nullptr));
        
    }

    while(pq.size() != 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        int sum = left -> frequency + right -> frequency;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    /// imprime los codigos para cada simblo 
    unordered_map<char, string> CodeHuffman;
    encode(root, "", CodeHuffman); 
    cout << "\n Los codigos de huffman \n" <<"\n";
    for(auto pair: CodeHuffman){
        cout << pair.first <<  " " <<  pair.second << "\n";
    }
    
    //-------------------------------------------------------------------------------- 

    cout << "\n el codigo original \n " << text <<"\n"; 
    string str = ""; 
    for(char symbol : text){
        str += CodeHuffman[symbol];
    }

    //--------------------------------------------------------------------------------


    cout << "\n el mensaje en binario es :  \n" << str << "\n";
    
    int index = -1; 
    cout << "\n el texto decodificado  es: \n"; 
    while (index < (int)str.size() -2 ){
        decode(root, index ,str);              // toma el codigo binario y de descomprime 

    } 
    cout << "\n";

    //str contiene el codigo binario  de la comprecion.    




}
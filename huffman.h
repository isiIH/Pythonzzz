#include <iostream>
#include <string> 
#include <queue> 
#include <unordered_map> 
#include <vector>

using namespace std;

struct Node{               // genera el tipo de dato node 
    char symbol;
    int frequency;
    Node *left, *right;
};

struct comp{                               // objeto que sirve para ordenar la cola (encuentra la frecuencia mas baja )
    bool operator()(Node* l, Node* r){
        return l -> frequency > r -> frequency;
    }
};

Node*  getNode(char symbol, int frequency,  Node *left , Node *right){  //asigna un nuevo  nodo al arbol 
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

void decode(Node* root,  string Binario, string &textodeco ){    // desceodifica los simbolos codificados 
    
    int index=0;

    Node* head=root;


    while(index<Binario.length())
    {  

         if(Binario[index]=='0')
         {
             head=head->left;
         }

         else{
             head=head->right;
         }


         if(head->left==nullptr && head->right==nullptr)
         {
             textodeco.push_back(head->symbol);
             head=root;
         }

         index++;
    }

}




int busquedaSecuencial(vector<Node> &F, int x){
	int i;
	for(i=0; i<F.size(); i++){
		if(x == F[i].symbol)
			return i;
	}
	return -1;
}


void imprimirSimbolos(vector<Node> &F){
    for (int i = 0; i < F.size(); i++){
        cout << "'" << F[i].symbol << "'\t" << F[i].frequency << "\t" << endl;
        
    }
    
}

void imprimirCodeHuffman(unordered_map<char,string> &CodeHuffman){
    cout << "\n Los codigos de Huffman: \n" <<"\n";
    for(auto pair: CodeHuffman){
        cout << pair.first <<  " " <<  pair.second << "\n";
    }

}

void codigoBinario(unordered_map<char,string> &CodeHuffman, string text, string *binario  ){
    //cout<< text<<endl;
    for(char symbol : text){
        *binario += CodeHuffman[symbol];
    }
    //cout << "\n El mensaje en binario es:  \n" << *binario << "\n";

}


void CuentaFrecuencia(vector<Node> &F, string text , Node &s){
    int indice;
    for(char c : text){
        indice = busquedaSecuencial(F,c);
        if(indice == -1){
            s.symbol = c;
            F.push_back(s);
        } else F[indice].frequency++;

        
    }
    
}



Node* GeneradorArbol(vector<Node> &F, priority_queue<Node* ,vector<Node*>, comp> &pq ){

    
    
    for(auto i : F ){ // agrega a la cola de prioridad los nodos de cada simbolo 
        
        pq.push(getNode(i.symbol, i.frequency, nullptr,nullptr));
                 // el tipo de caracter   // su freceuncia 
    }
    
    // repite el proceso hasta que haya mas de un nodo en cola
     
    while(pq.size() > 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        int sum = left -> frequency + right -> frequency;
        pq.push(getNode('\0', sum, left, right));
    }

    //crea la raiz para el arbol 
     Node* root = pq.top();

    return root; 

    
   
    
    
   


    
    
    
    
     
                    

    
  

        
    



}



#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
    char simbolo;
    double probabilidad = 0.0;
    string bitstream = ""; 
};

void obtenerProb(vector<Node> &v, string texto);
void encode(vector<Node> &v, int l, int r);
void particion(vector<Node> v, int *l, int *r, double lprob, double rprob);
void crearCodificado(vector<Node> v, string text);
void decode(vector<Node> v, string text);
void imprimirSimbolos(vector<Node> v);

void obtenerProb(vector<Node> &v, string texto){
    ifstream archivo;
    archivo.open("archivos/" + texto, ios::in);
    char letra;
    double total = 0.0;
    Node s;
    map<char,double> prob;
    map<char, double>::iterator fi;
    int i;

    if(archivo.fail()){
        cout << "Error" << endl;
        exit(1);
    }
    while(archivo >> noskipws >> letra){
        prob[letra]++;
        total++;
    }
    archivo.close();

    for(fi = prob.begin(), i = 0; fi != prob.end(); ++fi, ++i){
        s.simbolo = (*fi).first;
        s.probabilidad = (*fi).second / total;
        v.push_back(s);
    }
}

void encode(vector<Node> &v, int l, int r) {
    if(l<r){
        int x, y;
        x = l;
        y = r;
        particion(v, &l, &r, v[l].probabilidad, v[r].probabilidad);
        for(int i=x; i<=l; i++){
            v[i].bitstream += "1";
            // cout << v[i].bitstream << endl;
        }
        for(int i=r; i<=y; i++){
            v[i].bitstream += "0";
            // cout << v[i].bitstream << endl;
        }
        // cout << "l: " << l << ", r: " << r << endl;
        encode(v,x,l);
        encode(v,r,y);
    }
}

void particion(vector<Node> v, int *l, int *r, double lprob, double rprob){
    /* cout << *l << " " << *r << endl;
    cout << "lprob: " << lprob << endl;
    cout << "rprob: " << rprob << endl; */
    if(*l != *r-1){
        if(lprob > rprob){
            *r -= 1;
            rprob += v[*r].probabilidad;
        } else {
            *l += 1;
            lprob += v[*l].probabilidad;
        }
        particion(v,l,r,lprob,rprob);
    }
}

void crearCodificado(vector<Node> v, string text){
    ifstream archivo;
    ofstream archivoMod;
    archivo.open("archivos/" + text, ios::in);
    archivoMod.open("archivos/codificado.txt");
    char letra;

    if(archivo.fail()){
        cout << "Error" << endl;
        exit(1);
    }

    map<char, string> CodeShannon;
    for(int i=0; i<v.size(); i++){
        CodeShannon[v[i].simbolo] = v[i].bitstream;
    }

    while(archivo >> noskipws >> letra){
        archivoMod << CodeShannon[letra];
    }
    cout << "Se ha creado el archivo codificado" << endl;
    archivo.close();
    archivoMod.close();
}

void decode(vector<Node> v, string text){

}

void imprimirSimbolos(vector<Node> v){
    double suma = 0.0;
    for (int i = 0; i < v.size(); i++){
        cout << v[i].simbolo << " " << v[i].probabilidad << " " << v[i].bitstream << endl;
        suma = suma + v[i].probabilidad;
    }
    cout << "suma: " << suma << endl; 
}


#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Node {
    char simbolo;
    double probabilidad;
    int bitstream[]; 
};

vector<Node> obtenerProb(string texto){
    vector<Node> v;

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

    return v;
}

void particion(vector<Node> v, int *l, int *r, double lprob, double rprob){
    cout << *l << " " << *r << endl;
    cout << "rprob: " << rprob << endl;
    cout << "lprob: " << lprob << endl;
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

void imprimirSimbolos(vector<Node> v){
    double suma = 0.0;
    for (int i = 0; i < v.size(); i++){
        cout << v[i].simbolo << " " << v[i].probabilidad << endl;
        suma = suma + v[i].probabilidad;
    }
    cout << "suma: " << suma << endl; 
}


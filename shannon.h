#include <iostream>
#include <vector>
#include <string>
#include <map>
#include<algorithm>
using namespace std;

struct Node {
    char simbolo;
    double probabilidad;
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
    while(!archivo.eof()){
        archivo >> letra;
        prob[letra]++;
        total++;
    }
    archivo.close();

    for(fi = prob.begin(), i = 0; fi != prob.end(); ++fi, ++i){
        s.simbolo = (*fi).first;
        s.probabilidad = (*fi).second / total;
        v.push_back(s);
    }

    double suma = 0.0;
    for (i = 0; i < v.size(); i++){
        cout << v[i].simbolo << " " << v[i].probabilidad << endl;
        suma = suma + v[i].probabilidad;
    }
    cout << "suma: " << suma << endl; 

    return v;
}


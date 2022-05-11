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
void asignaCodigos(vector<Node> &v, int l, int r);
int particion(vector<Node> &v, int l, int r, double lprob, double rprob);
void encode(vector<Node> &v, string text);
void decode(vector<Node> &v, string text);
void imprimirSimbolos(vector<Node> &v);
int busquedaSecuencial(vector<Node> &v, int x);

void obtenerProb(vector<Node> &v, string texto){
    double total = 0.0;
/*     vector<Node> f(256); */
    int indice;
    Node s;

    for(char c : texto){
        if(int(c) < 256 && int(c)>=0){            
            indice = busquedaSecuencial(v,c);

            if(indice == -1){
                s.simbolo = c;
                s.probabilidad = 1;
                v.push_back(s);
            } else v[indice].probabilidad++;

            total++;
        }
    }

    for(int i=0; i<v.size(); i++) {
        v[i].probabilidad /= total;
    }

    /* for(char c : texto){
        if(int(c) < 256 && int(c)>=0){
            f[int(c)].simbolo = c;
            f[int(c)].probabilidad++;
            total++;
        }
    }

    for(Node sim : f){
        if(sim.probabilidad != 0){
            sim.probabilidad /= total;
            v.push_back(sim);
        }
    } */
}


void asignaCodigos(vector<Node> &v, int l, int r) {
    if(l<r){
        int p = particion(v, l, r, v[l].probabilidad, v[r].probabilidad);
        for(int i=l; i<=r; i++){
            if(i<=p){
                v[i].bitstream += "1";
            } else {
                v[i].bitstream += "0";
            }
        }
        asignaCodigos(v,l,p);
        asignaCodigos(v,p+1,r);
    }
}

int particion(vector<Node> &v, int l, int r, double lprob, double rprob){
/*     cout << l << " " << r << endl;
    cout << "lprob: " << lprob << endl;
    cout << "rprob: " << rprob << endl; */
    if(l != r-1){
        if(lprob > rprob){
            r -= 1;
            rprob += v[r].probabilidad;
        } else {
            l += 1;
            lprob += v[l].probabilidad;
        }
        return particion(v, l, r, lprob, rprob);
    }
    return l;
}

void encode(vector<Node> &v, string text){
    ofstream archivoMod;
    archivoMod.open("archivos/codificado.txt");
    int indice;

    for(char c : text){
        indice = busquedaSecuencial(v,c);
        archivoMod << v[indice].bitstream;
    }
    archivoMod.close();
    cout << "Se ha creado el archivo codificado" << endl;
}

void decode(vector<Node> &v, string texto){
    ofstream archivoMod;
    archivoMod.open("archivos/codificado.txt", ios::in);
    char letra;
    string codigo = "";

    map<char, string> CodeShannon;
    for(int i=0; i<v.size(); i++){
        CodeShannon[v[i].simbolo] = v[i].bitstream;
    }

    for(char c : texto){
        /*INSERTE CODIGO xd*/
        archivoMod << "xd";
    }
    archivoMod.close();
}

void imprimirSimbolos(vector<Node> &v){
    double suma = 0.0;
    for (int i = 0; i < v.size(); i++){
        cout << "'" << v[i].simbolo << "'\t" << v[i].probabilidad << "\t" << v[i].bitstream << endl;
        suma = suma + v[i].probabilidad;
    }
    cout << "suma: " << suma << endl; 
}

int busquedaSecuencial(vector<Node> &v, int x){
	int i;
	for(i=0; i<v.size(); i++){
		if(x == v[i].simbolo)
			return i;
	}
	return -1;
}

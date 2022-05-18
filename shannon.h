#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct Simbolo {
    char letra;
    double probabilidad = 1.0;
    string bitstream = "";
};

void obtenerProb(vector<Simbolo> &v, string texto);
void asignaCodigos(vector<Simbolo> &v, int l, int r);
int particion(vector<Simbolo> &v, int l, int r, double lprob, double rprob);
string encode(vector<Simbolo> &v, string text);
void decode(vector<Simbolo> &v, string texto);
void decode2(vector<Simbolo> &v, string texto, int k);
void imprimirSimbolos(vector<Simbolo> &v);
int busquedaSecuencial(vector<Simbolo> &v, int x);

void obtenerProb(vector<Simbolo> &v, string texto){
    double total = 0.0;
    int indice;
    Simbolo s;

    for(char c : texto){
        if(int(c) < 256 && int(c)>=0){            
            indice = busquedaSecuencial(v,c);

            if(indice == -1){
                s.letra = c;
                v.push_back(s);
            } else v[indice].probabilidad++;

            total++;
        }
    }

    /* for(char c : texto){
        if(int(c) < 256 && int(c)>=0){
            v[int(c)].simbolo = c;
            v[int(c)].probabilidad++;
            total++;
        }
    } */

    for(int i=0; i<v.size(); i++) {
        v[i].probabilidad /= total;
    }
}


void asignaCodigos(vector<Simbolo> &v, int l, int r) {
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

int particion(vector<Simbolo> &v, int l, int r, double lprob, double rprob){
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

string encode(vector<Simbolo> &v, string text){
    ofstream archivoMod;
    archivoMod.open("archivos/codificado.txt");
    int indice;
    string texto = "";

    for(char c : text){
        if(int(c) < 256 && int(c)>=0){
            indice = busquedaSecuencial(v,c);
            archivoMod << v[indice].bitstream;
            texto += v[indice].bitstream;
        }
    }

    archivoMod.close();
    cout << "Se ha creado el archivo codificado" << endl;
    return texto;
}

void decode(vector<Simbolo> &v, string texto){
    ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt");
    int l = 0;
    int i, r;

    while(l+v[0].bitstream.length() <= texto.length()) {
        i = 0;
        r = v[i].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl;  000010100*/
        while(texto.substr(l,r) != v[i].bitstream && i < v.size()-1) {
            /* cout << v[i].bitstream << endl; */
            i += 1;
            /* cout << i << endl; */
            if(v[i].bitstream.length() > v[i-1].bitstream.length()) {
                r++;
            } else if(v[i].bitstream.length() < v[i-1].bitstream.length()) {
                r--;
            }
        }

        archivoMod << v[i].letra;
        l += r;
    }
    archivoMod.close();
}

void decode2(vector<Simbolo> &v, string texto, int k) {
    if(k<0 || k>v.size()) return;

    ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt");
    int l = 0;
    int i, r;
    string textoDecod = "";

    while(textoDecod.length()!=k && l+v[0].bitstream.length() <= texto.length()) {
        i = 0;
        r = v[i].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl;  000010100*/
        while(texto.substr(l,r) != v[i].bitstream && i < v.size()-1) {
            /* cout << v[i].bitstream << endl; */
            i += 1;
            /* cout << i << endl; */
            if(v[i].bitstream.length() > v[i-1].bitstream.length()) {
                r++;
            } else if(v[i].bitstream.length() < v[i-1].bitstream.length()) {
                r--;
            }
        }

        archivoMod << v[i].letra;
        textoDecod += v[i].letra;
        l += r;
    }
    cout << textoDecod << endl;
    archivoMod.close();
}

void imprimirSimbolos(vector<Simbolo> &v){
    double suma = 0.0;
    for (int i = 0; i < v.size(); i++){
        cout << "'" << v[i].letra << "'\t" << v[i].probabilidad << "\t" << v[i].bitstream << endl;
        suma = suma + v[i].probabilidad;
    }
    cout << "suma: " << suma << endl; 
}

int busquedaSecuencial(vector<Simbolo> &v, int x){
	int i;
	for(i=0; i<v.size(); i++){
		if(x == v[i].letra)
			return i;
	}
	return -1;
}

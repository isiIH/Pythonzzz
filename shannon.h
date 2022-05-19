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

struct PosCodificado {
    char simbolo;
    int posInicial;
    int posFinal;
};

void obtenerProb(vector<Simbolo> &F, string texto);
void asignaCodigos(vector<Simbolo> &F, int l, int r);
int particion(vector<Simbolo> &F, int l, int r, double lprob, double rprob);
string encode(vector<Simbolo> &F, string text);
string encode2(vector<Simbolo> &F, vector<PosCodificado> &P, string text);
void decode(vector<Simbolo> &F, string texto);
void decode2(vector<Simbolo> &F, string texto, int k);
void decode3(vector<Simbolo> &F, vector<PosCodificado> &P, int i, int j, string texto);
void imprimirSimbolos(vector<Simbolo> &F);
void imprimirPosiciones(vector<PosCodificado> &P);
int busquedaSecuencial(vector<Simbolo> &F, int x);

void obtenerProb(vector<Simbolo> &F, string texto){
    double total = 0.0;
    int indice;
    Simbolo s;

    for(char c : texto){
        if(int(c) < 256 && int(c)>=0){            
            indice = busquedaSecuencial(F,c);

            if(indice == -1){
                s.letra = c;
                F.push_back(s);
            } else F[indice].probabilidad++;

            total++;
        }
    }

    /* for(char c : texto){
        if(int(c) < 256 && int(c)>=0){
            F[int(c)].simbolo = c;
            F[int(c)].probabilidad++;
            total++;
        }
    } */

    for(int i=0; i<F.size(); i++) {
        F[i].probabilidad /= total;
    }
}


void asignaCodigos(vector<Simbolo> &F, int l, int r) {
    if(l<r){
        int p = particion(F, l, r, F[l].probabilidad, F[r].probabilidad);
        for(int i=l; i<=r; i++){
            if(i<=p){
                F[i].bitstream += "1";
            } else {
                F[i].bitstream += "0";
            }
        }
        asignaCodigos(F,l,p);
        asignaCodigos(F,p+1,r);
    }
}

int particion(vector<Simbolo> &F, int l, int r, double lprob, double rprob){
/*     cout << l << " " << r << endl;
    cout << "lprob: " << lprob << endl;
    cout << "rprob: " << rprob << endl; */
    if(l != r-1){
        if(lprob > rprob){
            r -= 1;
            rprob += F[r].probabilidad;
        } else {
            l += 1;
            lprob += F[l].probabilidad;
        }
        return particion(F, l, r, lprob, rprob);
    }
    return l;
}

string encode(vector<Simbolo> &F, string text){
    ofstream archivoMod;
    archivoMod.open("archivos/codificado.txt");
    int indice;
    string texto = "";

    for(char c : text){
        if(int(c) < 256 && int(c)>=0){
            indice = busquedaSecuencial(F,c);
            archivoMod << F[indice].bitstream;
            texto += F[indice].bitstream;

        }   
    }

    archivoMod.close();
    cout << "Se ha creado el archivo codificado" << endl;
    return texto;
}

string encode2(vector<Simbolo> &F, vector<PosCodificado> &P, string text){
    ofstream archivoMod;
    archivoMod.open("archivos/codificado.txt");
    int indice;
    string texto = "";
    PosCodificado p;

    for(char c : text){
        if(int(c) < 256 && int(c)>=0){
            p.simbolo = c;
            p.posInicial = texto.length();

            indice = busquedaSecuencial(F,c);
            archivoMod << F[indice].bitstream;
            texto += F[indice].bitstream;

            p.posFinal = texto.length()-1;
            P.push_back(p);
        }   
    }

    archivoMod.close();
    cout << "Se ha creado el archivo codificado" << endl;
    return texto;
}

void decode(vector<Simbolo> &F, string texto){
    ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt");
    int l = 0;
    int i, r;

    while(l+F[0].bitstream.length() <= texto.length()) {
        i = 0;
        r = F[i].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl;  000010100*/
        while(texto.substr(l,r) != F[i].bitstream && i < F.size()-1) {
            /* cout << F[i].bitstream << endl; */
            i += 1;
            /* cout << i << endl; */
            if(F[i].bitstream.length() > F[i-1].bitstream.length()) {
                r++;
            } else if(F[i].bitstream.length() < F[i-1].bitstream.length()) {
                r--;
            }
        }

        archivoMod << F[i].letra;
        l += r;
    }
    archivoMod.close();
}

void decode2(vector<Simbolo> &F, string texto, int k) {
    if(k<0 || k>F.size()) return;

    ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt");
    int l = 0;
    int i, r;
    string textoDecod = "";

    while(textoDecod.length()!=k && l+F[0].bitstream.length() <= texto.length()) {
        i = 0;
        r = F[i].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl;  000010100*/
        while(texto.substr(l,r) != F[i].bitstream && i < F.size()-1) {
            /* cout << v[i].bitstream << endl; */
            i += 1;
            /* cout << i << endl; */
            if(F[i].bitstream.length() > F[i-1].bitstream.length()) {
                r++;
            } else if(F[i].bitstream.length() < F[i-1].bitstream.length()) {
                r--;
            }
        }

        archivoMod << F[i].letra;
        textoDecod += F[i].letra;
        l += r;
    }
    cout << textoDecod << endl;
    archivoMod.close();
}

void decode3(vector<Simbolo> &F, vector<PosCodificado> &P, int i, int j, string texto){
    ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt");

    if(i<1 || i>j || j>P.size()-1) {
        cout << "Posiciones i, j fuera de límite..." << endl;
        return;
    }

    texto = texto.substr(P[i].posInicial, P[j].posFinal - P[i].posInicial + 1);
    /* cout << texto << endl; */

    int l = 0;
    int x, r;

    while(l+F[0].bitstream.length() <= texto.length()) {
        x = 0;
        r = F[0].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl; */
        while(texto.substr(l,r) != F[x].bitstream && x < F.size()-1) {
            /* cout << F[x].letra << " " << F[x].bitstream << endl; */
            x += 1;
            /* cout << x << endl; */
            if(F[x].bitstream.length() > F[x-1].bitstream.length()) {
                r++;
            } else if(F[x].bitstream.length() < F[x-1].bitstream.length()) {
                r--;
            }
        }

        archivoMod << F[x].letra;
        /* cout << F[x].letra; */
        l += r;
    }
    /* cout << endl; */
    archivoMod.close();
}

void imprimirSimbolos(vector<Simbolo> &F){
    double suma = 0.0;
    for (int i = 0; i < F.size(); i++){
        cout << "'" << F[i].letra << "'\t" << F[i].probabilidad << "\t" << F[i].bitstream << endl;
        suma = suma + F[i].probabilidad;
    }
    cout << "suma: " << suma << endl; 
}

void imprimirPosiciones(vector<PosCodificado> &P){
    for (int i = 0; i < P.size(); i++){
        cout << "'" << P[i].simbolo << "'\t" << P[i].posInicial << " " << P[i].posFinal << endl;
    }
}

int busquedaSecuencial(vector<Simbolo> &F, int x){
	int i;
	for(i=0; i<F.size(); i++){
		if(x == F[i].letra)
			return i;
	}
	return -1;
}

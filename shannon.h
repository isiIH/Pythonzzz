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

string encode(vector<Simbolo> &F, string texto);
string encode2(vector<Simbolo> &F, vector<PosCodificado> &P, string texto);

string decode(vector<Simbolo> &F, string texto);
string decode2(vector<Simbolo> &F, string texto, int k, int u);
string decode3(vector<Simbolo> &F, vector<PosCodificado> &P, int i, int j, string texto);

void imprimirSimbolos(vector<Simbolo> &F);
void imprimirPosiciones(vector<PosCodificado> &P);

int busquedaSecuencial(vector<Simbolo> &F, int x);

void obtenerProb(vector<Simbolo> &F, string texto){
    double total = 0.0;
    int indice;
    Simbolo s;

    for(char c : texto){          
        indice = busquedaSecuencial(F,c);

        if(indice == -1){
            s.letra = c;
            F.push_back(s);
        } else F[indice].probabilidad++;

        total++;
    }

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

string encode(vector<Simbolo> &F, string texto){
    /* ofstream archivoMod;
    archivoMod.open("archivos/codificado.txt"); */
    int indice;
    string textoCod = "";

    for(char c : texto){
        indice = busquedaSecuencial(F,c);
        /* archivoMod << F[indice].bitstream; */
        textoCod += F[indice].bitstream;
    }

    /* archivoMod.close();
    cout << "Se ha creado el archivo codificado.txt" << endl; */
    return textoCod;
}

string encode2(vector<Simbolo> &F, vector<PosCodificado> &P, string texto){
    /* ofstream archivoMod;
    archivoMod.open("archivos/codificado.txt"); */
    int indice;
    string textoCod = "";
    PosCodificado p;

    for(char c : texto){
        p.simbolo = c;
        p.posInicial = textoCod.length();

        indice = busquedaSecuencial(F,c);
        /* archivoMod << F[indice].bitstream; */
        textoCod += F[indice].bitstream;

        p.posFinal = textoCod.length()-1;
        P.push_back(p);
    }

    /* archivoMod.close();
    cout << "Se ha creado el archivo codificado.txt" << endl; */
    return textoCod;
}

string decode(vector<Simbolo> &F, string texto){
    /* ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt"); */
    int l = 0;
    int i, r;
    string textoDecod = "";

    while(l+F[0].bitstream.length() <= texto.length()) {
        i = 0;
        r = F[i].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl; */
        while(texto.substr(l,r) != F[i].bitstream) {
            /* cout << F[i].bitstream << endl; */
            i += 1;
            /* cout << i << endl; */
            r = F[i].bitstream.length();
        }

        /* archivoMod << F[i].letra; */
        textoDecod += F[i].letra;
        l += r;
    }
    // cout << textoDecod << endl; 
    /* archivoMod.close();
    cout << "Se ha creado el archivo decodificado.txt" << endl; */

    return textoDecod;
}

string decode2(vector<Simbolo> &F, string texto, int k, int u) {
    if(k<0 || k>(u-1)) {
        cout << "Posición k fuera de rango..." << endl;
        return "";
    }

    /* ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt"); */
    int l = 0;
    int i, r;
    string textoDecod = "";

    while(textoDecod.length()-1 !=k) {
        i = 0;
        r = F[i].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl; */
        while(texto.substr(l,r) != F[i].bitstream) {
            /* cout << v[i].bitstream << endl; */
            i += 1;
            /* cout << i << endl; */
            r = F[i].bitstream.length();
        }

        /* archivoMod << F[i].letra; */
        textoDecod += F[i].letra;
        l += r;
    }
    /* cout << textoDecod << endl; */
    /* archivoMod.close();
    cout << "Se ha creado el archivo decodificado.txt" << endl; */

    return textoDecod;
}

string decode3(vector<Simbolo> &F, vector<PosCodificado> &P, int i, int j, string texto){
    if(i<1 || i>j || j>P.size()-1) {
        cout << "Posiciones i, j fuera de límite..." << endl;
        return "";
    }

    /* ofstream archivoMod;
    archivoMod.open("archivos/decodificado.txt"); */
    texto = texto.substr(P[i].posInicial, P[j].posFinal - P[i].posInicial + 1);
    /* cout << texto << endl; */

    int l = 0;
    int x, r;
    string textoDecod = "";

    while(l+F[0].bitstream.length() <= texto.length()) {
        x = 0;
        r = F[x].bitstream.length();
        /* cout << "l: " << l << " r: " << r << " " << texto.substr(l,r) << endl; */
        while(texto.substr(l,r) != F[x].bitstream) {
            /* cout << F[x].letra << " " << F[x].bitstream << endl; */
            x += 1;
            /* cout << x << endl; */
            r = F[x].bitstream.length();
        }

        /* archivoMod << F[x].letra; */
        textoDecod += F[x].letra;
        l += r;
    }

    /* cout << textoDecod << endl;  */

    /* archivoMod.close();
    cout << "Se ha creado el archivo decodificado.txt" << endl; */
    return textoDecod;
}

void imprimirSimbolos(vector<Simbolo> &F){
    double suma = 0.0;
    for (int i = 0; i < F.size(); i++){
        cout << "'" << F[i].letra << "'\t" << F[i].probabilidad << " \t " << F[i].bitstream << endl;
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

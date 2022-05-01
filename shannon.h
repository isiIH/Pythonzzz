
#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include <stdlib.h>

using namespace std;

class shannonF{


    struct Node
	{
		char symbol;
		float probability;
	};

    int tsize;
    Node *ptable;
    map<char, string> bits;

    public:
        
        void Encode(const char *text, const char *output){

            char symbol;
            float ftot;
            int i, total = 0; 
            ifstream inputData;
            inputData.open(text);
            if (inputData.is_open()){
                map<char, int> frequencyMap;
                while (inputData >> noskipws >> symbol){

                    frequencyMap[symbol]++;
                    total++;
                }
                //------------------------------------------------------------------------------------------------------
                tsize = (int)frequencyMap.size(); // // cantidad de signos distintos en el texto
                ptable = new Node[tsize];  // crea los nodos con la cantidad de signos que hay  en el texto
                ftot = float(total);
                map<char, int>::iterator fi;
                for (fi = frequencyMap.begin(), i = 0; fi != frequencyMap.end(); ++fi, ++i)
                {
                    ptable[i].symbol = (*fi).first; // agrega el simbolo al node 
                    ptable[i].probability = float((*fi).second) / ftot; //agrega con que frecuencia esta . 
                

                }

                for (i = 0; i < tsize; i++)
                {
                    cout << ptable[i].symbol << " " << ptable[i].probability << endl;
                }

            


            }else  
                cout << "Error" <<  endl;

        }
};






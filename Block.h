#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "TBData.h"
using namespace std;

class Block{
public:
    string blockHash;
    string prevHash;
    TBData data;
    int nonce = 1;

private:
    int index=0;
    string generateHash(){
        const int g = 31;
        const int top = 21;
        unsigned long long int hash = 1;
        string toHash = to_string(data.monto)+" "+
                         data.emisor+" "+data.receptor+" "+
                         to_string(data.fecha)+" "+this->prevHash+" "+
                         to_string(this->nonce);
        //funcion hash
        for(int i=0; i<toHash.size(); i++)
            hash = g*hash + toHash[i];//genera numeros de hasta 20 cifras

        string rhash = to_string(hash);
        string ceros;
        if(rhash.size() < top){
            for (int i = 0; i < (top-rhash.size()); ++i){
                ceros += "0";
            }
        }
        rhash = ceros+rhash;
        return rhash;
    }

public:
    Block() = default;

    Block(int i, TBData d, string preHash){
        index = i;
        data = d;
        prevHash = preHash;
        blockHash = generateHash();
    }
    int getIndex(){
        return index;
    }
    string getHash(){
        return blockHash;
    }

    string getPreviousHash(){
        return prevHash;
    }

    bool isHashValid(){
        return generateHash() == getHash();
    }
};

#endif //BLOCK_H

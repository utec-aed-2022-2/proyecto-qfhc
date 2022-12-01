#ifndef BLOCK
#define BLOCK
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdint>
#include "TBData.h"
#include "sha256.h"
#include "sha256.cpp"

using namespace std;

class Block {
    int64_t nonce=0; // from priv
    string blockHash; // to store hash of current block / from priv
    TBData* data; // to store data / from priv
    uint32_t index; // to store block number

    string generateHash(){
        stringstream hash;
        hash << index << data->monto << data->emisor 
        << data->receptor << data->fecha << prevHash << nonce;
        return sha256(hash.str());
    }
public:
    string prevHash; // to store hash of previous block
    Block() = default;
    Block(int i, TBData* &d){
        index = i;
        data = d;
        prevHash = "0";
        blockHash = generateHash();
    }
    void mineBlock(const uint32_t dif) {
        string cond;
        for(int i = 0; i < dif; ++i)
            cond += "0";

        do
        {
            nonce++;
            blockHash = generateHash();
        }
        while (blockHash.substr(0, dif) != cond);
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

    void printBlock(){
        cout<<"\n\nBlock\n===================================";
        cout<<"\nIndex: " << getIndex();
        cout<<"\nHash: " << getHash();
        cout<<"\nHash previo: " << getPreviousHash();
        data->print();
        cout<<"\nEl bloque es valido?: " << isHashValid() << endl;
        cout<<endl;
    }

};

/*
string Block::getHash() {
    return blockHash;
}



/////////////////////
void Block::Hash() {
    cout << "Hash: " << blockHash << endl;
}

void Block::Nonce() {
    cout << "Nonce: " << nonce << endl;
}

void Block::PrevHash() {
    // cout << "Prev Hash: " << prevHash << endl;
    if(prevHash == ""){
        cout << "Prev Hash: null" << endl;
    } else{
        cout << "Prev Hash: " << prevHash << endl;
    }
}

string Block::Data(){
    stringstream dat;
    dat << data.emisor << ";" << data.receptor << ";" 
    << to_string(data.monto) << ";" << data.fecha;
    return dat.str();
}
*/

#endif
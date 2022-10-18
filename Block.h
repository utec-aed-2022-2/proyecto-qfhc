#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdint>
#include "sha256.h"
#include "TBData.h"
using namespace std;

class Block{
public:
    string blockHash;
    string prevHash;
    TBData data;
    int nonce = 0;

private:
    int index=0;
    string generateHash(){
        stringstream hash;
        hash << index << to_string(data.monto) << data.emisor << data.receptor << data.fecha << prevHash << nonce;
        return sha256(hash.str());
    }

public:
    Block() = default;

    Block(int i, TBData d, string preHash){
        index = i;
        data = d;
        prevHash = preHash;
        blockHash = generateHash();
    }

    void mineBlock(int dif){
        string cond;
        for(int i = 0; i < dif; ++i){
            cond += "0";
        }

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

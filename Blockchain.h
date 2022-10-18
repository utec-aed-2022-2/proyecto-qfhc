#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>
#include "Double.h"

using namespace std;

class Blockchain{
private:
    Block createGenesisBlock(){
        time_t current;
        TBData d(0, "Genesis", "Genesis", fecha());

        Block genesis(0, d, "0");
        return genesis;
    }
    List<Block> *chain = new DoubleList<Block>();
    int dificulty = 2;

public:
    Blockchain(){
        Block genesis = createGenesisBlock();
        chain->push_back(genesis);
    }

    Block getLatestBlock(){
        return chain->back();
    }

    void addBlock(TBData &data){
        int index = (int)chain->size();
        string previousHash = (int)chain->size() > 0 ? getLatestBlock().getHash() : "0";
        Block newBlock(index, data, previousHash);
        newBlock.mineBlock(dificulty);
        chain->push_back(newBlock);
    }

    int chainSize(){
        return chain->size()-1;
    }

    void printChain(){
        for (auto it = chain->begin(); it != chain->end(); ++it){
            Block currentBlock = *it;
            if(currentBlock.getIndex()!=0){
                cout << "\n\nBlock\n===================================";
                cout << "\nIndex: " << currentBlock.getIndex();
                cout << "\nmonto: " << currentBlock.data.monto;
                cout << "\nemisor: " << currentBlock.data.emisor;
                cout << "\nreceptor: " << currentBlock.data.receptor;
                cout << "\nfecha: " << currentBlock.data.fecha;
                cout << "\nHash: " << currentBlock.getHash();
                cout << "\nHash previo: " << currentBlock.getPreviousHash();
                cout << "\nEl bloque es valido?: " << currentBlock.isHashValid() << endl;
            }
        }
    }
};

#endif 

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include "Double.h"
#include "block.h"

using namespace std;

class Blockchain {
    uint32_t dificult;    
    List<Block> *chain = new DoubleList<Block>();
public:
    Blockchain(){
        TBData* d = new TBData(0, "Genesis", "Genesis", fecha());
        chain->push_back(Block(0, d));
        dificult = 2;
    }

    void addBlock(Block newBlock){
        newBlock.prevHash = lastBlock().getHash();
        newBlock.mineBlock(dificult);
        chain->push_back(newBlock);
    }

    Block lastBlock(){
        return chain->back();
    }

    Block block_at(int id){
        return (*chain)[id];
    }

    int size(){
        return chain->size();
    }
  
};

#endif

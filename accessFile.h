#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "blockchain.h"
#include "AVLtree.h"

using namespace std;

TBData* constructData(string d){
    auto data = new TBData();
    char delimiter = ',';
    stringstream ss (d);
    string item;
    for(int i=0; i<4; ++i){
        getline (ss, item, delimiter);
        if(i==0)
            data->emisor=item;
        else if(i==1)
            data->receptor=item;
        else if(i==2)
            data->monto=stod(item);
        else if(i==3){
            data->fecha=stoull(item);
        }
    }
    return data;
}

int accessFileLogin(string filename, string userData){
    ofstream log;
    log.open(filename.c_str(), fstream::app);
    log << userData.c_str() << "\n";
    log.close();
    return 0;
}

int accessFileDB(string filename, string data){
    ofstream log;
    log.open(filename.c_str(), fstream::app);
    log << data.c_str() << "\n";
    log.close();
    return 0;
}

void loadFileDB(Blockchain* &blockchain, AVLTree<TBData*>* &avl,string filenameDB){
    ifstream fin(filenameDB);
    string data;
    auto tbd = new TBData();
    int id = 1;
    while(std::getline(fin, data)){
        tbd = constructData(data);
        blockchain->addBlock(Block(id, tbd));
        avl->genInsert(tbd);
        id++;
    }
    cout << "Base de datos cargada.\n" << endl;
}


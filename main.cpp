#include <cctype>
#include "displayMenu.h"
#include "login.h"

int main(){
     login("login.txt");
     auto blockchain = new Blockchain();
     auto mountIndex = new AVLTree<TBData*>(TBData_compare, TBData_print);
     loadFileDB(blockchain, mountIndex, "db.txt");
     displayMenu(blockchain, mountIndex, "db.txt");
     return 0;
}
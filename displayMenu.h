#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include "blockchain.h"
#include "block.h"
#include "accessFile.h"
#include "hash.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>

#include <sstream>
#include <vector>

using namespace std;

bool esEntero(string linea){
	bool esEntero = true;
	int longitud = linea.size();

	if(longitud == 0){
		esEntero = false;
	}else if (longitud == 1 && !isdigit(linea[0])) {
		esEntero = false;
	}else {
		int indice = 0;
		while (indice < longitud) {
			if (!isdigit(linea[indice])) {
				esEntero = false;
				break;
			}
			indice++;
		}
	}
  return esEntero;
}

void printMainMenu(){
  cout << "=======VENTAS=======" << endl;
  cout << "1. Ingresar una transacción." << endl; // Crear un nuevo bloque
  cout << "2. Mostrar última transacción." << endl; // Mostrar último bloque creado
  cout << "3. Mostrar todas las transacciones." << endl; // Mostrar cadena
  cout << "4. Buscar en transacciones por..." << endl;
  cout << "5. Salir." << endl;
  cout << "====================\n" << endl;
  cout << "Elegir una opción: ";
}

void printTransactionsMenu(){
  cout << "Buscar en transacciones por..." << endl;
  cout << "1. Ventas mayores a un monto." << endl; // Criterio de búsqueda
  cout << "2. Rango de ventas registradas." << endl; // Criterio de búsqueda
  cout << "3. Cantidad que compró un cliente." << endl; // Cálculo transaccional
  cout << "4. Cantidad de clientes que atendió un vendedor." << endl; // Cálculo transaccional
  cout << "5. Atrás." << endl;
  cout << "\n";
  cout << "Elegir una opción: ";
}

void displayMenu(Blockchain* &blockchain, AVLTree<TBData*>* &avl, string filenameDB, string filenameHASH){
    HashTable hash;
    string data = "";
    string dat = "";
    auto bdata = new TBData();

    string clientName = "";
    string sellerName = "";

    ifstream readFile(filenameDB);
    string _Client;
    string _Seller;
    double _Amount;
    string _Date;

    string line;
    string countString = "";
    double countAmount = 0;
    int count = 0;

    int id1 = 0;
    int id2 = 0;

    char ans;
    uint32_t id = blockchain->size();
    string option = "";
    int cases = 0;
    while(true){
        while(true){
          printMainMenu();
          getline(cin, option);
          cout << endl;
          if(esEntero(option)){
            cases = atoi(option.c_str());
            break;
          } else{
            cout<<"Ingrese un valor entero."<<endl;
          }
        }
        switch (cases){
          case 1: // Ingresar una transacción
              cout << "Ingresar datos de transacción #" << id << ".\n" << endl;
              cout << "Nombre del emisor: ";
              getline(cin, dat);
              data.append(dat+",");
              bdata->emisor=dat;
              cout << "Nombre del receptor: ";
              getline(cin, dat);
              data.append(dat+",");
              bdata->receptor=dat;
              cout << "Monto a transferir (en soles): ";
              getline(cin, dat);
              data.append(dat+",");
              bdata->monto=stod(dat);
              //cout << "Fecha de la venta (dd-mm-aa): ";
              //getline(cin, dat);
              dat=to_string(fecha());
              cout<<endl;
              //cout<<dat<<endl;
              data.append(dat);
              bdata->fecha=fecha();
              cout << "\n";

              blockchain->addBlock(Block(id, bdata));
              accessFileDB(filenameDB, data);
              accessFileHash(filenameHASH, blockchain->block_at(id).getHash());

              data = dat = "";
              cout << "\n";
              id++;
              break;
          case 2: // Mostrar última transacción
              if(id == 1){
                cout << "Aún no existen transacciones." << endl;
                cout << "\n";
                break;
              }
              cout << "La última transacción es la venta #" << id - 1 << ":" << endl;
              cout << blockchain->block_at(id - 1).getHash() << endl;
              cout << "\n";
              blockchain->block_at(id - 1).printBlock();
              break;
          case 3: // Mostrar todas las transacciones
              if(id == 1){
                cout << "Aún no existen transacciones." << endl;
                cout << "\n";
                break;
              } else{
                cout << "Historial de transacciones:" << endl;
                cout << "Hay " << blockchain->size() - 1 << " ventas registradas." << endl; // Sin contar genesis
                cout << "\n";
                for(int i = 1; i < id; i++){
                    cout << "Transacción #" << i << ":" << endl;
                    cout << blockchain->block_at(i).getHash() << endl;
                    cout << "\n";
                }
                break;
              }
          case 4: // Buscar en transacciones por...
            while(true){
              while(true){
                printTransactionsMenu();
                getline(cin, option);
                cout << "\n";
                if(esEntero(option)){
                  cases = atoi(option.c_str());
                  break;
                } else{
                  cout<<"Ingrese un valor entero."<<endl;
                }
                cout << "\n";
              }
              switch (cases){
                case 1: // Ventas mayores a un monto
                  cout << "Monto de referencia: ";
                  getline(cin,countString);
                  count = hash.searchMin(countString);
                  cout << "Hay " << count << " ventas registradas mayores a " << countString << endl;
                  break;

                case 2: // Rango de ventas registradas
                  cout << "Elegir el rango de ventas."<<endl;
                  cout << "Posición de inicio: ";
                  getline(cin,countString);
                  id1 = atoi(countString.c_str());
                  cout << "Posicion de fin: ";
                  getline(cin,countString);
                  id2 = atoi(countString.c_str()) + id1;
                  hash.searchRange(id1,id2);
                  
                  break;

                case 3: // Cantidad que compró un cliente
                  cout << "Nombre del cliente: ";
                  getline(cin,clientName);
                  countString = hash.searchClient(clientName);
                  cout << clientName << " compró en total S/" << countString << ".\n" << endl;
                  break;

                case 4: // Cantidad de clientes que atendió un vendedor
                  cout << "Nombre del vendedor: ";
                  getline(cin,sellerName);
                  count = hash.searchSeller(sellerName);
                  cout << sellerName << " atendió a " << count << " clientes.\n" << endl;
                  break;

                case 5:
                  break;
                default:
                  cout << "Ingresa una opción correcta.\n" << endl;
                  break;
              }
            }
          case 5: // Salir
              return;
          default:
              cout << "Ingresa una opción correcta.\n" << endl;
              break;
      }
    }
}
#endif
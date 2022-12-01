#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include "blockchain.h"
#include "block.h"
#include "accessFile.h"
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
  cout << "========MENU========" << endl;
  cout << "1. Ingresar una transacción." << endl; // Crear un nuevo bloque
  cout << "2. Mostrar última transacción." << endl; // Mostrar último bloque creado
  cout << "3. Mostrar todas las transacciones." << endl; // Mostrar cadena
  cout << "4. Buscar en transacciones por..." << endl;
  cout << "5. Salir." << endl;
  cout << endl;
  cout << "Elegir una opción: ";
}

void printTransactionsMenu(){
  cout << "Buscar en transacciones por..." << endl;
  cout << "1. Transacciones con monto igual a X." << endl; // Criterio de búsqueda
  cout << "2. Transacciones con montos entre X y Y." << endl; // Criterio de búsqueda
  cout << "3. Transaccion con el mayor monto." << endl; // Cálculo transaccional
  cout << "4. Transaccion con el menor monto." << endl; // Cálculo transaccional
  cout << "5. Salir." << endl;
  cout << endl;
  cout << "Elegir una opción: ";
}

void displayMenu(Blockchain* &blockchain, AVLTree<TBData*>* &avl, string filenameDB){
    string data = "";
    string dat = "";
    auto bdata = new TBData();
    auto ref1 = new TBData();
    auto ref2 = new TBData();

    string line;
    string refMount;

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
              dat=to_string(fecha());
              cout<<endl;
              data.append(dat);
              bdata->fecha=fecha();
              cout << "\n";

              blockchain->addBlock(Block(id, bdata));
              accessFileDB(filenameDB, data);

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
              blockchain->lastBlock().printBlock();
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
                case 1:
                  cout << "Monto a buscar: ";
                  getline(cin, refMount);
                  ref1->monto = stod(refMount);
                  avl->genFind(ref1);
                  break;

                case 2: // Rango de ventas registradas
                  cout << "Montos mayores a: ";
                  getline(cin, refMount);
                  ref1->monto = stod(refMount);
                  cout << "Y menores a: ";
                  getline(cin,refMount);
                  ref2->monto = stod(refMount);
                  avl->genRangeSearch(ref1, ref2);
                  
                  break;

                case 3: // Cantidad que compró un cliente
                  cout << "La transaccion con el mayor monto es: ";
                  avl->maxValue()->print();
                  break;

                case 4: // Cantidad de clientes que atendió un vendedor
                  cout << "La transaccion con el menor monto es: ";
                  avl->minValue()->print();
                  break;

                case 5:
                  return;
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
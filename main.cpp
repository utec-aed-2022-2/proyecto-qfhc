#include <iostream>
#include <ctime>
#include "Blockchain.h"

using namespace std;

void Menu(){
    Blockchain aurora;
    int option = 0;
    string emisor;
    string receptor;
    double monto=0;
    //time_t dataTime;
    TBData data;
    while(true){
        while(true){
            cout << "********** Blockchain Aurora **********" << endl;
            cout << "1 -> Nueva transacción" << endl;
            cout << "2 -> Transacciones realizadas" << endl;
            cout << "3 -> Ultima transaccion" << endl;
            cout << "4 -> Salir" << endl;
            cout << "***************************************" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cout << endl;
            if(option > 4){
                cout<<"Ingrese un valor valido"<<endl;
            }
            else
                break;
        }
        //auto f = new time_t;
        switch (option){
            case 1: // Ingresar una transacción
                cout << "Nombre del emisor: ";
                cin >> emisor;
                cout << "Nombre del receptor: ";
                cin >> receptor;
                cout << "Monto a transferir: ";
                cin >> monto;
                cout << endl;

                data.emisor=emisor;
                data.receptor=receptor;
                data.monto=monto;
                data.fecha=fecha();
                aurora.addBlock(data);
                cout << endl;
                break;
            case 2:
                 if(aurora.getLatestBlock().prevHash == "0"){
                    cout << "No existen transacciones." << endl;
                    cout << endl;
                    break;
                }
                cout << "Total de transacciones: "<< aurora.chainSize() << endl;
                cout << endl;
                aurora.printChain();
                break;
            case 3:
                if(aurora.getLatestBlock().prevHash == "0"){
                    cout << "No existen transacciones" << endl;
                    cout << endl;
                    break;
                }
                cout << "Ultima transacción: "<< endl;
                aurora.getLatestBlock().printBlock();
                cout << endl;
                break;
            case 4:
                return;
            default:
                cout << "Ingrese una opcion valida." << endl;
                cout << endl;
                break;
        }
    }
}


int main(){

    Menu();

    return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include "displayMenu.h"

using namespace std;

void login(string filenameLogin){
    string line = " ";    
    ifstream readFile(filenameLogin);
    string Username;
    string Password;
    string _UserName;
    string _Password;
    string userData;

    string option = "";
    int cases = 0;
    bool found = false;

    while(true){
        while(true){
            cout << "=======LOGIN=======" << endl;
            cout << "1. Ya tengo una cuenta." << endl;
            cout << "2. Crear una cuenta nueva." << endl;
            cout << "3. Salir." << endl;
            cout << "====================\n" << endl;
            cout << "Elegir una opción: ";
            getline(cin, option);
            cout << endl;
            if(esEntero(option)){  
                cases = atoi(option.c_str());
                break;
            } else{
                cout<<"Ingrese un valor entero.\n"<<endl;
            }
        }
        switch (cases){
            case 1: // Ya tengo una cuenta
                cout << "Usuario: ";
                getline(cin, Username);
                cout << "Contraseña: ";
                getline(cin, Password);
                found = false;
                while(getline(readFile,line)){
                    stringstream iss(line);
                    iss >> _UserName >> _Password;
                    if (Username == _UserName && Password == _Password){
                        cout << "Bienvenid@!\n"<< endl;
                        found = true;
                        return;
                    }
                }
                if(!found){
                cout << "Usuario y/o contraseña incorrecto(s).\n"<< endl;
                break;
                }

            case 2: // Crear una cuenta nueva
                cout << "Crea un nuevo usuario: ";
                getline(cin, Username);

                while(!found && getline(readFile,line)){
                    stringstream iss(line);
                    iss >> _UserName >> _Password;
                    if (Username == _UserName){
                        found = true;
                        cout << "El usuario ya existe."<< endl;
                        cout << "Crea un nuevo usuario: ";
                        getline(cin, Username);
                        // _UserName = "";
                        break;
                    }
                }

                userData.append(Username+" ");
                cout << "Crea una nueva contraseña: ";
                getline(cin, Password);
                userData.append(Password);
                accessFileLogin(filenameLogin, userData);
                userData = "";
                cout << "Usuario creado!\n" << endl;
                break;

            case 3:
                return;

            default:
              cout << "Ingresa una opción correcta.\n" << endl;
              break;
        }
    }
}
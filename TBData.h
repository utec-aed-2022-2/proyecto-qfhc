#ifndef PROYECTO_HORA_DE_SALVAR_EL_CURSO_TBDATA_H
#define PROYECTO_HORA_DE_SALVAR_EL_CURSO_TBDATA_H

#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

string fecha(){
  time_t f = time(nullptr);
  string fe;
  char dat[40];
  strftime(dat, 30, "%c %Z", localtime(&f));
  fe=dat;
  return fe;
}

struct TBData{

    double monto=0;
    string emisor;
    string receptor;
    string fecha;

    TBData(){}

    TBData(double amt, string sender, string reciever, string time){
        monto = amt;
        emisor = sender;
        receptor = reciever;
        fecha = time;
    }
};

#endif //PROYECTO_HORA_DE_SALVAR_EL_CURSO_TBDATA_H

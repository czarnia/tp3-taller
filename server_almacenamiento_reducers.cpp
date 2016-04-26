#include "server_almacenamiento_reducers.h"
#include "server_lock.h"

#include <sstream>
#include <string>
#include <iostream>
#include <ostream>

#include <stdlib.h>

//--------------->Auxiliares<-----------//
std::vector<int> obtener_claves(std::map<int,Reduce*> hash){
  std::vector<int> v;
  std::map<int,Reduce*>::iterator i;
  for (i = hash.begin(); i != hash.end(); i++){
    v.push_back(i->first);
  }
  return v;
}
//-------------------------------------//

Almacenamiento_reducers::Almacenamiento_reducers(){
  std::map<int, Reduce*> hilos_reduce;
}

Almacenamiento_reducers::~Almacenamiento_reducers(){
  std::vector<int> claves_reduce = obtener_claves(hilos_reduce);
  for (size_t i = 0; i < claves_reduce.size(); i++){
    Reduce* r = hilos_reduce[claves_reduce[i]];
    hilos_reduce.erase(claves_reduce[i]);
    delete r;
  }
}

void Almacenamiento_reducers::agregar_temperatura(char* cadena){
  std::istringstream cadena_parseada(cadena);
  std::string ciudad, temperatura, dia;

  cadena_parseada >> dia >> ciudad >> temperatura;
  int temp = atoi(temperatura.c_str());
  int d = atoi(dia.c_str());

  Registro clave_valor = Registro(ciudad, temp, d);

  Lock candado(proteccion);
  if (hilos_reduce[d] == NULL){
    std::cout << "agrego un reduce \n";
    hilos_reduce[d] =  new Reduce();
  }
  (*hilos_reduce[d]).agregar_registro(clave_valor);
}

std::map<int, Reduce*> Almacenamiento_reducers::devolver_hilos(){
  return hilos_reduce;
}

void Almacenamiento_reducers::ejecutar_reduce(){
  std::map<int,Reduce*>::iterator i;
  std::cout << hilos_reduce.size() << "holi \n";
  for (i = hilos_reduce.begin(); i != hilos_reduce.end(); i++){
    std::cout << hilos_reduce.size() <<"holi (2)\n";
    (*(i->second)).start();
    std::cout << hilos_reduce.size() <<"holi (2-1)\n";
  }
  for (i = hilos_reduce.begin(); i != hilos_reduce.end(); i++){
    std::cout << hilos_reduce.size() << "holi (3)\n";
    (*(i->second)).join();
  }
  std::cout << "holi (4)\n";
}

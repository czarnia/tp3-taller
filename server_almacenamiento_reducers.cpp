#include "server_almacenamiento_reducers.h"
#include "server_lock.h"

#include <sstream>
#include <string>
#include <iostream>
#include <ostream>

#include <stdlib.h>

#include <vector>
#include <map>

#define CANT_DIAS 31
/*
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
*/
Almacenamiento_reducers::Almacenamiento_reducers(){
  std::cout << "creo un almacenamiento \n";
  std::vector<Reduce*> hilos_reduce;
  for (size_t i = 0; i < CANT_DIAS; i++){
    Reduce* nuevo_hilo = new Reduce();
    hilos_reduce.push_back(nuevo_hilo);
  }
  std::cout << "tam hilos luego de ser creados: " << hilos_reduce.size() << "\n";
}

Almacenamiento_reducers::~Almacenamiento_reducers(){
  //std::vector<int> claves_reduce = obtener_claves(hilos_reduce);
  std::cout << "estoy borrando mis reducers !! \n";
  for (size_t i = 0; i < CANT_DIAS; i++){
    Reduce* r = hilos_reduce[i];
    hilos_reduce.erase(hilos_reduce.begin()+i);
    delete r;
  }
}

void Almacenamiento_reducers::agregar_temperatura(char* cadena){
  std::istringstream cadena_parseada(cadena);
  std::string ciudad, temperatura, dia;

  cadena_parseada >> dia >> ciudad >> temperatura;
  int temp = atoi(temperatura.c_str());
  int d = atoi(dia.c_str());

  std::cout << "estoy agregando una temperatura \n";

  Registro clave_valor = Registro(ciudad, temp, d);

  Lock candado(proteccion);
  std::cout << "tam hilos: " << hilos_reduce.size() << "dia a agregar: " << d << "\n";
  /*if (hilos_reduce[d-1] == NULL){
    Reduce* nuevo_hilo = new Reduce();
    hilos_reduce.insert(hilos_reduce.begin()+(d-1), nuevo_hilo);
  }*/
  (*hilos_reduce[d-1]).agregar_registro(clave_valor);
}

std::vector<Reduce*> Almacenamiento_reducers::devolver_hilos(){
  return hilos_reduce;
}

void Almacenamiento_reducers::ejecutar_reduce(){
  int i = 0;
  while (i < CANT_DIAS){
    for (int j = i; j < i + 4; j++){
      (*hilos_reduce[j]).start();
    }
    for (int j = i; j < i + 4; j++){
      (*hilos_reduce[j]).join();
    }
    i+=4;
    std::cout << "estoy en el while mi amigo \n";
  }

}

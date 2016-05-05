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

Almacenamiento_reducers::Almacenamiento_reducers(){
  for (size_t i = 0; i < CANT_DIAS; i++){
    Reduce* nuevo_hilo = new Reduce();
    hilos_reduce.push_back(nuevo_hilo);
  }
}

Almacenamiento_reducers::~Almacenamiento_reducers(){
  for (size_t i = 0 ; i < CANT_DIAS; i++){
    Reduce* r = hilos_reduce.back();
    hilos_reduce.pop_back();
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
  (*hilos_reduce[d-1]).agregar_registro(clave_valor);
}

std::vector<Reduce*> Almacenamiento_reducers::devolver_hilos(){
  Lock candado(proteccion);
  return hilos_reduce;
}

void Almacenamiento_reducers::ejecutar_reduce(){
  int i = 0;
  while (i < CANT_DIAS){
    for (int j = i; (j < i + 4) && (j < CANT_DIAS); j++){
      (*hilos_reduce[j]).start();
    }
    for (int j = i; (j < i + 4) && (j < CANT_DIAS); j++){
      (*hilos_reduce[j]).join();
    }
    i+=4;
  }
}

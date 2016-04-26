#include "server_procesador_servidor.h"
#include "server_conexion_cliente.h"
#include "server_reduce.h"
#include "server_salida_maximos.h"

#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <ostream>

#include <stdlib.h>


Procesador_servidor::Procesador_servidor(){
  std::vector<Conexion_cliente*> clientes;
  reducers = new Almacenamiento_reducers();
}

Procesador_servidor::~Procesador_servidor(){
  size_t tam_clientes = clientes.size();
  for (size_t i = 0 ; i < tam_clientes; i++){
    Conexion_cliente* cliente = clientes.back();
    clientes.pop_back();
    delete cliente;
  }
  delete reducers;
}

void Procesador_servidor::agregar_cliente(Conexion_cliente* cliente){
  //std::cout << "Cant de hilos: (agr_cliente pre)" << hilos_reduce.size() << "\n";
  //std::cout << "Agregue a un cliente! \n";
  (*cliente).start();
  clientes.push_back(cliente);
  //std::cout << "Cant de hilos: (agr_cliente post)" << hilos_reduce.size() << "\n";
}

void Procesador_servidor::agregar_temperatura(char* cadena){
  (*reducers).agregar_temperatura(cadena);
}

bool Procesador_servidor::clientes_terminaron(){
  for (size_t i = 0; i < clientes.size(); i++){
    if (!(*clientes[i]).termino()){
      //std::cout << "No terminaron, idiota \n";
      return false;
    }
  }
  //std::cout << "terminaron \n";
  return true;
}

void Procesador_servidor::join(){
  //std::cout << "hago un joiiinn \n";
  bool terminaron = false;
  while (!terminaron){
    terminaron = clientes_terminaron();
  }
  //std::cout << "los clientes terminaron \n";
  for (size_t i = 0; i < clientes.size(); i++){
    (*clientes[i]).join();
  }
  (*reducers).ejecutar_reduce();
  return;
}

void Procesador_servidor::imprimir_resultados(){
  std::map<int,Reduce*> hilos_reduce = (*reducers).devolver_hilos();
  //std::cout << "Cant de hilos (imprimir): " << hilos_reduce.size() << "\n";
  Salida_maximos salida = Salida_maximos();
  std::map<int,Reduce*>::iterator i;
  for (i = hilos_reduce.begin(); i != hilos_reduce.end(); i++){
    std::vector<Registro> maximos_dia = (*(i->second)).devolver_maximos();
    std::cout << salida.to_string(maximos_dia);
  }
}

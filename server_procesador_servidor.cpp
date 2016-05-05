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
  (*cliente).start();
  clientes.push_back(cliente);
}

void Procesador_servidor::agregar_temperatura(char* cadena){
  (*reducers).agregar_temperatura(cadena);
}

void Procesador_servidor::join(){
  for (size_t i = 0; i < clientes.size(); i++){
    (*clientes[i]).join();
  }
  (*reducers).ejecutar_reduce();
  return;
}

void Procesador_servidor::imprimir_resultados(){
  std::vector<Reduce*> hilos_reduce = (*reducers).devolver_hilos();
  Salida_maximos salida = Salida_maximos();
  for (size_t i = 0; i < hilos_reduce.size(); i++){
    std::vector<Registro> maximos_dia = (*hilos_reduce[i]).devolver_maximos();
    std::cout << salida.to_string(maximos_dia);
  }
}

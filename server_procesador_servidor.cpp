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
  //std::map<int,Reduce*> hilos_reduce = reducers.devolver_hilos();

  /*std::vector<int> claves_reduce = obtener_claves(hilos_reduce);
  for (size_t i = 0; i < claves_reduce.size(); i++){
    Reduce* r = hilos_reduce[claves_reduce[i]];
    hilos_reduce.erase(claves_reduce[i]);
    delete r;
  }*/
  size_t tam_clientes = clientes.size();
  for (size_t i = 0 ; i < tam_clientes; i++){
    //Conexion_cliente* cliente = clientes.back();
    clientes.pop_back();
    //delete cliente;
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
  //std::cout << "Agrego una temperatura! \n";
  /*std::istringstream cadena_parseada(cadena);
  std::string ciudad, temperatura, dia;

  cadena_parseada >> dia >> ciudad >> temperatura;
  int temp = atoi(temperatura.c_str());
  int d = atoi(dia.c_str());

  Registro clave_valor = Registro(ciudad, temp, d);

  if (hilos_reduce[d] == NULL){
    std::cout << "agrego un reduce \n";
    hilos_reduce[d] =  new Reduce();
  }
  (*hilos_reduce[d]).agregar_registro(clave_valor);
  std::cout << "Cant de hilos: (agregar)" << hilos_reduce.size() << "\n";*/
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
  /*for (i = hilos_reduce.begin(); i != hilos_reduce.end(); i++){
    (*(i->second)).start();
  }
  for (i = hilos_reduce.begin(); i != hilos_reduce.end(); i++){
    (*(i->second)).join();
  }*/
  for (i = hilos_reduce.begin(); i != hilos_reduce.end(); i++){
    std::vector<Registro> maximos_dia = (*(i->second)).devolver_maximos();
    std::cout << salida.to_string(maximos_dia);
  }
}

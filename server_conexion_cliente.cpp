#include "server_conexion_cliente.h"
#include "common_socket.h"
#include <string>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <sstream>
#include <iostream>

#define FIN_ENTRADA "End"
#define EN_ESPERA " "
#define FIN_BUFFER '\n'
#define TAM_FIN 1

#define MAX_TAM_BUFFER 70 //Se considera como maximo el pueblo de
//"Llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch" cuyo nombre tiene
//59 caracteres.

Conexion_cliente::Conexion_cliente(Socket* conexion, Procesador_servidor* srv)
:skt(conexion){
  server = srv;
  fin = false;
}

Conexion_cliente::~Conexion_cliente(){
  delete skt;
}

void Conexion_cliente::ejecutar(){
  char buffer[MAX_TAM_BUFFER];
  if ((*skt).receive(buffer, MAX_TAM_BUFFER, FIN_BUFFER, TAM_FIN) < 0){
      std::cout << "-1 al recibir \n";
  }
  while (strcmp(buffer, FIN_ENTRADA) != 0){
    if (strcmp(buffer, EN_ESPERA) != 0){
      (*server).agregar_temperatura(buffer);
    }
    strncpy(buffer, EN_ESPERA, MAX_TAM_BUFFER);
    if ((*skt).receive(buffer, MAX_TAM_BUFFER, FIN_BUFFER, TAM_FIN) < 0){
        std::cout << "-1 al recibir \n";
    }
  }
  (*skt).shutdown(SHUT_RDWR);
  fin = true;
  return;
}

bool Conexion_cliente::termino(){
  return fin;
}

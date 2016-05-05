#include "server_accept.h"
#include "common_socket.h"
#include "server_conexion_cliente.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>


#define MAX_CONEXIONES 4

Accept::Accept(char* puerto, Procesador_servidor* srv){
  fin = false;
  server = srv;
  skt = new Socket(NULL, puerto);

  (*skt).bind(NULL, puerto);
  (*skt).listen(MAX_CONEXIONES);
}

Accept::~Accept(){
  delete skt;
  delete server;
}

void Accept::terminar(){
  fin = true;
  (*skt).shutdown(SHUT_RDWR);
}

void Accept::ejecutar(){
  while (!fin){
    Socket* aceptado = (*skt).accept(NULL);
    if (aceptado == NULL && fin){
      return;
    }
    Conexion_cliente* nueva_conexion = new Conexion_cliente(aceptado, server);
    (*server).agregar_cliente(nueva_conexion);
  }
}

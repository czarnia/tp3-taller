#include "server_accept.h"
#include "common_socket.h"
#include "server_conexion_cliente.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

//#define CONEXIONES 5

Accept::Accept(Socket& conexion_server, Procesador_servidor& srv)
:skt(conexion_server){
  fin = false;
  server = srv;
}

Accept::~Accept(){}

void Accept::terminar(){
  fin = true;
  skt.shutdown(SHUT_RDWR);
}

void Accept::ejecutar(){
  while (!fin){
    int nuevo_skt = skt.accept(NULL);
    if(nuevo_skt < 0 && fin){
      return;
    }
    Socket* aceptado = new Socket(NULL, NULL, nuevo_skt);
    Conexion_cliente* nueva_conexion = new Conexion_cliente(aceptado, server);
    server.agregar_cliente(nueva_conexion);
  }
}

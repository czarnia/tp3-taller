#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

#include "common_socket.h"
#include "server_procesador_servidor.h"
#include "server_accept.h"


int main(int argc, char *argv[]){
  std::string linea_actual;
  char* puerto = argv[1];

  Procesador_servidor* server = new Procesador_servidor();

  Accept aceptador = Accept(puerto, server);
  aceptador.start();

  std::getline(std::cin,linea_actual);
  while (linea_actual.compare("q") != 0){
    std::getline(std::cin,linea_actual);
  }

  aceptador.terminar();
  aceptador.join();

  (*server).join();
  (*server).imprimir_resultados();

  //delete aceptador;
  return 0;
}

#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

#include "common_socket.h"
#include "server_procesador_servidor.h"
#include "server_accept.h"

#define MAX_CONEXIONES 10

int main(int argc, char *argv[]){
  std::string linea_actual;
  char* puerto = argv[1];

  std::cout << "entro al server \n";
  Procesador_servidor* server = new Procesador_servidor();

  Socket* conexion = new Socket(NULL, puerto);
  std::cout << "creo un socket \n";

  (*conexion).bind(NULL, puerto);
  (*conexion).listen(MAX_CONEXIONES);
  std::cout << "socket procesado \n";

  Accept* aceptador = new Accept(conexion, server);
  (*aceptador).start();
  std::cout << "lanze al aceptador \n";

  std::getline(std::cin,linea_actual);
  while (linea_actual.compare("q") != 0){
    std::getline(std::cin,linea_actual);
  }
  std::cout << "recibí el q \n";

  (*aceptador).terminar();
  (*aceptador).join();

  std::cout << "hice join del aceptador \n";
  (*server).join();
  std::cout << "hice join del server \n";
  (*server).imprimir_resultados();

  delete aceptador;
  return 0;
}

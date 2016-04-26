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
  //std::cout << "Servidor \n";
  std::string linea_actual;
  char* puerto = argv[1];
  //std::cout << puerto << "\n";

  Procesador_servidor* server = new Procesador_servidor();

  Socket* conexion = new Socket(NULL, puerto);

  (*conexion).bind(NULL, puerto);
  (*conexion).listen(MAX_CONEXIONES);

  /*int nuevo_skt = (*conexion).accept(NULL);
  if(nuevo_skt < 0){
    return -1;
  }
  Socket* aceptado = new Socket(NULL, NULL, nuevo_skt);

  char buffer[10];

  (*aceptado).receive(buffer, 10, '\n', 1);
  std::cout << "Recibi: " << buffer << "fin \n";
  strncpy(buffer, "", 10);
  (*aceptado).receive(buffer, 10, '\n', 1);
  std::cout << "Recibi(2): " << buffer << "fin(2) \n";
  */

  Accept* aceptador = new Accept(*conexion, *server);
  (*aceptador).start();

  std::cout <<"Cree y lanze el aceptado \n";

  std::getline(std::cin,linea_actual);
  std::cout << "Estoy en el while, mi línea es(0): " << linea_actual << "\n";
  while (linea_actual.compare("q") != 0){
    std::cout << "Estoy en el while, mi línea es(1): " << linea_actual << "\n";
    std::getline(std::cin,linea_actual);
    std::cout << "Estoy en el while, mi línea es(2): " << linea_actual << "\n";
  }

  std::cout << "Salgo del while \n";

  (*aceptador).terminar();
  (*aceptador).join();
  (*server).join();
  //(*server).imprimir_resultados();

  std::cout << "joinie \n";

  //delete aceptador;
  delete conexion;
  //delete server;

  return 0;
}

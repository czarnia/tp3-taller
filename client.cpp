#include "client_procesador_cliente.h"
#include "common_socket.h"
#include "common_registro.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  std::cout << "Cliente \n";

  Procesador_cliente procesador = Procesador_cliente();
  char* id = argv[1];
  char* puerto = argv[2];
  //std::cout << id << " " << puerto << "\n";
  Socket* cliente = new Socket(NULL, puerto);

  //Me conecto al servidor
  if ((*cliente).conect(id, puerto) < 0){
    std::cout << "Problema en conect \n";
    printf("%s \n", strerror(errno));
    return 0;
  }

  /*cliente.send("Hola \n", strlen("Hola \n"));
  cliente.send("Chau \n", strlen("Chau \n"));*/
  std::string linea_actual;

  while (std::getline(std::cin,linea_actual) && linea_actual != ""){
    std::cout << linea_actual << "\n";
    Registro clave_valor = procesador.devolver_clave_valor(linea_actual);
    procesador.enviar_clave_valor(clave_valor, *cliente);
  }
  procesador.enviar_fin(*cliente);

  //delete cliente;
  return 0;
}

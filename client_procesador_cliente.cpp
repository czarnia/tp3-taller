#include "client_procesador_cliente.h"
#include "common_par.h"
#include "common_socket.h"

#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIN_SEND "\n"
#define FIN "End\n"

Registro Procesador_cliente::devolver_clave_valor(std::string cadena){
  std::istringstream cadena_parseada(cadena);
  std::string nombre, temperatura, dia;

  cadena_parseada >> nombre >> temperatura >> dia;
  int temp = atoi(temperatura.c_str());
  int d = atoi(dia.c_str());

  Registro clave_valor = Registro(nombre, temp, d);

  return clave_valor;
}

void Procesador_cliente::enviar_clave_valor(Registro kv, Socket& skt){
  std::string registro = kv.to_string();
  const char* registro_env = registro.c_str();
  //std::cout << "Envio: " << registro_env << "\n";
  size_t tam = strlen(registro_env);
  if (registro_env == NULL){
    std::cout << "uya! \n";
  }
  skt.send(registro_env, tam);
  skt.send(FIN_SEND, strlen(FIN_SEND));
}

void Procesador_cliente::enviar_fin(Socket& skt){
  //std::cout << "Envio: " << FIN << "\n";
  skt.send(FIN, strlen(FIN));
}

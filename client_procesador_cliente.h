#ifndef PROCESADOR_CLIENTE
#define PROCESADOR_CLIENTE

#include "common_registro.h"
#include "common_socket.h"
#include <string>

class Procesador_cliente{
  public:
    Registro devolver_clave_valor(std::string cadena);
    void enviar_clave_valor(Registro kv, Socket skt);
    void enviar_fin(Socket skt);
};

#endif //PROCESADOR_CLIENTE

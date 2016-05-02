#ifndef PROCESADOR_CLIENTE
#define PROCESADOR_CLIENTE

#include "common_registro.h"
#include "common_socket.h"
#include <string>

class Procesador_cliente{
  public:
    //Dada una cadena, devuelve un registro con su informacion.
    Registro devolver_clave_valor(std::string cadena);
    //Dado un registro y un socket previamente conectado a un servidor,
    //envia la informacion del primero.
    void enviar_clave_valor(Registro kv, Socket& skt);
    //Dado un socket previamente conectado a un servidor, envia una señal de fin
    //al segundo.
    void enviar_fin(Socket& skt);
};

#endif //PROCESADOR_CLIENTE

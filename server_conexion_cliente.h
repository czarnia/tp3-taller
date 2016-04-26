#ifndef CONEXION_CLIENTE_H
#define CONEXION_CLIENTE_H

#include "server_hilo.h"
#include "common_socket.h"
#include "server_procesador_servidor.h"
//#include <queue>

//class Proceso_servidor;

class Conexion_cliente : public Hilo{
  private:
    Socket* skt;
    bool fin;
    Procesador_servidor* server;
  public:
    Conexion_cliente(Socket* conexion, Procesador_servidor* srv);
    ~Conexion_cliente();
    void ejecutar();
    bool termino();
};

#endif //CONEXION_CLIENTE_H

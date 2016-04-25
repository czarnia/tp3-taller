#ifndef ACCEPT_H
#define ACCEPT_H

#include "server_hilo.h"
#include "common_socket.h"
#include "server_procesador_servidor.h"

//class Proceso_servidor;

class Accept: public Hilo{
  private:
    Socket skt;
    bool fin;
    Procesador_servidor server;
  public:
    Accept(Socket& conexion_server, Procesador_servidor& svr);
    ~Accept();
    void terminar();
    virtual void ejecutar();
};

#endif //ACCEPT_H

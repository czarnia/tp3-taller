#ifndef ACCEPT_H
#define ACCEPT_H

#include "server_hilo.h"
#include "common_socket.h"
#include "server_procesador_servidor.h"

//class Proceso_servidor;

class Accept: public Hilo{
  private:
    Socket* skt;
    bool fin;
    Procesador_servidor* server;
  public:
    //Dado un puerto y un procesador_servidor, crea un accept.
    Accept(char* puerto, Procesador_servidor* svr);
    //Destruye un Accept.
    ~Accept();
    //Le notifica al accept que debe dejar de aceptar conexiones entrantes.
    void terminar();
    //Recibe conexiones entrantes.
    virtual void ejecutar();
};

#endif //ACCEPT_H

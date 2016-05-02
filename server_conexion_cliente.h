#ifndef CONEXION_CLIENTE_H
#define CONEXION_CLIENTE_H

#include "server_hilo.h"
#include "common_socket.h"
#include "server_procesador_servidor.h"

class Conexion_cliente : public Hilo{
  private:
    Socket* skt;
    bool fin;
    Procesador_servidor* server;
  public:
    //Dado un socket y un procesador_servidor, crea una conexion_cliente.
    Conexion_cliente(Socket* conexion, Procesador_servidor* srv);
    //Destruye una conexion_cliente.
    ~Conexion_cliente();
    //Recibe datos de un socket hasta encontrarse con una señal de fin.
    void ejecutar();
    //Pregunta si se termino de recibir.
    bool termino();
};

#endif //CONEXION_CLIENTE_H

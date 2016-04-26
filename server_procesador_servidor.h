#ifndef PROCESADOR_SERVIDOR_H
#define PROCESADOR_SERVIDOR_H

//#include "server_reduce.h"
#include "server_almacenamiento_reducers.h"

#include <vector>
#include <map>
#include <string>

class Conexion_cliente;

class Procesador_servidor{
  private:
    std::vector<Conexion_cliente*> clientes;
    Almacenamiento_reducers* reducers;

  public:
    Procesador_servidor();
    ~Procesador_servidor();
    void agregar_cliente(Conexion_cliente* cliente);
    void agregar_temperatura(char* temperatura);
    void join();
    void imprimir_resultados();
  private:
    bool clientes_terminaron();
};

#endif // PROCESADOR_SERVIDOR_H

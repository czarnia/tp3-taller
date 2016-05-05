#ifndef PROCESADOR_SERVIDOR_H
#define PROCESADOR_SERVIDOR_H

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
    //Crea un procesador_servidor.
    Procesador_servidor();
    //Destruye un procesador_servidor.
    ~Procesador_servidor();
    //Dada una conexion_cliente*, lo agrega al servidor.
    void agregar_cliente(Conexion_cliente* cliente);
    //Dada una cadena, que representa una temperatura, la agrega a su hilo
    //reduce correspondiente.
    void agregar_temperatura(char* temperatura);
    //Ejecuta a los reducers.
    void join();
    //Imprime los resultados de los reducers, habiendolos ejecutado antes.
    void imprimir_resultados();
};

#endif // PROCESADOR_SERVIDOR_H

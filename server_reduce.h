#ifndef REDUCE_H
#define REDUCE_H

#include "server_hilo.h"
#include "common_registro.h"
#include <queue>
#include <string>
#include <vector>

//class Proceso_servidor;

class Reduce : public Hilo{
  private:
    std::priority_queue<Registro> temperaturas;
    std::vector<Registro> maximos;
  public:
    //Crea un reduce.
    Reduce();
    //Destruye un reduce.
    ~Reduce();
    //Agrega un registro a los datos del reduce.
    void agregar_registro(Registro& registro);
    //Ejecuta al reduce.
    void ejecutar();
    //Devuelve los registros maximos.
    std::vector<Registro> devolver_maximos();
};

#endif //REDUCE_H

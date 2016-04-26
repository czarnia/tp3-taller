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
    std::priority_queue<int> temperaturas;
    std::vector<int> maximos;
  public:
    Reduce();
    ~Reduce();
    void agregar_registro(Registro& registro);
    void ejecutar();
    std::vector<int> devolver_maximos();
};

#endif //REDUCE_H

#ifndef ALMACENAMIENTO_REDUCERS_H
#define ALMACENAMIENTO_REDUCERS_H

#include "server_mutex.h"
#include "server_reduce.h"

#include <map>

class Almacenamiento_reducers{
  private:
    Mutex proteccion;
    std::map<int, Reduce*> hilos_reduce;

  public:
    Almacenamiento_reducers();
    ~Almacenamiento_reducers();
    void agregar_temperatura(char* cadena);
    std::map<int, Reduce*> devolver_hilos();
    void ejecutar_reduce();
};

#endif //ALMACENAMIENTO_REDUCERS_H

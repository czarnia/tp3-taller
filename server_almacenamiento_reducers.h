#ifndef ALMACENAMIENTO_REDUCERS_H
#define ALMACENAMIENTO_REDUCERS_H

#include "server_mutex.h"
#include "server_reduce.h"

#include <vector>

class Almacenamiento_reducers{
  private:
    Mutex proteccion;
    std::vector<Reduce*> hilos_reduce;

  public:
    //Crea un almacenamiento_reducers.
    Almacenamiento_reducers();
    //Destruye un almacenamiento_reducers.
    ~Almacenamiento_reducers();
    //Dada una cadena, la procesa y agrega una temperatura a su reducer
    //correspondiente.
    void agregar_temperatura(char* cadena);
    //Devuelve los reducers guardados en un vector.
    std::vector<Reduce*> devolver_hilos();
    //Lanza los hilos reduce y les hace join.
    void ejecutar_reduce();
};

#endif //ALMACENAMIENTO_REDUCERS_H

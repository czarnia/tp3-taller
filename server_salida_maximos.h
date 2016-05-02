#ifndef SALIDA_MAXIMOS_H
#define SALIDA_MAXIMOS_H

#include "common_registro.h"
#include <string>
#include <vector>

class Salida_maximos{
  public:
    //Da una representacion de string a un vector de registros.
    std::string to_string(std::vector<Registro> maximos);
};

#endif //SALIDA_MAXIMOS_H

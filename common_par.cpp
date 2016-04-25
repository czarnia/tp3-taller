#include "common_par.h"
#include <string>

Par::Par(std::string key, std::string value){
  clave = key;
  valor = value;
}

std::string Par::devolver_clave(){
  return clave;
}

std::string Par::devolver_valor(){
  return valor;
}

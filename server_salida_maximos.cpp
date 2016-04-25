#include "server_salida_maximos.h"
#include <string>
#include <vector>
#include <sstream>

std::string Salida_maximos::to_string(std::vector<Registro> maximos){
  std::stringstream ss;
  ss << maximos[0].get_dia() << ": ";
  for (size_t i = 0; i < maximos.size(); i++){
    ss << maximos[i].get_ciudad() << " ";
  }
  ss << maximos[0].get_temperatura() << "\n";
  return ss.str();
}

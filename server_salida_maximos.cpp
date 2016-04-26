#include "server_salida_maximos.h"
#include <string>
#include <vector>
#include <sstream>
#include <set>

std::set<std::string> ciudades_maximas(std::vector<Registro> maximos){
  std::set<std::string> ciudades;
  for (size_t i = 0; i < maximos.size(); i++){
    ciudades.insert(maximos[i].get_ciudad());
  }
  return ciudades;
}

std::string Salida_maximos::to_string(std::vector<Registro> maximos){
  std::stringstream ss;
  std::set<std::string> ciudades = ciudades_maximas(maximos);

  ss << maximos[0].get_dia() << ": ";

  std::set<std::string>::iterator i;
  for (i = ciudades.begin(); i != ciudades.end(); i++){
    if (i != ciudades.begin()){
      ss << "/";
    }
    ss << *i;
  }

  /*for (size_t i = 0; i < maximos.size(); i++){
    ss << maximos[i].get_ciudad() << " ";
  }*/
  ss << " (" << maximos[0].get_temperatura() << ")\n";
  return ss.str();
}

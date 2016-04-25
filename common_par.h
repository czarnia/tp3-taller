#ifndef PAR_H
#define PAR_H

#include <string>

class Par{
  private:
    std::string clave;
    std::string valor;
  public:
    Par(std::string key, std::string value);
    std::string devolver_clave();
    std::string devolver_valor();
};

#endif // PAR_H

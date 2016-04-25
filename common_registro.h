#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

class Registro{
  private:
    std::string ciudad;
    int temperatura;
    int dia;
  public:
    Registro(std::string nombre, int temp, int d);
    ~Registro();
    std::string get_ciudad();
    int get_temperatura();
    int get_dia();
    bool operator==(const Registro& otro) const;
    bool operator<(const Registro& otro) const;
    bool operator>(const Registro& otro) const;
    bool operator!=(const Registro& otro) const;
    std::string to_string();
};

#endif // REGISTRO_H

#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

class Registro{
  private:
    std::string ciudad;
    int temperatura;
    int dia;
  public:
    //Dado un string (nombre ciudad), una temperatura y un dia, crea un
    //registro.
    Registro(std::string nombre, int temp, int d);
    //Destruye un registro.
    ~Registro();
    //Devuelve la ciudad del registro.
    std::string get_ciudad();
    //Devuelve la temperatura del registro.
    int get_temperatura();
    //Devuelve el dia del registro.
    int get_dia();

    /*Comparadores*/
    bool operator==(const Registro& otro) const;
    bool operator<(const Registro& otro) const;
    bool operator>(const Registro& otro) const;
    bool operator!=(const Registro& otro) const;
    /**/

    //Devuelve la representacion en string del registro.
    std::string to_string();
};

#endif // REGISTRO_H

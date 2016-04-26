#include "common_registro.h"
#include <string>
#include <sstream>


Registro::Registro(std::string nombre, int temp, int d){
  ciudad = nombre;
  temperatura = temp;
  dia = d;
}

Registro::~Registro(){}

std::string Registro::get_ciudad(){
  return ciudad;
}

int Registro::get_temperatura(){
  return temperatura;
}

int Registro::get_dia(){
  return dia;
}

bool Registro::operator==(const Registro& otro) const{
  return ((*this).temperatura == otro.temperatura);
}

bool Registro::operator<(const Registro& otro) const{
  return ((*this).temperatura < otro.temperatura);
}

bool Registro::operator>(const Registro& otro) const{
  return !((*this) < otro);
}

bool Registro::operator!=(const Registro& otro) const{
  return !((*this) == otro);
}

std::string Registro::to_string(){
  std::stringstream ss;
  ss << dia << " " << ciudad << " " << temperatura;
  std::string str = ss.str();
  return str;
}

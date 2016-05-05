#include "server_reduce.h"
#include <vector>

#include <sstream>
#include <string>
#include <iostream>
#include <ostream>

Reduce::Reduce(){
  std::vector<Registro> maximos;
}

void Reduce::agregar_registro(Registro& valor){
  temperaturas.push(valor);
}

void Reduce::ejecutar(){
  Registro valor1 = temperaturas.top();
  temperaturas.pop();
  maximos.push_back(valor1);
  while (!temperaturas.empty()){
    Registro valor2 = temperaturas.top();
    temperaturas.pop();
    if (valor1 == valor2){
      maximos.push_back(valor2);
    }else{
      return;
    }
    valor1 = valor2;
  }
}

std::vector<Registro> Reduce::devolver_maximos(){
  return maximos;
}

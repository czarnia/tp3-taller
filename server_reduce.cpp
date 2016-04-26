#include "server_reduce.h"
#include <vector>

#include <sstream>
#include <string>
#include <iostream>
#include <ostream>

Reduce::Reduce(){
  std::vector<Registro> maximos;
}

Reduce::~Reduce(){}

void Reduce::agregar_registro(Registro& valor){
  temperaturas.push(valor);
}

void Reduce::ejecutar(){
  //std::cout << "entro al ejecutar \n";
  Registro valor1 = temperaturas.top();
  //std::cout << "hice top \n";
  temperaturas.pop();
  //std::cout << "hice pop \n";
  maximos.push_back(valor1);
  //std::cout << "primer push-back\n";
  while (!temperaturas.empty()){
    Registro valor2 = temperaturas.top();
    //std::cout << "hice top (while) \n";
    temperaturas.pop();
    //std::cout << "hice pop (while)\n";
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

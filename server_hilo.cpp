#include "server_hilo.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

void Hilo::start() {
    if (pthread_create(&hilo, NULL, Hilo::ejecutor, this) == 0){
      //std::cout << "uya, 0 \n";
    }
    //std::cout << "Entro al start \n";
}

void Hilo::join() {
    std::cout << "Hago join! \n";
    pthread_join(hilo, NULL);
    std::cout << "akakal \n";
}

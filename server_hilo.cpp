#include "server_hilo.h"

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

void Hilo::start() {
  pthread_create(&hilo, NULL, Hilo::ejecutor, this);
}

void Hilo::join() {
    pthread_join(hilo, NULL);
}

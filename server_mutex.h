#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex {
  private:
    pthread_mutex_t mutex;
  public:
    //Crea un mutex.
    Mutex();
    //Destruye un mutex.
    ~Mutex();
    //Hace un lock (protege a una operacion de race condition).
    void lock();
    //Hace un unlock (determina el fin de la zona protegida de race condition).
    void unlock();
  private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);
};

#endif //MUTEX_H

#ifndef LOCK_H
#define LOCK_H

#include "server_mutex.h"

class Lock {
  private:
    Mutex &m;
  public:
    //Crea un lock.
    explicit Lock(Mutex &m);
    //Destruye un lock.
    ~Lock();
};

#endif //LOCK_H

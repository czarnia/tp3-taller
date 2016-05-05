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
  private:
    Lock(const Lock&);
    Lock& operator=(const Lock&);
};

#endif //LOCK_H

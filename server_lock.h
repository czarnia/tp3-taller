#ifndef LOCK_H
#define LOCK_H

#include "server_mutex.h"

class Lock {
  private:
    Mutex &m;

  public:
    explicit Lock(Mutex &m);
    ~Lock();
};

#endif //LOCK_H

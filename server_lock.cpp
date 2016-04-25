#include <pthread.h>
#include "server_lock.h"

Lock::Lock(Mutex &m) : m(m) {
  m.lock();
}

Lock::~Lock() {
  m.unlock();
}

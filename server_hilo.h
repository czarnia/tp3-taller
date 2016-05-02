#ifndef HILO_H
#define HILO_H
#include <pthread.h>

class Hilo {
    private:
        pthread_t hilo;
        static void *ejecutor(void *data){
            Hilo* self = (Hilo*) data;
            self->ejecutar();
            return data;
        }

    public:
      //Destruye un hilo.
      virtual ~Hilo() {}
      //Define la funcion que ejecutara un hilo.
      virtual void ejecutar() = 0;
      //Lanza al hilo.
      void start();
      //Hace un join al hilo.
      void join();
};

#endif //HILO_H

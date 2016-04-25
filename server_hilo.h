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
        virtual ~Hilo() {}
        virtual void ejecutar() = 0;
        void start();
        void join();
};

#endif //HILO_H

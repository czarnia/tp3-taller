#ifndef SOCKET_H
#define SOCKET_H

#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


class Socket{
  private:
    int skt;
  public:
    Socket(char* puerto, char* ip, int sktc = -1);
    ~Socket();
    int shutdown(int como);
    int listen(int conexiones);
    int bind(char* id, char* puerto);
    int accept(struct sockaddr* dir_cliente);
    int conect(char* ip, char* puerto);
    int receive(char* buffer, size_t tam_max, const char fin_buffer,
    size_t tam_fin);
    int send(const char* buffer, size_t tamanio);

  private:
    struct addrinfo* iniciar_addrinfo(char* ip, char* puerto);
    int rcv(char* buffer, size_t tamanio);
};

#endif // SOCKET_H

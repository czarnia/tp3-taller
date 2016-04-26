#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>

#include <netdb.h>

#include "common_socket.h"
#include <stdlib.h>

#include <cstdlib>
#include <sstream>
#include <iostream>

Socket::Socket(char* puerto, char* ip, int sktc){
  if (sktc > 0){
    this->skt = sktc;
  }else{
    struct addrinfo* addr = iniciar_addrinfo(ip, puerto);
    this->skt = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    freeaddrinfo(addr);
  }
}

Socket::~Socket(){
  //(*this).shutdown(SHUT_RDWR);
  close(this->skt);
}


int Socket::shutdown(int como){
  return ::shutdown(this->skt, como);
}


int Socket::listen(int conexiones){
  return ::listen(this->skt, conexiones);
}


int Socket::bind(char* ip, char* puerto)
/*(struct sockaddr* direccion, int tamanio)*/{
  struct addrinfo* addr = iniciar_addrinfo(ip, puerto);
  int b = ::bind(this->skt, addr->ai_addr, addr->ai_addrlen);
  freeaddrinfo(addr);
  return b;
}


/*Socket* Socket::accept(struct sockaddr* dir_cliente){
  socklen_t tam_addr = sizeof(dir_cliente);
  int nuevo_socket = ::accept(this->skt, dir_cliente, &tam_addr);
  return new Socket(NULL, NULL, nuevo_socket);
}*/

int Socket::accept(struct sockaddr* dir_cliente){
  socklen_t tam_addr = sizeof(dir_cliente);
  int nuevo_socket = ::accept(this->skt, dir_cliente, &tam_addr);
  return nuevo_socket;
}

int Socket::conect(char* ip, char* puerto){
  struct addrinfo* server = iniciar_addrinfo(ip, puerto);
  int c = ::connect(this->skt, server->ai_addr, server->ai_addrlen);
  freeaddrinfo(server);
  return c;
}

/*int Socket::receive(char* buffer, size_t tam_max, const char* fin_buffer,
size_t tam_fin){
  size_t tam_actual = 0; //el tamaño total de lo que ya recibí.
  int tam_rcv = 0; //el tamaño de lo que recibo en cada ciclo.
  const char* fin_actual = "";

  std::cout << "Recibo \n";
  while ((strcmp(fin_actual, fin_buffer) != 0) || (tam_actual < tam_max)){
    std::cout << "Fin actual(1): " << fin_actual;
    int dif_tam = tam_max-tam_actual;
    tam_rcv = ::recv(this->skt, &buffer[tam_actual], dif_tam, MSG_NOSIGNAL);
    if (tam_rcv <= 0){
      std::cout << "Uya, no recibi!"<< "\n";
      return -1;
    }
    tam_actual += tam_rcv;
    fin_actual = buffer + (tam_actual -  tam_fin);
    //std::cout << "Buffer(rcv): " << buffer << "\n";
    std::cout << "Fin actual(2): " << fin_actual;
  }
  std::cout << "Buffer(rcv): " << buffer << "\n";
  return tam_actual;
}*/

int Socket::receive(char* buffer, size_t tam_max, const char fin_buffer,
size_t tam_fin){
  size_t tam_actual = 0;
  size_t tam_rcv = 0;
  while (tam_actual < tam_max){
    tam_rcv = rcv(&buffer[tam_actual],1);
    if (tam_rcv <= 0){
      std::cout << "Uya, no recibi!"<< "\n";
      return -1;
    }
    tam_actual += tam_rcv;
    //std::cout << "Recibido " << buffer << "\n";
    if (buffer[tam_actual-1] == '\n'){
      //std::cout << "Buffer(rcv): " << buffer << "\n";
      buffer[tam_actual-1] = '\0';
      //std::cout << "tam: " << tam_actual << "\n";
      return tam_actual;
    }
  }
  buffer[tam_actual-1] = '\0';
  //std::cout << "tam: " << tam_actual << "\n";
  return tam_actual;
}

int Socket::rcv(char* buffer, size_t tamanio){
  size_t tam_actual = 0; //el tamaño total de lo que ya recibí.
  int tam_rcv = 0; //el tamaño de lo que recibo en cada ciclo.

  while (tam_actual < tamanio){
    int dif_tam = tamanio-tam_actual;
    tam_rcv = ::recv(this->skt, &buffer[tam_actual], dif_tam, MSG_NOSIGNAL);
    if (tam_rcv <= 0){
      return -1;
    }
    tam_actual += tam_rcv;
  }

  return tam_actual;
}


int Socket::send(const char* buffer, size_t tamanio){
  //std::cout << "Envio un: " << buffer;
  size_t tam_actual = 0; //el tamaño total de lo que ya envié.
  int tam_send = 0; //el tamaño de lo que envio en cada ciclo.

  while (tam_actual < tamanio){
    int dif_tam = tamanio-tam_actual;
    tam_send = ::send(this->skt, &buffer[tam_actual], dif_tam, MSG_NOSIGNAL);
    if (tam_send <= 0){
      return -1;
    }
    tam_actual += tam_send;
  }

  return tam_actual;
}

struct addrinfo* Socket::iniciar_addrinfo(char* ip, char* puerto){
  struct addrinfo hints;
  struct addrinfo* server;
  // = (struct addrinfo*) malloc(sizeof(struct addrinfo));

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(ip, puerto, &hints, &server);

  return server;
}

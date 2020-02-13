#ifndef ALTALIBRERIA_CONNECTIONS_H_
#define ALTALIBRERIA_CONNECTIONS_H_

#define MAX_CONN 40
#define null NULL

#include <arpa/inet.h>
#include <commons/collections/list.h>
#include <commons/bitarray.h>
#include <commons/config.h>
#include <commons/log.h>
#include <commons/string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <limits.h>
#include <dirent.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/syscall.h>
//#include <readline/readline.h>
//#include <readline/history.h>
#include "structures.h"

int client_socket_array[MAX_CONN];

typedef struct t_thread_client {
	int socket;
	char * client_ip;
	int connection_port;
	void (*lost_connection)(int, char*, int);
	void (*incoming_message)(int, char*, int,MessageHeader*);
}t_thread_client;

/**
 *
 * @return
 */
int create_socket();

/**
 *
 * @param socket
 * @param port
 * @return
 */
int bind_socket(int socket, int port);

/**
 *
 * @param socket
 * @param IP
 * @param port
 * @return
 */
int connect_socket(int socket, char * IP, int port);

/**
 *
 * @param socket
 * @return
 */
int close_socket(int socket);

/**
 *
 * @param destination
 * @param type
 * @param data_size
 * @param data_stream
 * @return
 */
int send_data(int destination, MessageType type, int data_size, void * data_stream);

/**
 *
 * @param source
 * @param buffer
 * @return
 */
int receive_header(int source, MessageHeader * buffer);

/**
 *
 * @param source
 * @param buffer
 * @param data_size
 * @return
 */
int receive_data(int source, void * buffer, int data_size);

/**
 *
 * @param socket
 * @param new_connection
 * @param lost_connection
 * @param incoming_message
 * @return
 */
int start_server(int socket,
    void (*new_connection)(int fd, char * ip, int port),
    void (*lost_connection)(int fd, char * ip, int port),
    void (*incoming_message)(int fd, char * ip, int port, MessageHeader * header));

/**
 *
 * @param tipo
 * @return
 */
t_paquete* create_package(MessageType tipo);

/**
 *
 * @param paquete
 * @param valor
 * @param tamanio
 */
void add_to_package(t_paquete* paquete, void* valor, int tamanio);

/**
 *
 * @param paquete
 * @param socket_cliente
 * @return
 */
int send_package(t_paquete* paquete, int socket_cliente);

/**
 *
 * @param paquete
 * @param bytes
 * @return
 */
void* serialize_package(t_paquete* paquete, int bytes);

/**
 *
 * @param paquete
 */
void free_package(t_paquete* paquete);

/**
 *
 * @param socket_cliente
 * @param header
 * @return
 */
t_list* receive_package(int socket_cliente, MessageHeader *header);

/**
 *
 * @param params
 * @return
 */
void* server_client(void* params);

/**
 *
 * @param socket
 * @param new_connection
 * @param lost_connection
 * @param incoming_message
 * @return
 */
int start_multithread_server(int socket, void (*new_connection)(int fd, char *ip, int port),
    void (*lost_connection)(int fd, char *ip, int port),
    void (*incoming_message)(int fd, char *ip, int port, MessageHeader *header));
#endif

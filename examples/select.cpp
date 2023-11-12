#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <memory>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string>
#include <map>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <signal.h>
#include <poll.h>
#include <termios.h>
#include "fcntl.h"

int main() {
    int listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int flags = fcntl(listen_socket_fd, F_GETFL);

    fcntl(listen_socket_fd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listen_socket_fd, (struct sockaddr *) &addr, sizeof(addr));
    listen(listen_socket_fd, 100);

    for (;;) {
        int client_socket_fd = accept(listen_socket_fd, NULL, NULL);
        if (client_socket_fd == -1) {
        if (errno == EWOULDBLOCK) {
            printf("No pending connections; sleeping for one second.\n");
            sleep(1);
        } else {
            perror("error when accepting connection");
            exit(1);
        }
        } else {
        char msg[] = "hello\n";
        printf("Got a connection; writing 'hello' then closing.\n");
        send(client_socket_fd, msg, sizeof(msg), 0);
        close(client_socket_fd);
        }
  }
    
}
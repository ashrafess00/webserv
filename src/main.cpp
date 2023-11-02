
#include "webserv.hpp"

int main(int argc, char const *argv[])
{
    int opt = 1;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error creating socket" << '\n';
        return EXIT_FAILURE;
    }
    // -----------------------------------------------------
    // this solve the error of error binding by reusing address and port
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(1);
    }
    // -----------------------------------------------------
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Error binding socket" << '\n';
        close(server_socket);
        return EXIT_FAILURE;
    }
    // -----------------------------------------------------
    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "Error listening on socket" << '\n';
        close(server_socket);
        return EXIT_FAILURE;
    }
    // -----------------------------------------------------
    std::cout << "Server is listening on 0.0.0.0:8080" << '\n';
    // -----------------------------------------------------
    while (1)
    {
        sockaddr client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(server_socket, &client_addr, &client_addr_len);
        ft_handle_client(client_fd);
    }
    // -----------------------------------------------------
    return 0;
}

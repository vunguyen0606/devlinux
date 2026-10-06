#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9000

int main(void)
{
    int sockfd;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t client_len =
        sizeof(client_addr);

    char buffer[128];

    sockfd =
        socket(AF_INET,
               SOCK_DGRAM,
               0);

    if (sockfd < 0)
    {
        perror("socket");
        return 1;
    }

    memset(&server_addr,
           0,
           sizeof(server_addr));

    server_addr.sin_family =
        AF_INET;

    server_addr.sin_addr.s_addr =
        INADDR_ANY;

    server_addr.sin_port =
        htons(PORT);

    if (bind(sockfd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr))
        < 0)
    {
        perror("bind");
        return 1;
    }

    printf("[RECEIVER] Listening on port %d\n",
           PORT);

    while (1)
    {
        memset(buffer,
               0,
               sizeof(buffer));

        recvfrom(sockfd,
                 buffer,
                 sizeof(buffer),
                 0,
                 (struct sockaddr *)&client_addr,
                 &client_len);

        printf("[RECEIVER] Received: %s\n",
               buffer);
    }

    close(sockfd);

    return 0;
}

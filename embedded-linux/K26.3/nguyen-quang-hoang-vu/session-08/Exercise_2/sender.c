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

    char message[128];

    sockfd = socket(AF_INET,
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

    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(PORT);

    server_addr.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    printf("Enter message: ");

    if (scanf("%127s",
              message) != 1)
    {
        printf("Invalid input\n");

        close(sockfd);

        return 1;
    }

    if (sendto(sockfd,
               message,
               strlen(message),
               0,
               (struct sockaddr *)&server_addr,
               sizeof(server_addr))
        < 0)
    {
        perror("sendto");

        close(sockfd);

        return 1;
    }

    printf("[SENDER] Sent: %s\n",
           message);

    close(sockfd);

    return 0;
}

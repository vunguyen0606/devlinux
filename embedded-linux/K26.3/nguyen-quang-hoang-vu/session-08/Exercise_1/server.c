#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/monitor.sock"

int main(void)
{
    int server_fd;
    int client_fd;

    struct sockaddr_un addr;

    unlink(SOCKET_PATH);

    server_fd = socket(AF_UNIX,
                       SOCK_STREAM,
                       0);

    if (server_fd < 0)
    {
        perror("socket");
        return 1;
    }

    memset(&addr,
           0,
           sizeof(addr));

    addr.sun_family = AF_UNIX;

    strncpy(addr.sun_path,
            SOCKET_PATH,
            sizeof(addr.sun_path) - 1);

    if (bind(server_fd,
             (struct sockaddr *)&addr,
             sizeof(addr))
        < 0)
    {
        perror("bind");
        return 1;
    }

    if (listen(server_fd,
               5)
        < 0)
    {
        perror("listen");
        return 1;
    }

    printf("[SERVER] Listening on %s\n",
           SOCKET_PATH);

    while (1)
    {
        char buffer[128];

        client_fd =
            accept(server_fd,
                   NULL,
                   NULL);

        if (client_fd < 0)
        {
            perror("accept");
            continue;
        }

        memset(buffer,
               0,
               sizeof(buffer));

        read(client_fd,
             buffer,
             sizeof(buffer));

        printf("[SERVER] Command: %s\n",
               buffer);

        if (strcmp(buffer, "cpu") == 0)
        {
            FILE *fp =
                fopen("/proc/loadavg", "r");

            if (fp != NULL)
            {
                fgets(buffer,
                      sizeof(buffer),
                      fp);

                fclose(fp);
            }
        }
        else if (strcmp(buffer, "mem") == 0)
        {
            FILE *fp =
                fopen("/proc/meminfo", "r");

            if (fp != NULL)
            {
                fgets(buffer,
                      sizeof(buffer),
                      fp);

                fclose(fp);
            }
        }
        else
        {
            strcpy(buffer,
                   "Unknown command");
        }

        write(client_fd,
              buffer,
              strlen(buffer));

        close(client_fd);
    }

    close(server_fd);

    unlink(SOCKET_PATH);

    return 0;
}

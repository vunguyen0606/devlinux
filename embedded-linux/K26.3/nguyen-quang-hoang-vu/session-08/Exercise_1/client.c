#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/monitor.sock"

int main(void)
{
    int fd;

    struct sockaddr_un addr;

    char command[128];

    printf("Command (cpu/mem): ");

    scanf("%127s",
          command);

    fd = socket(AF_UNIX,
                SOCK_STREAM,
                0);

    if (fd < 0)
    {
        perror("socket");
        return 1;
    }

    memset(&addr,
           0,
           sizeof(addr));

    addr.sun_family =
        AF_UNIX;

    strncpy(addr.sun_path,
            SOCKET_PATH,
            sizeof(addr.sun_path) - 1);

    if (connect(fd,
                (struct sockaddr *)&addr,
                sizeof(addr))
        < 0)
    {
        perror("connect");
        return 1;
    }

    write(fd,
          command,
          strlen(command));

    memset(command,
           0,
           sizeof(command));

    read(fd,
         command,
         sizeof(command));

    printf("\n");
    printf("Response:\n%s\n",
           command);

    close(fd);

    return 0;
}

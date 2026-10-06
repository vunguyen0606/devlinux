#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t running = 1;

void handle_sigterm(int sig)
{
    (void)sig;

    printf("Service shutting down...\n");

    running = 0;
}

int main(void)
{
    signal(SIGTERM,
           handle_sigterm);

    setbuf(stdout,
           NULL);

    while (running)
    {
        printf("Service is running...\n");

        sleep(2);
    }

    return 0;
}

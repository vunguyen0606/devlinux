#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    setbuf(stdout, NULL);

    printf("Logger service started\n");

    for (int i = 1; i <= 30; i++)
    {
        fprintf(stderr,
                "<6> INFO log %d\n",
                i);

        sleep(1);
    }

    fprintf(stderr,
            "<3> Fatal error. Abort...\n");

    abort();

    return 0;
}

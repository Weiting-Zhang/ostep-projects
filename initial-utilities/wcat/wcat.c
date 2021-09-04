#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
int main(int argc, char *argv[])
{
    char buf[BUFFER_SIZE];
    for (int i = 1; i < argc; ++i)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        while (fgets(buf, 60, fp) != NULL)
        {
            printf("%s", buf);
        }
        fclose(fp);
    }

    return 0;
}

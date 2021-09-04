#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }
    if (argc > 2)
    {
        FILE *stream;
        for (int i = 2; i < argc; ++i)
        {
            stream = fopen(argv[i], "r");
            if (stream == NULL)
            {

                printf("wgrep: cannot open file\n");
                exit(EXIT_FAILURE);
            }

            while ((nread = getline(&line, &len, stream)) != -1)
            {
                char *ret;
                ret = strstr(line, argv[1]);
                if (ret != NULL)
                {
                    printf("%s", line);
                }
            }
            fclose(stream);
        }
        free(line);
        exit(EXIT_SUCCESS);
    }

    while ((nread = getline(&line, &len, stdin)) != -1)
    {
        char *ret;
        ret = strstr(line, argv[1]);
        if (ret != NULL)
        {
            printf("%s", line);
        }
    }

    free(line);
    exit(EXIT_SUCCESS);
}
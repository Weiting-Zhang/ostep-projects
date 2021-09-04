#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("%s", "wzip: file1 [file2 ...]\n");
        exit(1);
    }
    char pre = '\0';
    int cnt = 0;
    for (int j = 1; j < argc; ++j)
    {
        FILE *pFile;
        long lSize;
        char *buffer;
        size_t result;

        pFile = fopen(argv[j], "rb");
        if (pFile == NULL)
        {
            fputs("File error", stderr);
            exit(1);
        }

        // obtain file size:
        fseek(pFile, 0, SEEK_END);
        lSize = ftell(pFile);
        rewind(pFile);

        // allocate memory to contain the whole file:
        buffer = (char *)malloc(sizeof(char) * lSize);
        if (buffer == NULL)
        {
            fputs("Memory error", stderr);
            exit(2);
        }

        // copy the file into the buffer:
        result = fread(buffer, 1, lSize, pFile);
        if (result != lSize)
        {
            fputs("Reading error", stderr);
            exit(3);
        }

        /* the whole file is now loaded in the memory buffer. */

        // terminate
        fclose(pFile);
        for (int i = 0; i < lSize; ++i)
        {
            if (buffer[i] != pre)
            {
                if (pre != '\0')
                {
                    fwrite(&cnt, sizeof(cnt), 1, stdout);
                    fwrite(&pre, sizeof(pre), 1, stdout);
                }
                pre = buffer[i];
                cnt = 1;
            }
            else
            {
                cnt++;
            }
        }
        free(buffer);
    }
    fwrite(&cnt, sizeof(cnt), 1, stdout);
    fwrite(&pre, sizeof(pre), 1, stdout);
    exit(EXIT_SUCCESS);
}

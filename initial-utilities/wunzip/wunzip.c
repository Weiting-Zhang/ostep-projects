#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("%s", "wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    char buffer;
    int cnt;
    int item = 1;
    for (int i = 1; i < argc; ++i)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            fputs("File error", stderr);
            exit(1);
        }
        while (fread(&cnt, sizeof(cnt), item, fp) == item)
        {
            if (fread(&buffer, sizeof(buffer), item, fp) != item)
            {
                fputs("Decode error", stderr);
                exit(1);
            }
            for (int j = 0; j < cnt; ++j)
            {
                fwrite(&buffer, sizeof(buffer), item, stdout);
            }
        }
    }
    exit(0);
}
#include "execute.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>

struct
{
    char *input;
} args;

void init_stuff()
{
    args.input  = NULL;
}

void parse_args(int argc, char **argv)
{
    int opt;
    struct option opts[] =
    {
        {"help", 0, 0, 'h'},
        {"version", 0, 0, 'v'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "hv", opts, NULL)) != -1)
    {
        switch(opt)
        {
            case 'h':
                printf("cfuck FILE\n And it runs the program\n");
                exit(0);
            case 'v':
                printf("cfuck written from scratch in C by patrick-nonedev\n");
                exit(0);
        }
    }

    if (optind < argc)
        args.input = argv[optind];
}

int main(int argc, char **argv)
{
    init_stuff();
    parse_args(argc, argv);
    if (args.input == NULL)
    {
        printf("ERROR: No given input files\n");
        return 1;
    }

    struct stat st;
    if (stat(args.input, &st) == -1)
    {
        perror("stat");
        return 1;
    }

    char *buf = malloc(st.st_size * sizeof(char));
    if (buf == NULL)
    {
        peror("malloc");
        return 1;
    }

    int fd = open(args.input, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    ssize_t r = read(fd, buf, st.st_size);
    if (r < st.st_size)
    {
        perror("read");
        return 1;
    }

    execute(buf, st.st_size);

    free(buf);
    close(fd);
    putchar('\n');
    return 0;
}

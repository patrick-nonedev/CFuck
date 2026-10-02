#include "execute.h"

#include <stdio.h>
#include <stdint.h>

uint8_t cells[30000]; // 30,000 cells

void execute(char *buf, size_t len)
{
    size_t c = 0;
    size_t ptr = 0;

    while (c < len)
    {
        switch (buf[c])
        {
            case '<':
                if (ptr == 0)
                    ptr = 29999;
                else
                    ptr--;
                break;

            case '>':
                if (ptr == 29999)
                    ptr = 0;
                else
                    ptr++;
                break;

            case '+':
                cells[ptr]++;
                break;

            case '-':
                cells[ptr]--;
                break;

            case '.':
                putchar(cells[ptr]);
                break;

            case ',':
                cells[ptr] = fgetc(stdin);
                break;

            case '[':
                if (cells[ptr] == 0)
                {
                    int depth = 1;

                    while (depth && ++c < len)
                    {
                        if (buf[c] == '[')
                            depth++;
                        else if (buf[c] == ']')
                            depth--;
                    }
                }
                break;

            case ']':
                if (cells[ptr] != 0)
                {
                    int depth = 1;

                    while (depth && c > 0)
                    {
                        c--;

                        if (buf[c] == ']')
                            depth++;
                        else if (buf[c] == '[')
                            depth--;
                    }
                }
                break;
        }

        c++;
    }
}

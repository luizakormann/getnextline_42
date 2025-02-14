
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;
    int line_count = 0;

    fd = open("41_no_nl.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Leia linhas até o fim do arquivo
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Linha %d: %s", ++line_count, line);
        free(line);
    }

    // Feche o arquivo
    close(fd);

    printf("Total de linhas lidas: %d\n", line_count);

    return 0;
}

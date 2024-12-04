#include "get_next_line.h"
#include <stdio.h>

int main() {
    int fd;
    char *line;

    // Abrir um arquivo para leitura
    fd = open("text.txt", 'r');

    if (fd == -1)
        return 1;
    close(fd);
    // Ler e imprimir cada linha
    while ((line = get_next_line(0))) {
        printf("%s", line);
        free(line);
    }

    // Fechar o arquivo
    close(fd);

    return 0;
}

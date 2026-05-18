#include <stdio.h>
#include <stdlib.h>
#include <string.h>






int read_lines(const char *filename, char ***lines) {
    
    return -1;
}

void free_lines(char **lines, int count) {
    for (int i = 0; i < count; i++)
        free(lines[i]);
    free(lines);
}

int main(void) {
    const char *filename = "test_read.txt";

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Cannot create test file\n");
        return 1;
    }
    fprintf(f, "Premiere ligne\n");
    fprintf(f, "Deuxieme ligne\n");
    fprintf(f, "Troisieme ligne avec du contenu plus long\n");
    fprintf(f, "Quatrieme ligne\n");
    fprintf(f, "Fin du fichier\n");
    fclose(f);

    char **lines = NULL;
    int count = read_lines(filename, &lines);

    if (count < 0) {
        fprintf(stderr, "Erreur lecture fichier\n");
        return 1;
    }

    printf("Fichier '%s' : %d lignes lues\n\n", filename, count);
    for (int i = 0; i < count; i++) {
        printf("  [%d] %s\n", i, lines[i]);
    }

    free_lines(lines, count);
    remove(filename);

    return 0;
}

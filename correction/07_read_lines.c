#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remove trailing newline from buffer
static void trim_newline(char *buffer) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

// Resize the lines array if capacity is reached
static int resize_if_needed(char ***lines, int *capacity, int count) {
    if (count >= *capacity) {
        *capacity *= 2;
        char **tmp = realloc(*lines, sizeof(char *) * (*capacity));
        if (tmp == NULL)
            return 0;
        *lines = tmp;
    }
    return 1;
}

// Add a line to the array
static int add_line(char ***lines, int count, const char *buffer) {
    (*lines)[count] = strdup(buffer);
    if ((*lines)[count] == NULL)
        return 0;
    return 1;
}

// Read a text file line by line, store each line in a dynamic
// array of strings, return the number of lines read
// Returns -1 on file open error

int read_lines(const char *filename, char ***lines) {
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return -1;

    int capacity = 16;
    *lines = malloc(sizeof(char *) * capacity);
    if (*lines == NULL) {
		fclose(f);
        return -1;
    }

	int count = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        trim_newline(buffer);

        if (!resize_if_needed(lines, &capacity, count)) {
            fclose(f);
            return count;
        }

        if (!add_line(lines, count, buffer)) {
            fclose(f);
            return count;
        }
        count++;
    }

    fclose(f);
    return count;
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

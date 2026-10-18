#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 64

typedef struct {
    int id;
    char name[NAME_MAX];
} employee;

int count_lines(const char *path)
{
}

employee *allocate_employees(int count)
{
}

void fill_employee(const char *line, employee *table, int index)
{
}

void mark_sentinel(employee *table, int count)
{
}

employee *read_employees(const char *path)
{
}

int employee_exists(const employee *directory, int count, int id)
{
}

void add_employee(employee *directory, int *count, const employee *src)
{
}

void import_employees(const char *path, employee *directory, int *count)
{
}

int main(void)
{
    employee directory[16];
    const char *already[] = {"Camille", "Louis", "Ines", "Hugo"};
    int count = 4;

    for (int i = 0; i < count; i++) {
        directory[i].id = i + 1;
        snprintf(directory[i].name, NAME_MAX, "%s", already[i]);
    }
    import_employees("employes.csv", directory, &count);
    if (count != 15) {
        fprintf(stderr, "expected: 15 employees\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        printf("%d %s\n", directory[i].id, directory[i].name);
        if (directory[i].id != i + 1) {
            fprintf(stderr, "expected: ids 1 to 15, in order\n");
            return 1;
        }
    }
    printf("ok\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

char **parse_csv_line(const char *line, int *count) {
}

int insert_employee(Employee **employees, int *size, int *capacity, Employee emp) {
}

void free_tokens(char **tokens, int count) {

}

int main(void) {
    const char *filename = "employees.csv";

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Cannot create CSV file\n");
        return 1;
    }
    fprintf(f, "Alice Dupont,32,45000.00\n");
    fprintf(f, "Bob Martin,28,38000.50\n");
    fprintf(f, "Charlie Noir,45,62000.75\n");
    fprintf(f, "Diana Rose,37,51000.00\n");
    fclose(f);

    int emp_size = 0;
    int emp_capacity = 4;
    Employee *employees = malloc(sizeof(Employee) * emp_capacity);
    if (employees == NULL) {
        fprintf(stderr, "Malloc error\n");
        return 1;
    }

    f = fopen(filename, "r");
    if (f == NULL) {
        free(employees);
        fprintf(stderr, "Cannot open CSV\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
        int token_count = 0;
        char **tokens = parse_csv_line(line, &token_count);
        if (tokens == NULL || token_count < 3) {
            if (tokens) free_tokens(tokens, token_count);
            continue;
        }

        Employee emp = token_to_employee(tokens);
        insert_employee(&employees, &emp_size, &emp_capacity, emp);
        free_tokens(tokens, token_count);
    }
    fclose(f);

    printf("=== %d employes charges depuis %s ===\n\n", emp_size, filename);
    for (int i = 0; i < emp_size; i++) {
        printf("  [%d] %-20s | age: %2d | salaire: %.2f\n",
               i, employees[i].name, employees[i].age, employees[i].salary);
    }

    free(employees);
    remove(filename);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

// Step 1: Parse the CSV line into tokens separated by commas
char **parse_csv_line(const char *line, int *count) {
    *count = 0;
    int capacity = 8;
    char **tokens = malloc(sizeof(char *) * capacity);
    if (tokens == NULL)
        return NULL;

    char *copy = strdup(line);
    if (copy == NULL) {
        free(tokens);
        return NULL;
    }

    size_t len = strlen(copy);
    if (len > 0 && copy[len - 1] == '\n')
        copy[len - 1] = '\0';

    char *token = strtok(copy, ",");
    while (token != NULL) {
        if (*count >= capacity) {
            capacity *= 2;
            char **tmp = realloc(tokens, sizeof(char *) * capacity);
            if (tmp == NULL) {
                free(copy);
                return tokens;
            }
            tokens = tmp;
        }
        tokens[*count] = strdup(token);
        (*count)++;
        token = strtok(NULL, ",");
    }

    free(copy);
    return tokens;
}

// Step 2: Convert tokens to an Employee structure
Employee token_to_employee(char **tokens) {
    Employee emp = {0};
    if (tokens[0]) strncpy(emp.name, tokens[0], sizeof(emp.name) - 1);
    if (tokens[1]) emp.age = atoi(tokens[1]);
    if (tokens[2]) emp.salary = (float)atof(tokens[2]);
    return emp;
}

// Step 3: Insert the employee into the dynamic array
int insert_employee(Employee **employees, int *size, int *capacity, Employee emp) {
    if (*size >= *capacity) {
        *capacity *= 2;
        Employee *tmp = realloc(*employees, sizeof(Employee) * (*capacity));
        if (tmp == NULL)
            return -1;
        *employees = tmp;
    }
    (*employees)[*size] = emp;
    (*size)++;
    return 0;
}

void free_tokens(char **tokens, int count) {
    for (int i = 0; i < count; i++)
        free(tokens[i]);
    free(tokens);
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

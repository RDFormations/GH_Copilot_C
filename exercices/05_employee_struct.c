#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

// TODO: Implement employee_create
// Allocate and initialize a new Employee
// Returns NULL on allocation failure
Employee *employee_create(const char *name, int age, float salary) {
    // Use Copilot to generate the implementation
    return NULL;
}

// TODO: Implement employee_destroy
// Free the memory allocated for an Employee
void employee_destroy(Employee *emp) {
    // Use Copilot to generate the implementation
}

// TODO: Implement employee_print
// Print employee information in a readable format
void employee_print(const Employee *emp) {
    // Use Copilot to generate the implementation
}

// TODO: Implement employee_serialize
// Write employee data to file in format: name;age;salary
// Returns 0 on success, -1 on error
int employee_serialize(const Employee *emp, FILE *out) {
    // Use Copilot to generate the implementation
    return -1;
}

// TODO: Implement employee_deserialize
// Read employee data from file (format: name;age;salary)
// Returns a new Employee or NULL on error
Employee *employee_deserialize(FILE *in) {
    // Use Copilot to generate the implementation
    return NULL;
}

int main(void) {
    Employee *emp1 = employee_create("Alice Dupont", 32, 45000.0f);
    Employee *emp2 = employee_create("Bob Martin", 28, 38000.0f);
    Employee *emp3 = employee_create("Charlie Noir", 45, 62000.0f);

    printf("=== Employes crees ===\n");
    employee_print(emp1);
    employee_print(emp2);
    employee_print(emp3);

    printf("\n=== Serialisation dans fichier ===\n");
    FILE *f = fopen("employees.dat", "w");
    if (f != NULL) {
        employee_serialize(emp1, f);
        employee_serialize(emp2, f);
        employee_serialize(emp3, f);
        fclose(f);
        printf("3 employes ecrits dans employees.dat\n");
    }

    employee_destroy(emp1);
    employee_destroy(emp2);
    employee_destroy(emp3);

    printf("\n=== Deserialisation depuis fichier ===\n");
    f = fopen("employees.dat", "r");
    if (f != NULL) {
        Employee *loaded;
        while ((loaded = employee_deserialize(f)) != NULL) {
            employee_print(loaded);
            employee_destroy(loaded);
        }
        fclose(f);
    }

    remove("employees.dat");
    return 0;
}

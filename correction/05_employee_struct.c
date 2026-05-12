#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

Employee *employee_create(const char *name, int age, float salary) {
    Employee *emp = malloc(sizeof(Employee));
    if (emp == NULL)
        return NULL;
    strncpy(emp->name, name, sizeof(emp->name) - 1);
    emp->name[sizeof(emp->name) - 1] = '\0';
    emp->age = age;
    emp->salary = salary;
    return emp;
}

void employee_destroy(Employee *emp) {
    free(emp);
}

void employee_print(const Employee *emp) {
    if (emp == NULL) {
        printf("(null employee)\n");
        return;
    }
    printf("Employee { name: \"%s\", age: %d, salary: %.2f }\n",
           emp->name, emp->age, emp->salary);
}

int employee_serialize(const Employee *emp, FILE *out) {
    if (emp == NULL || out == NULL)
        return -1;
    fprintf(out, "%s;%d;%.2f\n", emp->name, emp->age, emp->salary);
    return 0;
}

Employee *employee_deserialize(FILE *in) {
    if (in == NULL)
        return NULL;
    char name[50];
    int age;
    float salary;
    if (fscanf(in, "%49[^;];%d;%f\n", name, &age, &salary) != 3)
        return NULL;
    return employee_create(name, age, salary);
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

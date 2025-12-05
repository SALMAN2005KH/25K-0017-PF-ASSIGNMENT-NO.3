#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee e[], int n) {
    printf("\n%-10s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
    for (int i = 0; i < n; i++)
        printf("%-10d %-20s %-20s %-10.2f\n", e[i].id, e[i].name, e[i].designation, e[i].salary);
}

void findHighestSalary(struct Employee e[], int n) {
    int index = 0;
    for (int i = 1; i < n; i++)
        if (e[i].salary > e[index].salary)
            index = i;

    printf("\nEmployee With Highest Salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           e[index].id, e[index].name, e[index].designation, e[index].salary);
}

void searchEmployee(struct Employee e[], int n) {
    int choice;
    printf("\nSearch by: 1-ID  2-Name: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("Enter ID: ");
        scanf("%d", &id);

        for (int i = 0; i < n; i++)
            if (e[i].id == id) {
                printf("Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       e[i].id, e[i].name, e[i].designation, e[i].salary);
                return;
            }
        printf("Employee not found.\n");
    }

    else if (choice == 2) {
        char name[50];
        printf("Enter Name: ");
        scanf("%s", name);

        for (int i = 0; i < n; i++)
            if (strcmp(e[i].name, name) == 0) {
                printf("Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       e[i].id, e[i].name, e[i].designation, e[i].salary);
                return;
            }
        printf("Employee not found.\n");
    }
}

void applyBonus(struct Employee e[], int n, float threshold) {
    for (int i = 0; i < n; i++)
        if (e[i].salary < threshold)
            e[i].salary *= 1.10;
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee e[n];

    for (int i = 0; i < n; i++) {
        printf("\nEmployee %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &e[i].id);
        printf("Name: ");
        scanf("%s", e[i].name);
        printf("Designation: ");
        scanf("%s", e[i].designation);
        printf("Salary: ");
        scanf("%f", &e[i].salary);
    }

    displayEmployees(e, n);
    findHighestSalary(e, n);
    searchEmployee(e, n);

    applyBonus(e, n, 50000);

    printf("\nAfter Bonus Update:\n");
    displayEmployees(e, n);

    return 0;
}

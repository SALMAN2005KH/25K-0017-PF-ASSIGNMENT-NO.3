#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define INITIAL_CAPACITY 4
#define MAX_INPUT 1000

char* readLine() {
    char buffer[MAX_INPUT];
    if (fgets(buffer, MAX_INPUT, stdin) == NULL)
        return NULL;
    buffer[strcspn(buffer, "\n")] = '\0';
    char *line = malloc(strlen(buffer) + 1);
    if (!line) { perror("Allocation failed"); exit(1); }
    strcpy(line, buffer);
    return line;
}

void insertLine(char ***lines, int *count, int *capacity, int index, char *text) {
    if (*count == *capacity) {
        *capacity *= 2;
        char **temp = realloc(*lines, (*capacity) * sizeof(char*));
        if (!temp) { perror("Realloc failed"); exit(1); }
        *lines = temp;
    }
    if (index < 0 || index > *count) {
        printf("Invalid index\n");
        return;
    }
    memmove(&((*lines)[index + 1]), &((*lines)[index]), (*count - index) * sizeof(char*));
    (*lines)[index] = text;
    (*count)++;
}

void deleteLine(char ***lines, int *count, int index) {
    if (index < 0 || index >= *count) {
        printf("Invalid index\n");
        return;
    }
    free((*lines)[index]);
    memmove(&((*lines)[index]), &((*lines)[index + 1]), (*count - index - 1) * sizeof(char*));
    (*count)--;
}

void printAllLines(char **lines, int count) {
    printf("\n--- Buffer ---\n");
    for (int i = 0; i < count; i++)
        printf("%d: %s\n", i, lines[i]);
}

void shrinkToFit(char ***lines, int count) {
    char **temp = realloc(*lines, count * sizeof(char*));
    if (!temp && count > 0) return;
    *lines = temp;
}

void saveToFile(char **lines, int count, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror("File error"); return; }
    for (int i = 0; i < count; i++)
        fprintf(fp, "%s\n", lines[i]);
    fclose(fp);
    printf("Saved to %s\n", filename);
}

void loadFromFile(char ***lines, int *count, int *capacity, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("File error"); return; }
    char buffer[MAX_INPUT];
    while (fgets(buffer, MAX_INPUT, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *line = malloc(strlen(buffer) + 1);
        if (!line) exit(1);
        strcpy(line, buffer);
        if (*count == *capacity) {
            *capacity *= 2;
            char **temp = realloc(*lines, (*capacity) * sizeof(char*));
            if (!temp) exit(1);
            *lines = temp;
        }
        (*lines)[*count] = line;
        (*count)++;
    }
    fclose(fp);
    printf("Loaded from %s\n", filename);
}

void freeAll(char **lines, int count) {
    for (int i = 0; i < count; i++)
        free(lines[i]);
    free(lines);
}

int main() {
    char **lines = malloc(INITIAL_CAPACITY * sizeof(char*));
    if (!lines) { perror("Initial allocation failed"); exit(1); }

    int count = 0;
    int capacity = INITIAL_CAPACITY;

    while (1) {
        int choice;
        printf("\n1.Insert\n2.Delete\n3.Print\n4.Shrink\n5.Save\n6.Load\n7.Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            int index;
            printf("Index: ");
            scanf("%d", &index);
            getchar();
            printf("Line: ");
            char *text = readLine();
            insertLine(&lines, &count, &capacity, index, text);
        }

        else if (choice == 2) {
            int index;
            printf("Index: ");
            scanf("%d", &index);
            deleteLine(&lines, &count, index);
        }

        else if (choice == 3) {
            printAllLines(lines, count);
        }

        else if (choice == 4) {
            shrinkToFit(&lines, count);
            capacity = count;
            printf("Shrunk\n");
        }

        else if (choice == 5) {
            char filename[100];
            printf("Filename: ");
            scanf("%s", filename);
            saveToFile(lines, count, filename);
        }

        else if (choice == 6) {
            char filename[100];
            printf("Filename: ");
            scanf("%s", filename);
            loadFromFile(&lines, &count, &capacity, filename);
        }

        else if (choice == 7) {
            freeAll(lines, count);
            printf("Closed\n");
            break;
        }

        else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}

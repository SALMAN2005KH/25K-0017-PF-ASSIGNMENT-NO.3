#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "members.dat"
#define MAX 100

typedef struct {
    int id;
    char name[MAX];
    char batch[MAX];
    char type[MAX];
    char regDate[11];
    char dob[11];
    char interest[MAX];
} Member;

void readLine(char *s, int n) {
    fgets(s, n, stdin);
    s[strcspn(s, "\n")] = '\0';
}

int findByID(Member *list, int count, int id) {
    for (int i = 0; i < count; i++)
        if (list[i].id == id) return i;
    return -1;
}

Member* loadFile(const char *file, int *count) {
    FILE *fp = fopen(file, "rb");
    if (!fp) { *count = 0; return malloc(sizeof(Member) * 10); }

    int cap = 10;
    Member *list = malloc(cap * sizeof(Member));
    *count = 0;

    Member temp;
    while (fread(&temp, sizeof(Member), 1, fp) == 1) {
        if (*count == cap) {
            cap *= 2;
            list = realloc(list, cap * sizeof(Member));
        }
        list[*count] = temp;
        (*count)++;
    }

    fclose(fp);
    return list;
}

void saveFile(const char *file, Member *list, int count) {
    FILE *fp = fopen(file, "wb");
    fwrite(list, sizeof(Member), count, fp);
    fclose(fp);
}

void appendFile(const char *file, Member m) {
    FILE *fp = fopen(file, "ab");
    fwrite(&m, sizeof(Member), 1, fp);
    fclose(fp);
}

void showAll(Member *list, int count) {
    if (!count) { printf("No records.\n"); return; }
    for (int i = 0; i < count; i++) {
        Member m = list[i];
        printf("%d | %s | %s | %s | %s | %s | %s\n",
               m.id, m.name, m.batch, m.type, m.regDate, m.dob, m.interest);
    }
}

void showFiltered(Member *list, int count, char *batch, char *type) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        int okBatch = strcmp(batch, "ALL") == 0 || strcasecmp(list[i].batch, batch) == 0;
        int okType = strcmp(type, "ALL") == 0 || strcasecmp(list[i].type, type) == 0 || strcasecmp(list[i].interest, type) == 0;
        if (okBatch && okType) {
            Member m = list[i];
            printf("%d | %s | %s | %s | %s | %s | %s\n",
                   m.id, m.name, m.batch, m.type, m.regDate, m.dob, m.interest);
            found = 1;
        }
    }
    if (!found) printf("No matching records.\n");
}

int main() {
    int count = 0, cap = 10;
    Member *list = loadFile(FILE_NAME, &count);
    if (count > cap) cap = count * 2;
    list = realloc(list, cap * sizeof(Member));

    while (1) {
        printf("\n1. Register\n2. Update\n3. Delete\n4. View All\n5. Filter\n6. Exit\nChoice: ");
        int ch;
        if (scanf("%d", &ch) != 1) { while (getchar()!='\n'); continue; }
        getchar();

        if (ch == 1) {
            Member m;
            printf("ID: ");
            scanf("%d", &m.id);
            getchar();

            if (findByID(list, count, m.id) != -1) {
                printf("ID exists.\n");
                continue;
            }

            printf("Name: "); readLine(m.name, MAX);
            printf("Batch: "); readLine(m.batch, MAX);
            printf("Type: "); readLine(m.type, MAX);
            printf("Reg Date (YYYY-MM-DD): "); readLine(m.regDate, 11);
            printf("DOB (YYYY-MM-DD): "); readLine(m.dob, 11);
            printf("Interest: "); readLine(m.interest, MAX);

            if (count == cap) {
                cap *= 2;
                list = realloc(list, cap * sizeof(Member));
            }

            list[count++] = m;
            appendFile(FILE_NAME, m);
            printf("Registered.\n");
        }

        else if (ch == 2) {
            int id;
            printf("ID: ");
            scanf("%d", &id);
            getchar();

            int idx = findByID(list, count, id);
            if (idx == -1) { printf("Not found.\n"); continue; }

            char newBatch[MAX], newType[MAX];
            printf("New Batch (blank to skip): "); readLine(newBatch, MAX);
            printf("New Type (blank to skip): "); readLine(newType, MAX);

            if (strlen(newBatch)) strcpy(list[idx].batch, newBatch);
            if (strlen(newType)) strcpy(list[idx].type, newType);

            saveFile(FILE_NAME, list, count);
            printf("Updated.\n");
        }

        else if (ch == 3) {
            int id;
            printf("ID: ");
            scanf("%d", &id);
            getchar();

            int idx = findByID(list, count, id);
            if (idx == -1) { printf("Not found.\n"); continue; }

            for (int i = idx; i < count - 1; i++)
                list[i] = list[i + 1];

            count--;
            saveFile(FILE_NAME, list, count);
            printf("Deleted.\n");
        }

        else if (ch == 4) {
            showAll(list, count);
        }

        else if (ch == 5) {
            char b[MAX], t[MAX];
            printf("Batch (or ALL): "); readLine(b, MAX);
            printf("Type (or ALL): "); readLine(t, MAX);
            showFiltered(list, count, b, t);
        }

        else if (ch == 6) {
            saveFile(FILE_NAME, list, count);
            free(list);
            printf("Goodbye.\n");
            break;
        }
    }

    return 0;
}

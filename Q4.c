#include <stdio.h>

struct Book {
    int id;
    int popularity;
    int lastUsed;
};

int findBook(struct Book shelf[], int capacity, int id) {
    for (int i = 0; i < capacity; i++)
        if (shelf[i].id == id)
            return i;
    return -1;
}

int findEmptySlot(struct Book shelf[], int capacity) {
    for (int i = 0; i < capacity; i++)
        if (shelf[i].id == -1)
            return i;
    return -1;
}

int findLRU(struct Book shelf[], int capacity) {
    int index = 0;
    for (int i = 1; i < capacity; i++)
        if (shelf[i].lastUsed < shelf[index].lastUsed)
            index = i;
    return index;
}

int main() {
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];
    for (int i = 0; i < capacity; i++) {
        shelf[i].id = -1;
        shelf[i].popularity = 0;
        shelf[i].lastUsed = 0;
    }

    int time = 1;

    while (Q--) {
        char op[10];
        scanf("%s", op);

        if (op[0] == 'A' && op[1] == 'D') {
            int x, y;
            scanf("%d %d", &x, &y);

            int pos = findBook(shelf, capacity, x);

            if (pos != -1) {
                shelf[pos].popularity = y;
                shelf[pos].lastUsed = time++;
            } 
            else {
                int empty = findEmptySlot(shelf, capacity);

                if (empty != -1) {
                    shelf[empty].id = x;
                    shelf[empty].popularity = y;
                    shelf[empty].lastUsed = time++;
                } 
                else {
                    int lru = findLRU(shelf, capacity);
                    shelf[lru].id = x;
                    shelf[lru].popularity = y;
                    shelf[lru].lastUsed = time++;
                }
            }
        }

        else if (op[0] == 'A' && op[1] == 'C') {
            int x;
            scanf("%d", &x);

            int pos = findBook(shelf, capacity, x);

            if (pos == -1)
                printf("-1\n");
            else {
                printf("%d\n", shelf[pos].popularity);
                shelf[pos].lastUsed = time++;
            }
        }
    }

    return 0;
}

#include <stdio.h>
#include <string.h>

int main(void)
{
    invoice journal[16];
    invoice *read;
    const char *already[] = {"FAC-1042", "FAC-1043", "FAC-1044", "FAC-1045"};
    int count = 4;
    int n = 0;
    int times[16] = {0};

    for (int i = 0; i < count; i++) {
        journal[i].id = i + 1;
        snprintf(journal[i].reference, sizeof journal[i].reference, "%s", already[i]);
    }

    read = read_invoices("factures.csv");
    if (read == NULL) {
        fprintf(stderr, "read_invoices returned nothing\n");
        return 1;
    }
    while (n < 16 && read[n].id != -1) {
        n++;
    }
    if (n != 15) {
        fprintf(stderr, "the array read must hold 15 invoices then id -1\n");
        return 1;
    }

    post_to_journal("factures.csv", journal, &count);
    if (count != 15) {
        fprintf(stderr, "expected: 15 invoices in the journal\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        printf("%d %s\n", journal[i].id, journal[i].reference);
        if (journal[i].id < 1 || journal[i].id > 15 || journal[i].id != i + 1) {
            fprintf(stderr, "expected: ids 1 to 15, in order\n");
            return 1;
        }
        times[journal[i].id]++;
    }
    for (int id = 1; id <= 4; id++) {
        if (times[id] != 1) {
            fprintf(stderr, "invoice %d must appear only once\n", id);
            return 1;
        }
    }
    printf("ok\n");
    return 0;
}

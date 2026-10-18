#include <stdio.h>
#include <string.h>

int main(void)
{
    facture journal[16];
    facture *lues;
    const char *deja[] = {"FAC-1042", "FAC-1043", "FAC-1044", "FAC-1045"};
    int count = 4;
    int n = 0;
    int fois[16] = {0};

    for (int i = 0; i < count; i++) {
        journal[i].id = i + 1;
        snprintf(journal[i].reference, sizeof journal[i].reference, "%s", deja[i]);
    }

    lues = lire_factures("factures.csv");
    if (lues == NULL) {
        fprintf(stderr, "lire_factures n'a rien rendu\n");
        return 1;
    }
    while (n < 16 && lues[n].id != -1) {
        n++;
    }
    if (n != 15) {
        fprintf(stderr, "le tableau lu doit contenir 15 factures puis id -1\n");
        return 1;
    }

    comptabiliser("factures.csv", journal, &count);
    if (count != 15) {
        fprintf(stderr, "attendu : 15 factures au journal\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        printf("%d %s\n", journal[i].id, journal[i].reference);
        if (journal[i].id < 1 || journal[i].id > 15 || journal[i].id != i + 1) {
            fprintf(stderr, "attendu : les ids 1 à 15, dans l'ordre\n");
            return 1;
        }
        fois[journal[i].id]++;
    }
    for (int id = 1; id <= 4; id++) {
        if (fois[id] != 1) {
            fprintf(stderr, "la facture %d ne doit apparaître qu'une fois\n", id);
            return 1;
        }
    }
    printf("ok\n");
    return 0;
}

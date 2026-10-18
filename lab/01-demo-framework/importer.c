#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOM_MAX 64

typedef struct {
    int id;
    char nom[NOM_MAX];
} employe;

int compter_lignes(const char *chemin)
{
}

employe *allouer_employes(int nombre)
{
}

void remplir_employe(const char *ligne, employe *table, int index)
{
}

void marquer_sentinelle(employe *table, int nombre)
{
}

employe *lire_employes(const char *chemin)
{
}

int employe_existe(const employe *annuaire, int count, int id)
{
}

void ajouter_employe(employe *annuaire, int *count, const employe *src)
{
}

void importer(const char *chemin, employe *annuaire, int *count)
{
}

int main(void)
{
    employe annuaire[16];
    const char *deja[] = {"Camille", "Louis", "Ines", "Hugo"};
    int count = 4;

    for (int i = 0; i < count; i++) {
        annuaire[i].id = i + 1;
        snprintf(annuaire[i].nom, NOM_MAX, "%s", deja[i]);
    }
    importer("employes.csv", annuaire, &count);
    if (count != 15) {
        fprintf(stderr, "attendu : 15 employes\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        printf("%d %s\n", annuaire[i].id, annuaire[i].nom);
        if (annuaire[i].id != i + 1) {
            fprintf(stderr, "attendu : les ids 1 a 15, dans l'ordre\n");
            return 1;
        }
    }
    printf("ok\n");
    return 0;
}

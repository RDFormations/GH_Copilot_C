# Exercices — Completions inline et contexte

> **Contexte** — Vous implémentez des fonctions utilitaires en **C**. Des commentaires trop vagues produisent du code générique.

## Exercice — Commentaires-prompts algorithmiques

**Notions mobilisées :** sections 2.5–2.6 (Quoi/Comment/Contraintes, itération).

### Énoncé

1. Créez `src/sort.c`.
2. **Stub A** — copiez le stub vague, déclenchez une complétion (`Alt + \`), notez pourquoi la suggestion est insuffisante :

```c
/* trier un tableau */
int insertion_sort(const int* values, int count, int* out);
```

3. Remplacez par un commentaire structuré Quoi/Comment/Contraintes (tri par insertion, copie immuable) :

```c
/**
 * QUOI : Tri par insertion sur tableau de nombres
 * COMMENT : parcours O(n²), copie immuable
 * CONTRAINTES : retourne 0 si OK, -1 si erreur
 */
int insertion_sort(const int* values, int count, int* out);
```

4. **Stub B** — même démarche pour la recherche dichotomique (tableau trié, retourne index ou -1) :

```c
/* recherche dichotomique */
int binary_search(const int* values, int count, int target);
```

5. Pour chaque stub, documentez le nombre d itérations avant une suggestion acceptable.

**Critère de réussite :** deux fonctions avec prompts précis ; algorithme correct ; bilan d itération documenté.

**Documentation :** [Best practices](https://docs.github.com/copilot/get-started/best-practices-for-using-github-copilot)

> **Correction** : [Accéder à la correction](../correction/fr/correction-02-completions-inline.md)

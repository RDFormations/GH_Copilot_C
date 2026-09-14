# Exercices — Chat et modes d interaction

> **Contexte** — Un module de calcul de dates contient un bug. Les tests échouent : la deadline est parfois antérieure à createdAt.

## Exercice — Ask puis Edit sur un bug SLA

**Prérequis :** module 3 lu ; Copilot Chat opérationnel.

### Énoncé

1. Créez `src/date_utils.c` avec l échantillon buggy :

```c
#include <time.h>

time_t calculate_sla_deadline(time_t created_at, int priority_hours) {
    return created_at - (priority_hours * 3600); /* BUG */
}
```

2. **Ask** — sélectionnez la fonction, demandez : « Pourquoi la deadline peut être antérieure à createdAt ? » Notez la ligne fautive.
3. **Ask** — demandez la modification minimale sans appliquer le patch.
4. **Edit** — demandez : « Ajouter les heures SLA à createdAt, pas les soustraire. » Acceptez le diff après relecture.
5. Vérifiez : createdAt = 2026-01-10T10:00:00Z, priority normal (48 h) → deadline ≈ +48 h.
6. **Bonus** — utilisez `/tests` pour générer deux cas de test.

**Critère de réussite :** diagnostic Ask correct ; correction Edit avec addition ; test manuel OK.

> **Correction** : [Accéder à la correction](../correction/fr/correction-03-chat-modes.md)

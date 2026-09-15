# Exercices — Introduction à GitHub Copilot

> **Contexte** — Chaque développeur doit confirmer que Copilot est opérationnel en **C** et produire une première fonction utilitaire.

## Exercice — Installation et première complétion

**Notions mobilisées :** sections 1.2 à 1.3 (versions Copilot, installation, vérification inline).

**Prérequis :** compte GitHub + licence Copilot ; VS Code ; dépôt de travail local (ou dossier fourni).

### Énoncé

1. Installez **GitHub Copilot** et **GitHub Copilot Chat**, connectez-vous à GitHub. Vérifiez l icône dans la barre de statut.
2. Créez `src/utils/format_id.c`.
3. Saisissez la signature avec un commentaire décrivant le format `ID-00042` (sans implémenter le corps) :

```c
char* format_id(int id);
```

4. Acceptez la complétion avec `Tab` (ou partiellement `Ctrl + →`).
5. Testez que `strcmp(format_id(42), "ID-00042") == 0`.
6. Notez : taux de modification manuelle (aucune / légère / refonte).

**Critère de réussite :** Copilot connecté ; fonction exécutable ; `ID-00042` pour id=42.

**Documentation :** [Set up Copilot](https://docs.github.com/copilot/how-tos/set-up/install-copilot-extension)

> **Correction** : [Accéder à la correction](../correction/fr/correction-01-introduction.md)

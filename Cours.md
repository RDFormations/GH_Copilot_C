# Développer en C avec GitHub Copilot

---

## Module 1 : Introduction à GitHub Copilot

### Qu'est-ce que GitHub Copilot ?

GitHub Copilot est un assistant de programmation basé sur l'intelligence artificielle, développé par GitHub en collaboration avec OpenAI. Il fonctionne comme un **pair-programmer virtuel** intégré directement dans l'éditeur de code.

**Principe de fonctionnement :**

- Copilot analyse le contexte du code en cours d'écriture (fichiers ouverts, commentaires, noms de variables)
- Il génère des suggestions de code en temps réel, directement dans l'éditeur
- Le modèle sous-jacent a été entraîné sur des milliards de lignes de code provenant de dépôts publics GitHub
- Il est particulièrement efficace en C grâce à la quantité massive de code C disponible en open source (Linux kernel, GNU tools, etc.)

**Ce que Copilot n'est pas :**

- Ce n'est pas un compilateur ni un vérificateur de code
- Il ne garantit pas que le code généré est correct ou sécurisé
- Il ne remplace pas la compréhension du langage C par le développeur

### Les différentes versions

| Version              | Description                                    | Usage principal                         |
| -------------------- | ---------------------------------------------- | --------------------------------------- |
| **Copilot (inline)** | Suggestions de code directement dans l'éditeur | Écriture de code au quotidien           |
| **Copilot Chat**     | Interface conversationnelle intégrée           | Questions, explications, refactoring    |
| **Copilot CLI**      | Assistant Agentic similaire au mode Agent      | Commandes shell, compilation, debugging |

**Copilot inline** est le mode par défaut : dès qu'on tape du code, des suggestions apparaissent en gris. On peut les accepter avec `Tab` ou les ignorer en continuant à taper.

**Copilot Chat** permet d'avoir une conversation avec l'IA : expliquer du code, demander des corrections, générer des tests.

**Copilot CLI** permet d'avoir un outils centré sur les agents similaire a Claude Code

### Installation et configuration

**Prérequis :**

- Un compte GitHub avec un abonnement Copilot actif (Individual, Business ou Enterprise)
- Visual Studio Code installé
- Extension C/C++ de Microsoft (pour l'IntelliSense)

**Étapes d'installation :**

1. Ouvrir VS Code
2. Aller dans Extensions (`Ctrl + Shift + X`)
3. Rechercher "GitHub Copilot" et installer l'extension
4. Installer également "GitHub Copilot Chat"
5. Se connecter à GitHub quand VS Code le demande
6. Vérifier l'icône Copilot dans la barre de statut (en bas)

**Vérification du fonctionnement :**
Créer un fichier `test.c` et commencer à taper :

```c
#include <stdio.h>

// Fonction qui affiche Hello World
```

Si Copilot fonctionne, une suggestion devrait apparaître en gris pour compléter la fonction.

### Interface et statistiques d'utilisation

Pour consulter les statistiques d'utilisation de Copilot :

- Cliquer sur l'icône Copilot dans la barre de statut de VS Code
- Accéder au tableau de bord via GitHub : `Settings > Copilot > Usage`
- Les métriques disponibles : taux d'acceptation des suggestions, lignes de code générées, langages les plus utilisés

En entreprise (Copilot Business/Enterprise), les administrateurs ont accès à un dashboard détaillé montrant le pourcentage d'utilisation par équipe et par développeur.

---

## Module 2 : Suggestions inline et contexte

### Raccourcis clavier essentiels

| Action                           | Raccourci (Windows/Linux) | Raccourci (Mac) |
| -------------------------------- | ------------------------- | --------------- |
| Accepter la suggestion           | `Tab`                     | `Tab`           |
| Rejeter la suggestion            | `Échap`                   | `Échap`         |
| Suggestion suivante              | `Alt + ]`                 | `Option + ]`    |
| Suggestion précédente            | `Alt + [`                 | `Option + [`    |
| Accepter le mot suivant          | `Ctrl + →`                | `Cmd + →`       |
| Déclencher manuellement          | `Alt + \`                 | `Option + \`    |
| Ouvrir le panneau de suggestions | `Ctrl + Enter`            | `Ctrl + Enter`  |

Le panneau de suggestions (`Ctrl + Enter`) ouvre une fenêtre avec jusqu'à 10 suggestions alternatives. Utile quand la première suggestion ne convient pas.

### Déclencher des suggestions

#### Commencer à taper une signature de fonction

```c
int calculate_factorial(int n)
```

Copilot va proposer le corps de la fonction en se basant sur le nom explicite.

#### Écrire un commentaire descriptif

```c
// Tri à bulles sur un tableau d'entiers, retourne le tableau trié
void bubble_sort(int arr[], int size)
```

Le commentaire guide Copilot sur l'algorithme attendu.

#### Créer une structure de données

```c
typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;
```

Après avoir défini la structure, Copilot pourra suggérer des fonctions de manipulation cohérentes (create, print, free, etc.).

#### Nommer une variable de manière explicite

```c
int max_retry_count = 3;
char *error_message = NULL;
FILE *input_file = fopen("data.csv", "r");
```

Des noms de variables clairs aident Copilot à comprendre l'intention du code.

### Le contexte compte

Copilot ne se base pas uniquement sur la ligne en cours. Il analyse un **contexte élargi** :

**Les fichiers ouverts dans l'éditeur :**
Si vous avez un fichier `utils.h` ouvert avec des prototypes, Copilot les utilisera pour générer des implémentations cohérentes dans `utils.c`.

**Les includes influencent les suggestions :**

```c
#include <pthread.h>  // Copilot va suggérer du code multithread
#include <sys/socket.h>  // Copilot va suggérer du code réseau
#include <sqlite3.h>  // Copilot va suggérer du code base de données
```

**Le code environnant guide la génération :**
Si les fonctions précédentes utilisent un style particulier (gestion d'erreurs avec des codes de retour, allocation dynamique avec vérification), Copilot va reproduire ce pattern.

```c
// Si votre code existant fait ceci :
int *ptr = malloc(sizeof(int) * n);
if (ptr == NULL) {
    fprintf(stderr, "Erreur allocation mémoire\n");
    return -1;
}

// Copilot va reproduire ce pattern de vérification dans les suggestions suivantes
```

### La fenêtre de contexte (context window)

La **fenêtre de contexte** (ou _context window_) est la quantité maximale de texte — code, commentaires, historique de chat, instructions du projet — que le modèle peut prendre en compte **en une seule requête**.

**Définition concrète :**

- Tout ce que Copilot « voit » avant de répondre occupe cette fenêtre : fichiers ouverts, sélection, messages du chat, `@workspace`, instructions Copilot, etc.
- Cette limite se mesure en **tokens** (morceaux de texte), pas en lignes de code. Une ligne C dense ou un long commentaire consomme plus qu'une ligne vide.
- Au-delà de la limite, le contenu le plus ancien ou le moins prioritaire est **tronqué** : le modèle ne peut plus s'appuyer dessus, même s'il est encore visible dans votre éditeur.

**Pourquoi c'est important :**

| Conséquence                       | Explication                                                                                                                                         |
| --------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Perte de contexte**             | Un gros fichier + tout l'historique du chat peuvent faire « oublier » le début de la conversation ou des fichiers éloignés.                         |
| **Suggestions moins cohérentes**  | Si vos conventions (nommage, gestion d'erreurs) ne tiennent plus dans la fenêtre, Copilot revient à des patterns génériques appris sur tout GitHub. |
| **Réponses incomplètes en Agent** | Sur un gros dépôt, l'agent ne charge pas tout le code d'un coup ; il doit cibler les bons fichiers.                                                 |
| **Coût de qualité du prompt**     | Chaque mot utile (commentaire précis, prototype dans le `.h`) remplace du bruit ; un contexte pertinent vaut mieux qu'un contexte volumineux.       |

**Bonnes pratiques pour optimiser la fenêtre :**

- Garder ouverts uniquement les fichiers **pertinents** pour la tâche en cours (ex. `utils.h` + `utils.c`, pas tout le projet).
- Poser des questions **ciblées** dans le chat plutôt que de coller des milliers de lignes.
- Utiliser `#file:path/to/file.c` pour un fichier précis plutôt que `#workspace` quand la question est locale.
- Découper les grosses refontes en étapes (module par module) au lieu d'une seule demande globale.
- Centraliser les règles du projet dans les **instructions** (voir Module 5) plutôt que de les répéter à chaque message.

---

## Module 3 : Techniques de prompting

### L'art du commentaire-prompt

En C, les commentaires sont le principal levier pour guider Copilot. Un commentaire bien rédigé produit un code de meilleure qualité qu'un nom de fonction seul.

**Commentaire vague → résultat imprécis :**

```c
// trier le tableau
```

**Commentaire précis → résultat ciblé :**

```c
// Tri par insertion sur un tableau d'entiers en ordre croissant
// Complexité : O(n²) dans le pire cas, O(n) dans le meilleur cas
// Modifie le tableau en place
void insertion_sort(int arr[], int n)
```

### Principes de base

**Être spécifique et précis :**

```c
// ❌ Vague
// lire un fichier

// ✅ Précis
// Lire un fichier texte ligne par ligne, stocker chaque ligne dans un tableau
// dynamique de chaînes, retourner le nombre de lignes lues
// Retourne -1 en cas d'erreur d'ouverture
int read_lines(const char *filename, char ***lines)
```

**Donner du contexte :**

```c
// Cette fonction fait partie d'un allocateur mémoire custom
// Elle recherche un bloc libre de taille suffisante dans la free list
// Utilise la stratégie first-fit
void *find_free_block(size_t size)
```

**Décomposer les problèmes complexes :**
Plutôt que de demander une fonction monolithique, découper en étapes :

```c
// Étape 1 : Parser la ligne CSV en tokens séparés par des virgules
char **parse_csv_line(const char *line, int *count);

// Étape 2 : Convertir les tokens en structure Employee
Employee token_to_employee(char **tokens);

// Étape 3 : Insérer l'employé dans le tableau dynamique
int insert_employee(Employee **employees, int *size, int *capacity, Employee emp);
```

**Itérer sur les suggestions :**
Si la première suggestion ne convient pas, utiliser `Alt + ]` pour voir les alternatives, ou reformuler le commentaire.

### Structure d'un bon prompt

Un prompt efficace pour Copilot suit la structure **Quoi / Comment / Contraintes** :

```c
/**
 * QUOI : Recherche un élément dans un tableau trié
 * COMMENT : Utilise la recherche dichotomique (binary search)
 * CONTRAINTES :
 *   - Le tableau doit être trié en ordre croissant
 *   - Retourne l'index de l'élément ou -1 si non trouvé
 *   - Fonctionne pour des tableaux jusqu'à INT_MAX éléments
 */
int binary_search(const int arr[], int size, int target)
```

Autre exemple avec gestion mémoire :

```c
/**
 * QUOI : Crée une copie profonde d'une liste chaînée
 * COMMENT : Parcours itératif avec allocation de nouveaux nœuds
 * CONTRAINTES :
 *   - Retourne NULL si la liste source est NULL ou en cas d'erreur malloc
 *   - L'appelant est responsable de libérer la copie avec free_list()
 *   - Les données (char*) sont dupliquées avec strdup
 */
Node *deep_copy_list(const Node *head)
```

### Itération et raffinement

**Accepter partiellement une suggestion :**
Utiliser `Ctrl + →` (accepter mot par mot) quand le début de la suggestion est bon mais la suite diverge. Cela permet de garder le contrôle tout en profitant de l'assistance.

**Modifier et relancer pour affiner :**

```c
// Premier essai - suggestion trop simple
// Trier un tableau
// → Copilot génère un bubble sort basique

// Deuxième essai - plus précis
// Quicksort avec pivot médian de trois, partition de Lomuto
// Gère les tableaux de taille < 10 avec insertion sort
void quicksort(int arr[], int low, int high)
```

**Combiner plusieurs suggestions :**
Accepter une suggestion pour le squelette de la fonction, puis supprimer certaines parties et redemander à Copilot de les régénérer avec un commentaire plus spécifique.

---

## Module 4 : Copilot Chat et modes d'interaction

### Interface conversationnelle

Ouvrir le panneau Chat : `Ctrl + Shift + I` (ou `Cmd + Shift + I` sur Mac).

Copilot Chat permet de poser des questions en langage naturel directement dans VS Code :

**Exemples de questions utiles en C :**

- "Explique-moi ce que fait cette fonction"
- "Pourquoi ce code provoque un segfault ?"
- "Comment implémenter un pool de threads en C ?"
- "Génère les tests unitaires pour cette fonction"
- "Optimise cette boucle pour réduire les cache misses"

**Obtenir des explications détaillées :**
Sélectionner un bloc de code complexe puis demander dans le chat :
"Explique ce code étape par étape, en particulier la gestion de la mémoire"

### Commandes slash

Les commandes slash sont des raccourcis pour des actions fréquentes :

| Commande   | Action                                              |
| ---------- | --------------------------------------------------- |
| `/explain` | Explique le code sélectionné                        |
| `/fix`     | Propose une correction pour le code sélectionné     |
| `/tests`   | Génère des tests pour le code sélectionné           |
| `/doc`     | Génère la documentation (commentaires Doxygen en C) |
| `/new`     | Crée un nouveau fichier/projet                      |
| `/clear`   | Efface l'historique du chat                         |

**Exemple avec `/doc` sur une fonction C :**

```c
// Avant /doc
int add_node(LinkedList *list, void *data, size_t data_size);

// Après /doc - Copilot génère :
/**
 * @brief Ajoute un nouveau nœud en tête de la liste chaînée
 * @param list Pointeur vers la liste chaînée
 * @param data Pointeur vers les données à copier dans le nœud
 * @param data_size Taille en octets des données à copier
 * @return 0 en cas de succès, -1 en cas d'erreur d'allocation
 */
int add_node(LinkedList *list, void *data, size_t data_size);
```

### Sélection de contexte

**Sélectionner du code avant de poser une question :**
Surligner un bloc de code, puis ouvrir le chat → Copilot comprend que la question porte sur ce code précis.

### Indexation sémantique du codebase

L'**indexation sémantique** (ou _semantic codebase indexing_) permet à Copilot de **comprendre le sens** du code du projet, pas seulement de faire correspondre des mots-clés.

**Principe :**

- Le dépôt est analysé et transformé en représentations vectorielles (embeddings) : fonctions, structures, commentaires, relations entre fichiers.
- Une question du type « Où est gérée l'allocation mémoire ? » ou `@workspace trouve les fuites potentielles` s'appuie sur cette index, pas sur une simple recherche texte `grep`.
- Les résultats les plus **pertinents sémantiquement** sont injectés dans la fenêtre de contexte avant la génération de la réponse.

**Différence avec le contexte « classique » :**

| Approche                          | Limite                                                                                           |
| --------------------------------- | ------------------------------------------------------------------------------------------------ |
| Fichiers ouverts + ligne courante | Ne couvre que ce que vous avez sous les yeux                                                     |
| Recherche par nom de symbole      | Rate les implémentations sous un autre nom ou les patterns répétés                               |
| **Index sémantique**              | Retrouve du code par **intention** (« parsing CSV », « free list », « gestion d'erreur malloc ») |

**Quand l'utiliser :**

- Explorer un projet inconnu : `#workspace décris l'architecture et les modules principaux`
- Refactoring transversal : retrouver toutes les fonctions qui dupliquent une logique
- Debugging : localiser où une structure ou une API est utilisée sans connaître le nom exact

**Bonnes pratiques :**

- Laisser l'indexation se terminer après un clone ou un gros pull (indicateur dans la barre de statut / paramètres Copilot).
- Formuler des requêtes avec des **concepts** (« liste chaînée », « tri en place ») plutôt qu'un seul identifiant C.
- Combiner index sémantique + `#file:path/to/file.c` : d'abord localiser avec `#workspace`, puis affiner sur le fichier trouvé.
- Rappel : l'index alimente la fenêtre de contexte — rester précis évite de noyer le modèle sous trop d'extraits.

---

### Mode Agent

Le mode le plus autonome. Copilot peut :

- Exécuter des commandes terminal (compilation, tests)
- Modifier plusieurs fichiers en séquence
- Itérer jusqu'à résoudre un problème

Exemple en C :

```
Mode Agent : "Corrige tous les memory leaks détectés par Valgrind dans ce projet"
→ Copilot lance Valgrind, analyse la sortie, corrige les fichiers, recompile, vérifie
```

### Mode Cloud (aperçu)

Le mode Cloud permet d'exécuter des tâches Copilot sur l'infrastructure GitHub :

- Tâches longues qui tournent en arrière-plan
- Pas besoin de garder VS Code ouvert
- Résultats disponibles via notification ou PR
- Utile pour des refactorings massifs ou des migrations de code

---

## Module 5 : Fonctionnalités avancées

### Agents, Skills, Prompts et Instructions

**Instructions personnalisées :**
Créer un fichier `.github/copilot-instructions.md` à la racine du projet pour guider Copilot :

```markdown
# Instructions pour ce projet C

- Utiliser le standard C11
- Toujours vérifier les retours de malloc (retourner NULL en cas d'échec)
- Conventions de nommage : snake_case pour les fonctions et variables
- Préfixer les fonctions publiques par le nom du module (ex: list_add, list_remove)
- Documenter avec le format Doxygen
- Gestion d'erreurs par codes de retour (0 = succès, négatif = erreur)
```

### Instructions spécifiques par chemin (path-specific)

Les instructions **globales** s'appliquent à tout le dépôt. Les instructions **path-specific** ne s'activent que lorsque Copilot travaille sur des fichiers dont le chemin correspond à un **motif** (glob).

**Pourquoi les utiliser :**

- Un module C embarqué (MISRA, pas de `malloc`) n'a pas les mêmes règles qu'un outil CLI avec allocation libre.
- Les tests (`tests/`) peuvent exiger des macros ou du style différent du code de production (`src/`).
- Les headers publics (`include/`) et les implémentations (`src/`) peuvent demander des conventions distinctes (Doxygen, include guards, etc.).

**Organisation recommandée (GitHub Copilot) :**

Placer des fichiers Markdown dans `.github/instructions/`, chacun avec un en-tête YAML indiquant les chemins concernés :

```markdown
---
applyTo: "src/**/*.c,src/**/*.h"
---

# Règles pour le code source C

- Standard C11, pas d'extensions GNU sauf si déjà présent dans le fichier
- Vérifier systématiquement le retour de malloc/calloc/realloc
- snake_case pour fonctions et variables ; préfixe module pour l'API publique
```

```markdown
---
applyTo: "tests/**/*.c"
---

# Règles pour les tests

- Utiliser uniquement assert() et des helpers déjà définis dans test_common.h
- Pas de printf de debug : utiliser les macros TEST_LOG si besoin
- Un fichier de test par module testé (test_parser.c pour parser.c)
```

```markdown
---
applyTo: "exercices/**/*.c"
---

# Contexte pédagogique — exercices étudiants

- Laisser les blocs TODO intacts ; ne pas implémenter à la place de l'étudiant
- Suggérer des indices dans les commentaires plutôt que des solutions complètes
- Rester aligné sur les énoncés du fichier (noms de fonctions imposés)
```

**Ordre de priorité (du plus général au plus spécifique) :**

1. Instructions globales (`.github/copilot-instructions.md`)
2. Instructions path-specific dont le glob correspond au fichier actif
3. Contexte immédiat (fichier ouvert, sélection, commentaire-prompt)

**Bonnes pratiques :**

- Préférer des globs **étroits** (`src/net/*.c`) à `**/*` pour éviter des règles contradictoires.
- Documenter dans chaque fichier _pourquoi_ la règle existe (évite que Copilot la « contourne »).
- Aligner les instructions path-specific avec la structure réelle du repo (`exercices/`, `correction/`, `tests/`).
- Vérifier qu'une consigne globale n'annule pas une consigne locale (ex. « toujours compléter le code » vs exercices avec TODO).

**Fichiers prompt réutilisables (`.github/prompts/`) :**
Créer des prompts sauvegardés pour des tâches récurrentes :

```markdown
<!-- .github/prompts/new-module.prompt.md -->

Crée un nouveau module C avec :

- Un fichier header (.h) avec les include guards
- Un fichier source (.c) avec les implémentations
- Les fonctions init et cleanup du module
- Documentation Doxygen pour chaque fonction publique
```

### Commit automatique

Copilot peut générer automatiquement des messages de commit pertinents :

- Cliquer sur l'icône Copilot dans la vue Source Control
- Copilot analyse les changements (diff) et propose un message
- Le message suit les conventions du projet (Conventional Commits si configuré)

Exemple :

```
feat(parser): add CSV parsing with quoted field support

- Handle escaped quotes within fields
- Support multiline values enclosed in quotes
- Add error reporting with line numbers
```

### Code review sur les commits en cours

Copilot peut relire le code avant de commiter :

- Dans l'onglet Source Control, utiliser "Review Changes" avec Copilot
- Il identifie : bugs potentiels, fuites mémoire, problèmes de style, suggestions d'amélioration
- Particulièrement utile en C pour détecter :
  - Accès hors limites de tableaux
  - Pointeurs non initialisés
  - Double free / use after free
  - Buffer overflows

### Fine tuning et personnalisation

**Adapter Copilot au style du projet :**

- Les fichiers `.github/copilot-instructions.md` influencent toutes les suggestions
- Copilot apprend du code existant dans le projet (les patterns se propagent)
- Utiliser des fichiers d'exemple comme "modèles" que Copilot reproduira

---

## Module 6 : Bonnes pratiques et productivité

### Validation du code généré

Le code produit par Copilot en C nécessite une vigilance particulière :

**Toujours vérifier :**

- La gestion mémoire (malloc/free, pas de fuites, pas de double free)
- Les accès aux tableaux (pas de dépassement de bornes)
- Les pointeurs (vérification de NULL avant déréférencement)
- Les types et le casting (overflow d'entiers, troncature)
- La gestion des erreurs (retours de fonctions système)

**Outils de validation :**

```bash
# Compilation avec warnings stricts
gcc -Wall -Wextra -Werror -fsanitize=address,undefined -g -o prog main.c

# Analyse statique
cppcheck --enable=all --inconclusive src/

# Détection de fuites mémoire
valgrind --leak-check=full --show-leak-kinds=all ./prog
```

### Quand utiliser Copilot

**Code répétitif ou boilerplate :**

```c
// Copilot excelle pour générer des fonctions CRUD similaires
Employee *employee_create(const char *name, int age, float salary);
void employee_destroy(Employee *emp);
void employee_print(const Employee *emp);
int employee_serialize(const Employee *emp, FILE *out);
Employee *employee_deserialize(FILE *in);
```

**Implémentation d'algorithmes classiques :**
Tri, recherche, parcours de graphe, tables de hachage — Copilot connaît les implémentations standards.

**Tests unitaires :**

```c
// Demander à Copilot : "Génère les tests pour la fonction binary_search"
// Il produit des cas de test pertinents :
void test_binary_search_found(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 7) == 3);
}

void test_binary_search_not_found(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 4) == -1);
}

void test_binary_search_empty(void) {
    int arr[] = {};
    assert(binary_search(arr, 0, 5) == -1);
}
```

**Exploration de nouvelles APIs :**
Quand on utilise une bibliothèque peu familière (libcurl, OpenSSL, SQLite), Copilot aide à écrire le boilerplate d'initialisation.

### Quand être prudent

**Code critique pour la sécurité :**
Cryptographie, authentification, parsing d'entrées utilisateur — toujours relire manuellement et tester en profondeur.

**Logique métier complexe :**
Les règles métier spécifiques au projet ne sont pas connues de Copilot. Il peut générer du code syntaxiquement correct mais sémantiquement faux.

**Code avec des contraintes spécifiques :**
Systèmes embarqués avec mémoire limitée, code temps réel, conformité à des normes (MISRA C, DO-178C) — Copilot ne connaît pas ces contraintes.

**Optimisations de performance critiques :**
Copilot génère du code fonctionnel mais rarement optimal. Pour du code critique en performance (boucles internes, SIMD, cache-friendly), l'expertise humaine reste indispensable.

### Productivité optimale

**Utiliser Copilot comme assistant, pas comme remplacement :**

- Lire et comprendre chaque suggestion avant de l'accepter
- Ne jamais accepter aveuglément du code qu'on ne comprend pas
- Copilot accélère l'écriture, il ne dispense pas de la réflexion

**Apprendre des suggestions pour s'améliorer :**

- Copilot peut montrer des patterns ou des fonctions de la bibliothèque standard qu'on ne connaît pas
- Observer les suggestions est une forme d'apprentissage passif
- Exemple : découvrir `qsort`, `bsearch`, `srtok_rt` via les suggestions

**Adapter son workflow progressivement :**

1. Commencer par accepter les suggestions pour le boilerplate uniquement
2. Progressivement, utiliser les commentaires-prompts pour des fonctions entières
3. Intégrer Copilot Chat pour le debugging et la documentation
4. Utiliser le mode Agent pour des tâches complexes multi-fichiers

---

---
name: add-comment
description: When agent want to add a comment in a source code file, it can use this skill to insert a comment with the appropriate syntax for the language. The comment will be prefixed with "albert a dit:" to indicate that it was added by the agent.
---


Nom: ajouter-un-commentaire

Résumé:
  Compétence réutilisable pour insérer des commentaires lisibles dans le code source. Gère la détection du langage, choisit la syntaxe de commentaire appropriée, insère un préfixe demandé (par ex. "albert a dit:"), et pose des questions de clarification si le point d'insertion est ambigu.

Objectif:
  Permettre à un agent d'ajouter des commentaires explicatifs, TODOs ou annotations pédagogiques dans des fichiers source sans modifier la logique du code.

Entrées attendues:
  - chemin(s) de fichier ou dossier à annoter (ex: `correction/09_memory_allocator.c`)
  - texte du commentaire à insérer (ex: "vérifie la coalescence des blocs")
  - optionnel: position d'insertion (au-dessus d'une fonction, en ligne, à la fin du fichier)
  - optionnel: préfixe à utiliser (par défaut: "albert a dit:")

Sorties:
  - fichiers modifiés (avec commentaires insérés)
  - petit rapport listant les fichiers modifiés et les emplacements des insertions

Étapes (workflow):
  1. Valider les entrées : s'assurer que les chemins existent et que le texte du commentaire n'est pas vide.
  2. Pour chaque fichier :
     a. Détecter le langage par l'extension (.c, .h, .py, .sh, .html, ...).
     b. Choisir la syntaxe de commentaire adaptée:
        - C/C++/Java: `//` pour ligne, `/* */` pour bloc
        - Python/Shell: `#`
        - HTML/XML: `<!-- -->`
     c. Localiser le point d'insertion:
        - Si une position explicite est fournie, utiliser celle-ci.
        - Sinon, rechercher des indices : signature de fonction demandée, TODO existant, commentaire marqué, ou insertion en tête de fichier.
        - Si plusieurs emplacements possibles, demander une clarification à l'utilisateur.
     d. Préparer le commentaire en préfixant par le texte demandé (ex: "albert a dit: ...") et adapter la casse/spaces.
     e. Insérer le commentaire en préservant l'indentation et le style du fichier.
     f. Sauvegarder la copie modifiée dans le même chemin (optionnel: créer sauvegarde `.bak`).
  3. Générer un rapport sommaire des fichiers modifiés et des insertions (ligne, contexte).

Décisions et points de branchement:
  - Si le point d'insertion est ambigu, demander une confirmation avant modification.
  - Si le fichier contient des marqueurs `TODO` ou `FIXME`, proposer d'insérer là en priorité.
  - Proposer une option `--dry-run` pour afficher les changements sans les écrire.

Critères de qualité (checks):
  - Les commentaires utilisent la syntaxe correcte pour le langage détecté.
  - Le code n'est pas modifié en dehors de l'ajout de commentaires.
  - Les indentations et conventions de style existantes sont respectées.
  - Les fichiers originaux sont sauvegardés si l'utilisateur le souhaite.

Clarifications à demander si manquant:
  - Préférez-vous `//` ou `/* ... */` pour C lorsque l'on insère plus d'une ligne ?
  - Faut-il créer des sauvegardes `.bak` avant modification ?
  - Voulez-vous que je parcoure récursivement un dossier ?

Exemples de prompts pour l'agent:
  - "Ajoute 'albert a dit: vérifier l'alignement' au-dessus de `pool_free` dans correction/09_memory_allocator.c"
  - "Parcours `exercices/` et ajoute `albert a dit: revoir les cas limites` aux fichiers qui contiennent TODO"
  - "Dry-run: montrer comment j'insérerai 'albert a dit: optimiser' dans `exercices/10_factorial.c`"

Étapes d'itération:
  - Implémenter une version `--dry-run` et demander un retour.
  - Ajouter option pour sauvegardes automatiques et restauration.
  - Supporter règles d'exception (ne pas annoter fichiers générés, binaires, etc.).

Notes de sécurité:
  - Ne pas insérer d'informations sensibles (clés, mots de passe) dans les commentaires.
  - Demander confirmation pour modifier un grand nombre de fichiers (>50).

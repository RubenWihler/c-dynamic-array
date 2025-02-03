# C Generic Dynamic Array Implementation

Une simple implémentation d'un tableau dynamique générique en C. Les éléments du tableau sont stockés dans un espace mémoire contigu. La taille des éléments est spécifiée lors de la création du tableau.

## 🚀 Fonctionnalités

- [x] Créer un tableau dynamique
- [x] Libérer un tableau dynamique
- [x] Insértion
  - [x] Insertion en fin de tableau
  - [x] Insertion indexée avec décalage des éléments
- [x] Suppression
  - [x] Suppression en fin de tableau
  - [x] Suppression indexée avec décalage des éléments
- [x] Réservation
- [x] Accès aux éléments
- [x] Possibilité de spécifier une fonction de destruction pour les éléments stockés

## 🚧 Limitations

- Les éléments stockés dans le tableau doivent **être de la même taille**.
- Les éléments stockés dans le tableau sont copiés lors de l'insertion (pour éviter cette copie, il est possible d'utiliser `dyn_array_reserve` qui retourne un pointeur vers l'emplacement mémoire réservé)

## 📊 Complexité

La complexité des opérations sur le tableau dynamique est la suivante :

| Opération | Complexité |
| --------- | ---------- |
| Accès     | O(1)       |
| Push      | O(1)       |
| Pop       | O(1)       |
| Insert    | O(n)       |
| Remove    | O(n)       |
| Reserve   | O(n)       |
| Destroy   | O(n)       |
| Count     | O(1)       |

## 📦 Utilisation

Il suffit d'inclure les fichiers `dyn_array.h` et `dyn_array.c` dans votre projet. Vous pouvez ensuite utiliser les fonctions déclarées dans `dyn_array.h` pour manipuler les tableaux dynamiques.

Le fichier `demo.c` contient un exemple d'utilisation de la bibliothèque. Il contient un exemple d'utilisation avec un type primitif et un exemple d'utilisation avec un type un peu plus complexe, qui contient un pointeur vers un bloc de mémoire alloué dynamiquement sur le tas.

Le fichier `benchmark.c` contient un exemple de comparaison de performances entre une insertion avec réservation et une insertion sans réservation.

## 🛠️ Compilation

Pour compiler les fichiers de démonstration, vous pouvez utiliser la commande suivante :

```bash
make demo
```

> Pour compiler et exécuter le fichier de démonstration.

```bash
make benchmark && ./benchmark 1000000
```

> Pour le benchmark, vous pouvez spécifier le nombre d'éléments à insérer en argument.

## 📝 Licence

Ce projet est sous licence Apache 2.0. Voir le fichier [LICENSE](LICENSE) pour plus d'informations.

## 📧 Contact

Si vous avez des questions ou des suggestions, n'hésitez pas à me contacter par e-mail à l'adresse suivante : [wihlerruben@gmail.com](mailto:wihlerruben@gmail.com)

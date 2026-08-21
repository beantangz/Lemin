# Lem-in

Projet 42 basé sur la recherche de chemins optimaux dans un graphe afin de faire passer toutes les fourmis de `##start` à `##end` en un minimum de tours.

## Structure globale

Le projet est séparé en plusieurs parties :

* `parser.py` : lit la map, récupère le nombre de fourmis, les rooms, `start`, `end` et les liens.
* `node.py` : représente une room et contient ses edges voisines.
* `edge.py` : représente une arête avec sa capacité et son arête résiduelle `rev`.
* `graph.py` : construit le graphe, cherche les chemins et gère le flow.
* `simulation.py` : répartit les fourmis sur les chemins sélectionnés et simule leurs déplacements.
* `main.py` : relie toutes les parties.

## Recherche des chemins

Le graphe utilise un système de **flow / graphe résiduel**.

Chaque lien possède :

```text
forward  : capacity = 1
backward : capacity = 0
```

Le `BFS` cherche un chemin disponible entre `start` et `end`.

Quand un chemin est trouvé :

```python
edge.capacity -= 1
edge.rev.capacity += 1
```

Cela permet aussi aux prochains BFS de revenir sur certains choix grâce aux arêtes résiduelles.

## Choix de la meilleure solution

On ne garde pas forcément le dernier état du flow.

Après chaque augmentation :

```text
BFS
↓
construction du chemin
↓
ajout du flow
↓
extraction des chemins actuels
↓
calcul du nombre de tours
↓
comparaison avec la meilleure solution
```

On conserve la combinaison qui fait arriver toutes les fourmis en un minimum de tours.

Cela permet par exemple :

```text
1 fourmi
→ préférer un seul chemin très court

beaucoup de fourmis
→ préférer plusieurs chemins parallèles
```

## Simulation

Une fois les meilleurs chemins trouvés, `simulation.py` :

1. calcule combien de fourmis envoyer sur chaque chemin ;
2. fait avancer les fourmis d'une room par tour ;
3. injecte progressivement de nouvelles fourmis ;
4. affiche uniquement les mouvements effectués.

Exemple :

```text
L1-1 L2-3
L1-5 L2-4 L3-1 L4-3
L1-6 L3-5 L2-2 L4-4
L1-end L3-6 L2-end L4-2
L3-end L4-end
```

## Idée principale

Le but n'est pas simplement de trouver **le chemin le plus court**, mais la **meilleure combinaison de chemins en fonction du nombre de fourmis**.

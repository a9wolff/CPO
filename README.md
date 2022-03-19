# Projet CPO

---
GILLES, LE VU, WOLFF, DUPUY

## Projet

Créer une application de visualisation de données géographiques mondiales.

Les données proviennent de l'**Organisation Mondiale de la Santé** et de leur portail **Global Health Observatory**.

## Détails

Le projet est divisé en deux parties : une première partie en **Python** pour la récupération et le traitement des données,
et une seconde partie en **C++** pour l'aspect graphique de l'application.

Le code **Python** est fortement orienté object et utilise les bibliothèques *pandas* et *geopandas* pour le traitement des données.

Le code **C++** est plus technique et moins intéressant du point de vue orienté object.
La partie graphique de l'application s'appuis sur l'interface *OpenGL* et sur les bibliothèques *GLEW*, *GLFW*, *GLM* et *Dear ImGui*.

## Build

Le projet est construit avec **makefile** pour Windows. Les *targets* utilisables sont :

- *clean* : supprime les fichers **.o**, **.d**, **.exe**
- *clear* : supprime les fichers **.o**, **.d**
- *rebuild* : compile et link l'entièreté du projet
- *all* : clean, rebuild puis clear le projet pour ne laisser que l'éxécutable (à privilégier)

Les arguments et autres options de constructions sont disponibles en haut du fichier *GNUmakefile* (opt, clang, no-warn).

## Git

Pour définir son nom et mail :
```
git config --global user.name "T. Dupuy"
git config --global user.email t9dupuy@enib.fr
```

Pour récupérer le projet (la première fois), dans un dossier *projet_cpo* (peu importe le nom):
```
git init
git remote add origin https://github.com/t9dupuy/CPO
git pull
```

### Pour commencer à travailler

On récupère la dernière version du projet

```
git checkout master
git pull
```

On créé une nouvelle branche pour faire nos ajouts/modifications (en précisant sur quoi on travaille)
```
git branch titouan-classe-voiture
git checkout titouan-classe-voiture
```

On travaille et on peut regarder quels fichiers ont été modifiés ou ajoutés
```
git status
```

On fait quelques *commits* aux moments importants (avec un message explicit)
```
git add Voiture.cpp Voiture.hpp
git status
git commit -m "Création de la classe Voiture et de son constructeur"
```

### Pour finir de travailler

Une fois finit de travailler on envoie ses modifications
```
git push -u origin titouan-classe-voiture
```

Après cette opération on a la possibilité de créer une **pull request (PR)** sur Github.
Le but d'une PR est de regarder les changements effectuer et du décider ou non d'appliquer les changements faits à la branche principale *master*.

C'est pourquoi si on est pas **sûr** de ses changements on ne fait rien de plus.


# Python

**Programme final :** créé une carte du monde (fichier *JPG*) avec les pays coloriés selon un indicateur spécifique. Une image d'échelle est également créée.

Commande pour éxécution:
```
python <program_name> <indicator_to_visualize> <max_res>
```

*indicator_to_visualize* : donnée à visualiser (ex: *"Pollution de l'air"*)

*max_res* : résolution maximale (ex: *"16384"*)

## Dans le programme / A faire

---

### Récupération et vérification des arguments d'éxécution

Utiliser la librairie *sys* pour récupérer les arguments passer dans la commande d'éxécution (`sys.argv[]`). On vérifie le nombre et la validité des arguments.


### Classe de lecture des données brutes

Les données brutes sont récupérables depuis un dossier *data* et sont archivées en format *.csv*.

Utiliser la bibliothèque *pandas* pour gérer les données : on ne veut pas récupérer toutes les données, seulement ce qui nous intéresse (le bon fichier et les bonnes colonnes). Cette classe utilise les arguments de commande.


### Classe(s) de données

Une classe de données pour stocker les données précédemment lues et traitées. Cette classe utilise sûrement d'autre classes et sous-classes pour encapsuler efficacement les données.


### Classe de création des images finales

Une classe qui utilise les données collectées et stockées pour créer une carte en couleur. Cette classe utilise également les arguments de commande.

Utiliser la bibliothèque *geopandas* pour créer et colorier la carte et la bibliothèque *matplotlib* pour créer la légende de la carte.
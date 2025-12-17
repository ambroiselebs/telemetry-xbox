# Assetto Corsa Telemetry Analyzer

Un outil de capture et d'analyse de télémétrie pour Assetto Corsa, développé en C++ avec SFML.

## Auteur

**ambroiselebs**

## Description

En tant que joueur passionné d'Assetto Corsa, j'ai créé cet outil pour capturer et analyser mes données de télémétrie en temps réel. Le programme enregistre les inputs de la manette (freinage et accélération) pendant les sessions de jeu et permet de les visualiser sous forme de graphiques pour analyser son pilotage.

## Fonctionnalités

- **Capture en temps réel** : Enregistrement des inputs de freinage (LT) et d'accélération (RT) via manette Xbox
- **Horodatage précis** : Chaque input est enregistré avec un timestamp à la milliseconde
- **Visualisation graphique** : Interface de visualisation interactive avec SFML
- **Contrôles intuitifs** :
  - Démarrage/arrêt de l'enregistrement avec le bouton A de la manette
  - Zoom et navigation dans les graphiques
- **Export des données** : Sauvegarde des sessions au format CSV

## Comment ça fonctionne

### Architecture

Le programme fonctionne en deux modes :

#### 1. Mode Enregistrement
- Utilise l'API XInput pour lire les inputs de la manette Xbox
- Capture les valeurs des gâchettes gauche (LT - frein) et droite (RT - accélérateur)
- Convertit les valeurs brutes (0-255) en pourcentages (0-100%)
- Enregistre chaque donnée avec un horodatage précis au format `HH-MM-SS-mmm,pourcentage,input`
- Sauvegarde les données dans des fichiers séparés pour le frein et l'accélération

#### 2. Mode Visualisation
- Charge les fichiers de télémétrie enregistrés
- Affiche les données sous forme de graphiques :
  - **Rouge** : Freinage (LT)
  - **Cyan** : Accélération (RT)
- Permet de zoomer et scroller pour analyser en détail les différentes phases de conduite

### Flux de données

```
Manette Xbox → XInput API → Controller → OutFile → Fichiers CSV
                                                       ↓
                                    GraphLoader ← Fichiers CSV
                                         ↓
                                  Visualisation SFML
```

## Prérequis

- **Système d'exploitation** : Windows (utilise XInput et des bibliothèques Windows)
- **Compilateur** : g++ (MinGW recommandé)
- **Bibliothèques** :
  - SFML 2.x (incluse dans `lib/SFML`)
  - XInput (xinput1_4.dll ou xinput1_3.dll)
- **Matériel** : Manette Xbox compatible XInput

## Compilation

Le projet utilise un Makefile pour la compilation :

```bash
# Compiler le projet
make

# Nettoyer les fichiers objets
make clean

# Nettoyer complètement (objets + exécutable)
make fclean

# Recompiler complètement
make re
```

### Détails de compilation

- **Flags de compilation** : `-Wall -Wextra -DSFML_STATIC`
- **Bibliothèques liées** : SFML Graphics, Window, System (statiques) + OpenGL32, WinMM, GDI32
- **Include paths** : `includes/` et `lib/SFML/include`

## Utilisation

### Lancer le programme

Le programme nécessite deux arguments en ligne de commande pour spécifier les fichiers de sortie :

```bash
./analyzer.exe [file_brake] [file_throttle]
```

**Exemple :**
```bash
./analyzer.exe out/test/brake out/test/throttle
```

Au lancement, vous aurez le choix entre deux options :

```
What do you want :
  - Record entries (1)
  - Visualizer (2)
```

### Mode Enregistrement (1)

1. Lancez le programme avec les chemins des fichiers de sortie souhaités
2. Sélectionnez l'option 1 (Record entries)
3. Le programme détecte automatiquement votre manette
4. Appuyez sur le **bouton A** pour démarrer l'enregistrement
5. Jouez à Assetto Corsa normalement
6. Appuyez à nouveau sur **A** pour arrêter l'enregistrement
7. Les données sont sauvegardées dans les fichiers spécifiés

### Mode Visualisation (2)

1. Lancez le programme avec les chemins des fichiers de télémétrie à visualiser
2. Sélectionnez l'option 2 (Visualizer)
3. Une fenêtre SFML s'ouvre affichant vos données de télémétrie
4. Utilisez les contrôles suivants :
   - **Molette de la souris** : Scroller horizontalement
   - **Flèche Haut** : Zoomer
   - **Flèche Bas** : Dézoomer

### Interprétation des graphiques

- L'axe vertical représente le pourcentage d'appui (0-100%)
- L'axe horizontal représente le temps
- Des grilles horizontales sont affichées tous les 25% pour faciliter la lecture
- La ligne rouge montre votre freinage
- La ligne cyan montre votre accélération

## Structure du projet

```
analyzer/
├── main.cpp                 # Point d'entrée du programme
├── includes/
│   ├── Controller.hpp       # Gestion de la manette et capture des inputs
│   ├── GraphLoader.hpp      # Visualisation des graphiques
│   └── OutFile.hpp          # Gestion de l'écriture dans les fichiers
├── src/
│   ├── Controller.cpp       # Implémentation de la capture XInput
│   ├── GraphLoader.cpp      # Implémentation du visualiseur SFML
│   └── OutFile.cpp          # Implémentation de l'écriture de fichiers
├── lib/
│   └── SFML/                # Bibliothèque SFML
├── out/
│   └── test/                # Dossier de sortie des données
│       ├── brake            # Données de freinage
│       └── throttle         # Données d'accélération
├── Makefile                 # Script de compilation
└── *.dll                    # DLLs SFML et OpenAL nécessaires
```

## Format des données

Les fichiers de télémétrie utilisent le format CSV suivant :

```
HH-MM-SS-mmm,pourcentage,input_type
```

Exemple :
```
14-23-45-123,75,LT
14-23-45-223,82,RT
```

# Projet informatique - C++
## Elise LEI
&nbsp;
## Chiffrement en Morse

Ce code a pour but de chiffrer et déchiffrer des textes en Morse.

Dans les textes, les caractères autorisés sont :
- les lettres de l'alphabet (non accentuées)
- les chiffres
- les signes de ponctuations suivants : . , ? ' ! / ( ) & : ; = + - _ " @

## En pratique

Pour compiler le code, un fichier `Makefile` est fourni. Taper la commande `make`.

Un exécutable `morse` sera alors créé. Utiliser la commande `./morse` pour lancer le programmme, et suivre les indications de l'IA (ou un semblant d'IA).

## Guide des tests
Le dossier `text` contient les fichiers texte, le dossier `wave` contient quant à lui les fichiers audio. Entrer les emplacements correspondants lors de l'exécution du programme.

Les messages contenus dans les fichiers audio sont contenus en clair dans `cheat.txt`.

## Dictionnaire du Morse

| Lettre | Morse || Lettre | Morse |  
|:---:|:---:|--|:---:|:---:|
|a |.-   || 1 | .---- |
|b |-...|| 2 | ..--- |
|c |-.-.|| 3 | ...-- |
|d |-..|| 4 | ....- |
|e |.|| 5 | ..... |
|f |..-.|| 6 | -.... |
|g |--.|| 7 | --... |
|h |....|| 8 | ---.. |
|i |..|| 9 | ----. |
|j |.---|| 0 | ----- |
|k |-.-|| . | .-.-.- |
|l |.-..|| , | --..-- |
|m |--|| ? | ..--.. |
|n |-.|| ' | .----. |
|o |---|| ! | -.-.-- |
|p |.--.|| / | -..-. |
|q |--.-|| ( | -.--. |
|r |.-.|| ) | -.--.- |
|s |...|| & | .-... |
|t |-|| : | ---... |
|u |..--|| ; | -.-.-. |
|v |...-|| = | -...- |
|w |.--|| + | .-.-. |
|x |-..-|| - | -....- |
|y |-.--|| _ | ..--.- |
|z |--..|| " | .-..-. |
|  |    || @ | .--.-. |
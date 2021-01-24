#ifndef CODE_USAGE
#define CODE_USAGE

#include "BinTree.h"

//Initialisation de l'abre servant à encoder et décoder
void initTree(BinTree<char>& keyTree);


/*Encodage string -> morse
Option de souplesse par rapport au cractère possible : activée (les caractères non supportés deviennent des espaces)
Pour la désactiver, commenter lignes 14 à 20 (dans MorsCode.cpp), et décommenter le bloc initialement commenté*/
std::string encrypt(BinTree<char> const& keyTree, std::string const phrase);


//Décodage morse -> string
std::string decrypt(BinTree<char> const& keyTree, std::string const message);


#endif
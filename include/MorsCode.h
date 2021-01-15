#ifndef CODE_USAGE
#define CODE_USAGE

#include "BinTree.h"

//Initialisation de l'abre servant à encoder et décoder
void initTree(BinTree<char>& keyTree);


//Encodage string -> morse
std::string encrypt(BinTree<char> const& keyTree, std::string const phrase);


//Décodage morse -> string
std::string decrypt(BinTree<char> const& keyTree, std::string const message);


#endif
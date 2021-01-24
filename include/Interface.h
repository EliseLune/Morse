#ifndef FUNC_INTERFACE
#define FUNC_INTERFACE

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

//Dialogue lors d'un choix de l'utilisateur parmi 2 options
char AorB();

//Coder en morse ou décrypter un audio ?
char firstInteraction();

//Terminal ou fichier texte ?
char strOrTxt(bool const encode);

//Dialogue lorsque l'utilisateur entre un nom de fichier, wav ou txt
std::string askFileName(std::string const extension);

//Entrée dans le terminal du message à encoder
std::string readEntry();

//Lecture du message dans un fichier texte
std::string readTxt(std::string const txtName);

//Affichage dans le terminal du message en clair
void writeStr(std::string const message);

//Ecriture du message dans un fichier texte
void writeTxt(std::string const txtName, std::string const message);

//Petit message d'adieu
void lastLine();

#endif
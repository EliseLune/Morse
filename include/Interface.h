#ifndef FUNC_INTERFACE
#define FUNC_INTERFACE

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

char AorB(); //dialogue lors d'un choix de l'utilisateur parmi 2 options

char firstInteraction(); //coder en morse ou décrypter un audio ?

char strOrTxt(bool const encode); //terminal ou fichier texte ?

std::string askFileName(std::string const extension); //dialogue lorsque l'utilisateur entre un nom de fichier, wav ou txt

std::string readEntry(); //entrée dans le terminal le message à encoder

std::string readTxt(std::string const txtName); //lecture du message dans un fichier texte

void writeStr(std::string const message); //affichage dans le terminal du message en clair

void writeTxt(std::string const txtName, std::string const message); //écriture du message dans un fichier texte

void lastLine(); //petit message d'adieu

#endif
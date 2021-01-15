#include "Interface.h"

char firstInteraction() {
    std::cout << "Bonjour ! Je suis Hector. Que souhaitez-vous ?\n" << "    a. Chiffrer un message en Morse\n" << "    b. Déchiffrer un message\n" << "Votre réponse : ";
    
    char answer;
    std::cin >> answer ;
    std::cout << "\n";
    return answer;
}

char strOrTxt() {
    std::cout << "Désirez-vous entrer le message vous-même, ou me le transmettre dans un fichier texte ?\n    a. entrée\n    b. texte\n" << "Votre réponse : ";
    
    char answer;
    std::cin >> answer;
    std::cout << "\n";
    return answer;
}

std::string msgEntry() {
    std::cout << "Veuillez entrer votre message :\n";
    std::string answer;
    std::cin.ignore();
    getline(std::cin,answer);
    std::cout << "\n";
    return answer;
}

std::string msgTxt() {
    std::cout << "Veuillez entrer l'emplacement de votre fichier (sous forme \"dossier/nom.txt\")\n";
    std::string answer, temp, message("");
    std::cin >> answer;
    std::cout << "\n";
    
    std::ifstream file(answer.c_str());
    while(getline(file,temp)) {
        message += temp;
    }
    file.close();
    return message;
}
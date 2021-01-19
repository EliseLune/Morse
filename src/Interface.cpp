#include "Interface.h"

char firstInteraction() {
    std::cout << "Bonjour ! Je suis Hector. Que souhaitez-vous ?\n" << "    a. Chiffrer un message en Morse\n" << "    b. Déchiffrer un message\n";
    
    char answer('0');
    while(answer!='a' && answer!='b') {
        std::cout << "Votre réponse : ";
        std::cin >> answer ;
        std::cout << "\n";
        if(answer=='a' || answer=='b') return answer;
        else std::cout << "Réponse invalide.\n";
    }
    
    std::cerr << "ERROR : AI not working at first interaction";
    return ' ';
}

char strOrTxt() {
    std::cout << "Désirez-vous entrer le message vous-même, ou me le transmettre dans un fichier texte ?\n    a. saisie\n    b. texte\n";
    
    char answer('0');
    while(answer!='a' && answer!='b') {
        std::cout << "Votre réponse : ";
        std::cin >> answer ;
        std::cout << "\n";
        if(answer=='a' || answer=='b') return answer;
        else std::cout << "Réponse invalide.\n";
    }
    
    std::cerr << "ERROR : AI not working at second interaction";
    return ' ';
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
    std::cout << "Veuillez saisir l'emplacement de votre fichier (sous forme \"dossier/nom.txt\")\n";
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

std::string askFileName(bool cin) {
    std::cout << "Veuillez saisir le nom du fichier WAV souhaité (sous la forme \"dossier/nom.wav\")\n";
    std::string answer;
    if(cin) std::cin.ignore();
    getline(std::cin, answer);
    return answer;
}

void lastLine() {
    std::cout << "Ce fut un plaisir de travailler avec vous. Bonne journée !\n";
}
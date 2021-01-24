#include "Interface.h"

char AorB() {
    std::string answer("");
    while(answer!="a" && answer!="b" && answer!="A" && answer!="B") {
        std::cout << "Votre réponse : ";
        getline(std::cin, answer);
        std::cout << "\n";
        if(answer=="a" || answer=="b" || answer=="A" || answer=="B") {
            return (char)tolower(answer[0]);
        }
        else std::cout << "    Réponse invalide\n";
    }
    throw std::runtime_error("In AorB, interrupted dialogue ...\n");
    return ' ';
}

char firstInteraction() {
    std::cout << "Bonjour ! Je suis Hector. Que souhaitez-vous faire ?\n" << "    a. Chiffrer un message en Morse\n" << "    b. Déchiffrer un message\n";
    
    return AorB();
}

char strOrTxt(bool const encode) {
    if(encode)
        std::cout << "Désirez-vous entrer le message vous-même, ou me le transmettre dans un fichier texte ?\n    a. saisie\n    b. fichier texte\n";
    else
        std::cout << "Désirez-vous que j'affiche le message en clair directement ici, ou que que je vous le sauvegarde dans un fichier texte ?\n    a. ici\n    b. fichier texte\n";
    
    return AorB();
}

std::string askFileName(std::string const extension) {
    std::cout << "Veuillez saisir le nom de votre fichier ." << extension << " (sous forme \"dossier/nom." << extension << "\")\n";
    std::string answer;
    getline(std::cin, answer);
    std::cout << "\n";
    return answer;
}

std::string readEntry() {
    std::cout << "Veuillez entrer votre message :\n";
    std::string answer;
    getline(std::cin,answer);
    std::cout << "\n";
    return answer;
}

std::string readTxt(std::string const txtName) {
    std::string message(""), temp;
    std::ifstream file(txtName.c_str());
    while(getline(file,temp)) {
        message += temp + " ";
    }
    file.close();
    return message;
}

void writeStr(std::string const message) {
    std::cout << "\n#----------- MESSAGE -----------#\n\n" << message << "\n\n#------- FIN DU MESSAGE --------#\n\n";
}

void writeTxt(std::string const txtName, std::string const message) {
    std::ofstream file(txtName.c_str());
    file << message;
    file.close();
    std::cout << "Fichier texte créé !\n";
}

void lastLine() {
    std::cout << "\nCe fut un plaisir de travailler avec vous. Bonne journée !\n\n";
}
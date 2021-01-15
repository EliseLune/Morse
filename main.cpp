#include "MorsCode.h"
#include "Interface.h"

int main() {
    BinTree<char> keyTree(6);
    initTree(keyTree);
    
    char choice1(firstInteraction());
    //a = encoder ; b = décoder
    if(choice1=='a') {
        std::string message, morse;
        char choice2(strOrTxt()); //a = entrée ; b = txt
        if(choice2=='a')
            message = msgEntry();
        else
            message = msgTxt();
        morse = encrypt(keyTree, message);
        std::cout << morse << "\n" << decrypt(keyTree, morse) << "\n";
    }
    else {
        //Entrée = audio ; sortie = string
    }
    
    return 0;
}
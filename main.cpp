#include "MorsCode.h"
#include "Interface.h"
#include "Wave.h"

int main() {
    BinTree<char> keyTree(6);
    initTree(keyTree);
    
    char choice1(firstInteraction());
    //a = encoder ; b = décoder
    if(choice1=='a') {
        std::string message, morse, fileName;
        char choice2(strOrTxt()); //a = entrée ; b = txt
        if(choice2=='a') {
            message = msgEntry();
            fileName = askFileName();
        }
        else {
            message = msgTxt();
            fileName = askFileName(true);
        }
        morse = encrypt(keyTree, message);
        OutWav crypted(fileName);
        crypted.write(morse);
        std::cout << "\n" << morse << "\n" << decrypt(keyTree, morse) << "\n\n";
    }
    else {
        //Entrée = audio ; sortie = string
    }
    
    lastLine();
    
    //TEST WAVE.H
    /*OutWav f("tests/ex1.wav");
    f.write("... --- ... / .--. .-.. . .- ... . / .... . .-.. .--.");*/
    
    return 0;
}
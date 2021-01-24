#include "MorsCode.h"
#include "Interface.h"
#include "Wave.h"

int main() {
    try {
        BinTree<char> keyTree(6);
        initTree(keyTree);
        
        char choice1(firstInteraction()), choice2;
        std::string message, morse, wavName;
        //a = encoder ; b = décoder
        if(choice1=='a') {
            choice2 = strOrTxt(true); //a = entrée ; b = txt
            if(choice2=='a')
                message = readEntry();
            else
                message = readTxt(askFileName("txt"));
            morse = encrypt(keyTree, message);
            wavName = askFileName("wav");
            OutWav crypted(wavName);
            crypted.write(morse);
        }
        else {
            //Entrée = audio ; sortie = string
            wavName = askFileName("wav");
            InWav crypted(wavName);
            morse = crypted.read();
            message = decrypt(keyTree, morse);
            choice2 = strOrTxt(false);
            if(choice2=='a')
                writeStr(message);
            else
                writeTxt(askFileName("txt"), message);
        }
        
        lastLine();
    }
    catch(std::exception const& e) {
        std::cerr << "ERROR : " << e.what() << "\n";
    }
    //TEST WAVE.H
    /*InWav f("tests/test.wav");
    //f.testing();
    std::string morse;
    try {
        morse = (f.read());
        std::cout << decrypt(keyTree, morse) << "\n";
    }
    catch (int n) {
        std::cerr << "ERROR : durée du son incohérente à la " << n << "e itération\n";
    }
    catch (std::string e) {
        std::cerr << "Message décodé jusqu'ici : " << e << "\n";
    }
    std::string morse(f.read());
    std::cout << morse << "\n" << decrypt(keyTree, morse) << "\n";*/
    
    return 0;
}
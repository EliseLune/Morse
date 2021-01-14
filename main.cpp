#include "MorsCode.h"

int main() {
    BinTree<char> keyTree(6);
    initTree(keyTree);
    
    //TESTS
    std::string entry, morse;
    getline(std::cin, entry);
    morse = encrypt(keyTree, entry);
    std::cout << morse << "\n";
    std::cout << decrypt(keyTree, morse) << "\n";
    
    return 0;
}
#include "MorsCode.h"

void initTree(BinTree<char>& keyTree) {
    int const n = 121;
    char content[n] = " etianmsurwdkgohvf l pjbxcyzq  54 3   2& +    16=/   ( 7   8 90            ?_    \"  .    @   '  -        ;! )     ,    :";
    keyTree.change(n,content);
}

std::string encrypt(BinTree<char> const& keyTree, std::string const phrase) {
    std::string const allowed = "abcdefghijklmnopqrstuvwxyz0123456789.,?'!/()&:;=+-_\"@";
    std::string final("");
    char temp;
    for(unsigned int i=0; i<phrase.size(); i++) {
        temp = (char)tolower(phrase[i]);
        if(allowed.find(temp) != std::string::npos)
            final += keyTree.encode(temp);
        else if(temp==' ')
            final += '/';
        if(i<final.size()-1)
            final += ' ';
    }
    return final;
}

std::string decrypt(BinTree<char> const& keyTree, std::string const message) {
    std::string final(""), temp("");
    for(unsigned int i=0; i<=message.size(); i++) {
        if(i==message.size() || message[i]==' ') {
            final += keyTree.decode(temp);
            temp = "";
        }
        else if(message[i]=='/') {
            continue;
        }
        else {
            temp += message[i];
        }
    }
    return final;
}
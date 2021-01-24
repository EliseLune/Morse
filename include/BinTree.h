#ifndef DEF_BINTREE
#define DEF_BINTREE

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

template <typename T>
class BinTree {
    protected:
        int depth_;
            //profondeur de l'arbre (1 arbre-racine : profondeur de 0)
        T* table_;
    public:
        BinTree(int depth);
        ~BinTree();
        int getDepth() const;
        int getSize() const;
        void change(int const k, T const elem);
            //remplace l'élément d'indice k par elem
        void change(int const n, T* const newCon);
            //remplace les n premiers éléments par ceux de newCon
        void change(T const elem);
            //remplace tous les éléments par elem
        void print() const;
        
        /*------ Décodage morse -> caractère ------*/
        /*ie trouver étiquette d'une feuille à partir d'un emplacement*/
        T decode(std::string const morsChar) const;
        
        /*---- Encodage caractère -> morse ----*/
        /*ie trouver le caractère et retouner son emplacement, ie l'écriture en binaire de son indice*/
        std::string encode(T const elem) const;
};

#include "BinTree_impl.h"

#endif
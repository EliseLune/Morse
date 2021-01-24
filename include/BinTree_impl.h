#include "BinTree.h"

/*--------------------------------------------------------*/
/*--------------- Implémentation générale ----------------*/
/*--------------------------------------------------------*/

//Constructeur
template <typename T>
BinTree<T>::BinTree(int n) : depth_(n) {
    table_ = new T[(int)pow(2,n+1)-1];
}

//Destructeur
template <typename T>
BinTree<T>::~BinTree() {
    delete[] table_;
}

//Méthodes
template <typename T>
int BinTree<T>::getDepth() const {
    return depth_;
}

template <typename T>
int BinTree<T>::getSize() const {
    return (pow(2,depth_+1)-1);
}

template <typename T>
void BinTree<T>::change(int const k, T const elem) {
    try {
        if(k < pow(2,this->getSize())-1)
            table_[k] = elem;
        else
            throw k;
    }
    catch(int indice) {
        std::cout << "ERROR : Dépassement de la taille du tableau\n";
    }
}

template <typename T>
void BinTree<T>::change(int const n, T* const newCon) {
    for(int i=0; i<n && i<this->getSize(); i++)
        table_[i] = newCon[i];
}

template <typename T>
void BinTree<T>::change(T const elem) {
    for(int i=0; i<this->getSize(); i++)
        table_[i] = elem;
}

template <typename T>
void BinTree<T>::print() const {
    int index(0);
    for(int i=0; i<=this->getDepth(); i++) {
        for(int j=0; j<pow(2,i); j++) {
            std::cout << table_[index] << " ";
            index++;
        }
        std::cout << "\n";
    }
}

/*--------------------------------------------------------*/
/*----------------------- Décodage -----------------------*/
/*--------------------------------------------------------*/

template <typename T>
T BinTree<T>::decode(std::string const morsChar) const {
    int index(0), i(0);
    while(i < (int)morsChar.size()) {
        if(morsChar[i]=='.') //dit = fils gauche
            index = 2*index+1;
        else if(morsChar[i]=='-')//daah = fils droit
            index = 2*index+2;
        else throw std::invalid_argument("In BinTree::decode, unknown character to the morse alphabet -> "+morsChar[i]); //ERREUR : le std::string ne contient pas que des . et des -
        i++;
    }
    return table_[index];
}

/*--------------------------------------------------------*/
/*----------------------- Encodage -----------------------*/
/*--------------------------------------------------------*/

template <typename T>
std::string BinTree<T>::encode(T const elem) const {
    //Recherche du caractère dans l'arbre, par profondeur croissante
    int index(0);
    while(index < this->getSize() && table_[index] != elem)
        index++;
    
    std::string morsChar("");
    if(index == this->getSize())
        throw std::out_of_range("In BinTree::encode, unavailable character (I can't translate it in morse)"); //ERREUR : caractère introuvé
    else {
        //Ecriture du code morse comme en binaire, avec 0 = . ; 1 = -
        int remain;
        while(index > 0) {
            remain = index%2;
            if(remain==0) {
                morsChar = "-" + morsChar;
                index = (index-2)/2;
            }
            else {
                morsChar = "." + morsChar;
                index /= 2;
            }
        }
        return morsChar;
    }
}
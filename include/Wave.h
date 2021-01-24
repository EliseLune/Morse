#ifndef DEF_WAVE
#define DEF_WAVE

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>


class Wave {
    protected:
        static constexpr double amplitude = 32760; //volume
        
        int fileSize_;
        const unsigned int blocSize_ = 16; //standard
        unsigned int audioFormat_; //1 = PCM
        unsigned int nbrChannels_;
        unsigned int sampPerSec_; //11 025, 22 050, 44 100
        unsigned int bytePerSec_;
        unsigned int bytePerBloc_;
        unsigned int bitsPerSamp_; //8, 16, 24
        int dataSize_;
        
        Wave();
};

/*--------------------------------------------------------*/
/*---------- OutWav : création d'un fichier Wav ----------*/
/*--------------------------------------------------------*/

class OutWav : public Wave {
    private:
        static constexpr double twoPi = 6.283185307179586476925286766559;
        static constexpr double frequency = 261.626; //middle C
        
        std::ofstream file_;
        int unit_; //unité du code morse, en nombre d'échantillons par unité de temps (0.2s); par défaut, 0.2 s => sampPerSec_/5
        
        template <typename T>
        void writeWord(T something, unsigned size = sizeof(T)); //Ecrit quelque chose en binaire petit-boutiste dans file_
        void writeSound(int const timeLength, bool sinus = false); //Ecrit le son d'une durée de timeLength (en nombre d'échantillons)
        void writeSign(char const sign); //Ecrit le son correspondant à sign
        void wHeader(); //Ecrit le header du fichier wav
        void wData(std::string const morse); //Ecrit les données du fichier son
        void wSize(); //Complète avec les informations manquantes
    public:
        OutWav(std::string fileName);
        ~OutWav();
        void write(std::string const morse); //Ecrit le message en morse dans file_
};

template <typename T>
void OutWav::writeWord(T something, unsigned size) {
    for(; size; size--, something >>= 8) {
        file_.put((char)(something & 0xFF));
        fileSize_++;
    }
}

/*--------------------------------------------------------*/
/*----------- InWav : lecture d'un fichier Wav -----------*/
/*--------------------------------------------------------*/

class InWav : public Wave {
    private:
        static constexpr int epsVolume = (int)amplitude / 100; //seuil en-dessous duquel on compte le volume comme nul
        
        std::ifstream file_;
        int epsTime_; //sons de durée plus courte : négligés
        int minUnit_; //la plus petite unité de temps possible
        
        int readWord(int size);
        void setBlanks(std::vector<std::streampos>& tab);
        void setUnit(std::vector<std::streampos> const& tab);
    public:
        InWav(std::string fileName);
        ~InWav();
        void testing();
        std::string read();
};

#endif
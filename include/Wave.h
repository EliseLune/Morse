#ifndef DEF_WAVE
#define DEF_WAVE

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


class Wave {
    protected:
        static constexpr double twoPi = 6.283185307179586476925286766559;
        static constexpr double amplitude = 32760; //volume
        static constexpr double frequency = 261.626; //middle C
        
        double unit_;
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

class OutWav : public Wave {
    private:
        std::ofstream file_;
        template <typename T>
        void writeWord(T something, unsigned size = sizeof(T)); //Ecrit quelque chose en binaire petit-boutiste dans un ostream
        void writeSound(double const timeLength, bool sinus = false); //Ecrit le son d'une durée de timeLength
        void writeSign(char const sign); //Ecrit le son correspondant à sign
        void wHeader(); //Ecrit le header du fichier wav
        void wData(std::string const morse); //Ecrit les données du fichier son
        void wSize(); //Complète avec les informations manquantes
    public:
        OutWav(std::string fileName);
        ~OutWav();
        void write(std::string const morse);
};

template <typename T>
void OutWav::writeWord(T something, unsigned size) {
    for(; size; size--, something >>= 8) {
        file_.put((char)(something & 0xFF));
        fileSize_++;
    }
}

#endif
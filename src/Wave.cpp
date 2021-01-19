#include "Wave.h"

Wave::Wave() :
    unit_(0.2), fileSize_(-8), audioFormat_(1), nbrChannels_(1), sampPerSec_(44100), bitsPerSamp_(16), dataSize_(0)
{
    bytePerBloc_ = nbrChannels_ * bitsPerSamp_ / 8;
    bytePerSec_ = sampPerSec_ * bytePerBloc_;
}


/*--------------------------------------------------------*/
/*---------- OutWav : création d'un fichier Wav ----------*/
/*--------------------------------------------------------*/

OutWav::OutWav(std::string fileName) : Wave() {
    file_.open(fileName.c_str(), std::ios::binary);
}

OutWav::~OutWav() {
    if(file_.is_open())
        file_.close();
}

void OutWav::writeSound(double const timeLength, bool sinus) {
    int totSamp(sampPerSec_ * timeLength), value(0);
    for(int n=0; n<totSamp; n++) {
        if(sinus)
            value = amplitude * sin(twoPi * frequency * n / sampPerSec_);
        this->writeWord(value, bitsPerSamp_/8);
        dataSize_ += bitsPerSamp_/8;
    }
}

void OutWav::writeSign(char const sign) {
    double length;
    bool sinus(sign=='.' || sign=='-');
    switch(sign) {
    case '.':
        length = unit_;
        break;
    case '-':
        length = 3*unit_;
        break;
    case ' ':
        length = 2*unit_;
        break;
    case '/':
        length = 0;
        break;
    default:
        std::cerr << "ERROR : input string not valid\n";
        break;
    }
    if(length>0) this->writeSound(length, sinus); //caractère
    this->writeSound(unit_); //1 silence de séparation
}

void OutWav::wHeader() {
    file_ << "RIFF----WAVEfmt ";
    fileSize_ += 16;
    this->writeWord(blocSize_, 4);
    this->writeWord(audioFormat_, 2);
    this->writeWord(nbrChannels_, 2);
    this->writeWord(sampPerSec_, 4);
    this->writeWord(bytePerSec_, 4);
    this->writeWord(bytePerBloc_, 2);
    this->writeWord(bitsPerSamp_, 2);
}

void OutWav::wData(std::string const morse) {
    file_ << "data----";
    fileSize_ += 8;
    for(char e: morse) {
        this->writeSign(e);
    }
}

void OutWav::wSize() {
    file_.seekp(std::ios::beg + 4);
    this->writeWord(fileSize_, 4);
    fileSize_ -= 4;
    file_.seekp(std::ios::beg + 40);
    this->writeWord(dataSize_, 4);
    fileSize_ -= 4;
}

void OutWav::write(std::string const morse) {
    this->wHeader();
    this->wData(morse);
    this->wSize();
}
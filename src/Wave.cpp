#include "Wave.h"

Wave::Wave() :
    fileSize_(-8), audioFormat_(1), nbrChannels_(1), sampPerSec_(44100), bitsPerSamp_(16), dataSize_(0)
{
    bytePerBloc_ = nbrChannels_ * bitsPerSamp_ / 8;
    bytePerSec_ = sampPerSec_ * bytePerBloc_;
}


/*--------------------------------------------------------*/
/*---------- OutWav : création d'un fichier Wav ----------*/
/*--------------------------------------------------------*/

OutWav::OutWav(std::string fileName) : Wave(), unit_(sampPerSec_/5) {
    file_.open(fileName.c_str(), std::ios::binary);
}

OutWav::~OutWav() {
    if(file_.is_open())
        file_.close();
}

void OutWav::writeSound(int const sampLength, bool sinus) {
    int value(0);
    for(int n=0; n<sampLength; n++) {
        if(sinus)
            value = amplitude * sin(twoPi * frequency * n / sampPerSec_);
        this->writeWord(value, bitsPerSamp_/8);
        dataSize_ += bitsPerSamp_/8;
    }
}

void OutWav::writeSign(char const sign) {
    int length;
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
        throw std::invalid_argument("In OutWav::writeSign, unknown character to the morse alphabet -> "+sign);
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
    this->writeSound(unit_); //un silence au début
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
    std::cout << "Fichier audio créé !\n";
}


/*--------------------------------------------------------*/
/*----------- InWav : lecture d'un fichier Wav -----------*/
/*--------------------------------------------------------*/

int InWav::readWord(int size) {
    int value(0);
    for(int i=0; i<size; i++) {
        value ^= (file_.get() << 8*i);
    }
    int sign(value >> (8*size-1));
    value -= sign*(int)pow(2, 8*size-1);
    if(sign) value =-value; //lecture d'un entier relatif -> gestion du signe (bit de poids le plus fort)
    return value;
}

InWav::InWav(std::string fileName) : minUnit_(-1) {
    file_.open(fileName.c_str(), std::ios::binary);
    file_.seekg(4, std::ios::beg);
    fileSize_ = this->readWord(4);
    
    file_.seekg(12, std::ios::cur);
    audioFormat_ = this->readWord(2);
    nbrChannels_ = this->readWord(2);
    sampPerSec_ = this->readWord(4);
    bytePerSec_ = this->readWord(4);
    bytePerBloc_ = this->readWord(2);
    bitsPerSamp_ = this->readWord(2);
    
    file_.seekg(4, std::ios::cur);
    dataSize_ = this->readWord(4);
    
    epsTime_ = sampPerSec_ / 1750;
}

InWav::~InWav() {
    if(file_.is_open())
        file_.close();
}

void InWav::testing() const {
    std::cout << "FileSize = " << fileSize_ << "\n";
    std::cout << "AudioFormat = " << audioFormat_ << "\n";
    std::cout << "NbrChannels = " << nbrChannels_ << "\n";
    std::cout << "Samples per second = " << sampPerSec_ << "\n";
    std::cout << "Bytes per second = " << bytePerSec_ << "\n";
    std::cout << "Bytes per bloc = " << bytePerBloc_ << "\n";
    std::cout << "Bits per sample = " << bitsPerSamp_ << "\n";
    std::cout << "DataSize = " << dataSize_ << "\n";
    
    /*file_.seekg(44, std::ios::beg);
    int totSamp = dataSize_ / bitsPerSamp_ * 8;
    for(int n=0; n<totSamp; n++) {
        std::cout << this->readWord(bitsPerSamp_/8) << " ";
    }
    std::cout << "\n";*/
}

void InWav::setBlanks(std::vector<std::streampos>& tab) {
    const int totSamp(dataSize_ / bitsPerSamp_ * 8); //nombre total d'échantillons à lire
    int value;
    bool silence(true), test; //'silence' = échantillons lus liés à un silence ou à un son
    file_.seekg(44, std::ios::beg);
    std::streampos begin(file_.tellg()), end(file_.tellg());
    for(int n=0; n<totSamp; n++) {
        value = this->readWord(bitsPerSamp_ /8);
        test = (value <= epsVolume && value >= -epsVolume); //si son perçu négligeable, considèré comme un silence
        if(silence && !test) { //si nous lisions un silence et percevons un son
            silence = false;
            end = file_.tellg();
            if(n < epsTime_ || epsTime_ < end-begin) { //si silence non négligeable ou son perçu dès le début du fichier
                tab.push_back(begin);
                tab.push_back(end);
            }
        }
        else if(!silence && test) {
            silence = true;
            if(epsTime_ < file_.tellg()-end) 
                begin = file_.tellg();
            else { //son négligeable, il faut donc continuer le silence précédent
                tab.pop_back();
                tab.pop_back();
            }
        }
        if(n > totSamp-epsTime_) { //correction des effets de bord -> dernier son
            tab.push_back(file_.tellg());
            tab.push_back(file_.tellg());
            break;
        }
    }
}

void InWav::setUnit(std::vector<std::streampos> const& tab) {
    int mini, temp;
    for(unsigned int i=1; i<tab.size()-1; i+=2) {
        temp = tab[i+1] - tab[i];
        if(i==1) mini = temp;
        else if(temp < mini) mini = temp;
    }
    minUnit_ = mini;
}

std::string InWav::read() {
    std::vector<std::streampos> silences;
    this->setBlanks(silences);
    this->setUnit(silences);
    int timeSpan;
    std::string morse("");
    for(unsigned int i=0; i<silences.size()-1; i++) {
        timeSpan = silences[i+1] - silences[i];
        if(i%2==0) { //silence
            if(3*minUnit_ <= timeSpan && timeSpan <= 6*minUnit_)
                morse += " ";
            else if(timeSpan > 6*minUnit_)
                morse += " / ";
        }
        else { //son
            if(minUnit_ <= 2*timeSpan && timeSpan < 2*minUnit_)
                morse += ".";
            else
                morse += "-";
        }
    }
    return morse;
}
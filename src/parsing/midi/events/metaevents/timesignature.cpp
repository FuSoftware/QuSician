#include "timesignature.h"

TimeSignature::TimeSignature(int delta, int nn, int dd, int cc, int bb) : MidiEvent(delta)
{
    this->numerator = nn;
    this->denominator = dd;
    this->clock = cc;
    this->thirtySeconds = bb;
    this->type = MidiEventType::TIME_SIGNATURE;
    this->isMeta = true;
}

std::string TimeSignature::toString()
{
    std::stringstream oss;
    int d = 1;
    for(int i=0;i<this->denominator;i++)
        d*=2;

    oss << "Timing    : " << this->numerator << "/" << d << std::endl;
    oss << "Clock     : " << this->clock << std::endl;
    oss << "32nd Note : " << this->thirtySeconds << std::endl;
    return oss.str();
}

int TimeSignature::getNumerator() const
{
    return this->numerator;
}

int TimeSignature::getDenominator() const
{
    return (1 << this->denominator);
}

int TimeSignature::getClock() const
{
    return this->clock;
}

int TimeSignature::getThirtySeconds() const
{
    return this->thirtySeconds;
}

std::vector<unsigned char> TimeSignature::getData()
{

}


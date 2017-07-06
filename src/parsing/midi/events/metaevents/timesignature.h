#ifndef TIMESIGNATURE_H
#define TIMESIGNATURE_H

#include "../midievent.h"
#include <string>
#include <sstream>

class TimeSignature : public MidiEvent
{
public:
    TimeSignature(int delta, int nn, int dd, int cc, int bb);
    int getNumerator();
    int getDenominator();
    int getClock();
    int getThirtySeconds();
    std::string toString();
    std::vector<unsigned char> getData();

private:
    int numerator;
    int denominator;
    int clock;
    int thirtySeconds;
};

#endif // TIMESIGNATURE_H

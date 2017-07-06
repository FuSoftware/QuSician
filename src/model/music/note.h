#ifndef NOTE_H
#define NOTE_H

#include <vector>

using namespace std;

enum KeyLabel
{
    C = 0,
    C_SHARP,
    D,
    D_SHARP,
    E,
    F,
    F_SHARP,
    G,
    G_SHARP,
    A,
    A_SHARP,
    B,
    COUNT
};

class Note
{
public:
    Note();
    Note(int start, int key, int velocity);
    void setNoteOn(int t, int k, int v);
    void setNoteOff(int t, int v);
    void setTickTime(int us);

    int getKey();
    int getStartTicks();
    int getStopTicks();
    int getStart();
    int getStop();

    KeyLabel getLabel();
    int getOctave();

    int getStartVelocity();
    int getStopVelocity();

    static bool isSharp(int key);
    static bool isSharp(Note* n);
    static Note* getLastOpenKey(vector<Note*> *notes, int key);

private:
    int start;
    int stop;

    int startTime;
    int stopTime;

    int startVelocity;
    int stopVelocity;

    int key;
    KeyLabel label;
    int octave;
    int channel;

};

#endif // NOTE_H

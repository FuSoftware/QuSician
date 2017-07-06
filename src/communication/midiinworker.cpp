#include "midiinworker.h"

MidiInWorker::MidiInWorker(int port, QObject *parent) : QObject(parent)
{
    midiin = new RtMidiIn();
    this->port = port;
}

MidiInWorker::~MidiInWorker()
{
    delete midiin;
}

void MidiInWorker::process()
{
    midiin->openPort(this->port);

    // Don't ignore sysex, timing, or active sensing messages.
    midiin->ignoreTypes( false, false, false );

    vector<unsigned char> message;
    double stamp;
    run = true;
    while(run)
    {
        stamp = midiin->getMessage(&message);
        if(message.size() > 0)
            eventReceived(stamp, &message,0);

        QThread::usleep(5);
    }

    emit finished();
}


void MidiInWorker::eventReceived( double deltatime, vector< unsigned char > *message, void *userData )
{
    /*
    for ( unsigned int i=0; i<message->size(); i++ )
        cout << "Byte " << i << " = " << (int)message->at(i) << ", ";

    cout << "stamp = " << deltatime << endl;
    */

    if((*message)[0] == 0x90 || (*message)[0] == 0x80)
    {
        MidiNote n;
        n.key = (*message)[1];
        n.velocity = (*message)[2];
        n.stamp = deltatime;

        if((*message)[0] == 0x90)
        {
            n.state = true; //Note On
            emit noteOn(n);
        }
        else if((*message)[0] == 0x80)
        {
            n.state = false; //Off
            emit noteOff(n);
        }

        emit noteEvent(n);
    }


}

void MidiInWorker::stop()
{
    run = false;
}

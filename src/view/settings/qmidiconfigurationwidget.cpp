#include "qmidiconfigurationwidget.h"

QMidiConfigurationWidget::QMidiConfigurationWidget(QWidget *parent) : QWidget(parent)
{
    initialize();
}

void QMidiConfigurationWidget::initialize()
{
    this->keyboard = new QKeyboardWidget(this);
    this->midiPorts = new QMidiPortSelection(this);
    this->midiOutput = new MidiOutput(this);
    this->midiPlayer = 0;

    this->pbStartTest = new QPushButton("Test",this);


    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(this->midiPorts);
    l->addWidget(this->pbStartTest);
    l->addWidget(this->keyboard);

    setLayout(l);

    connect(this->pbStartTest,SIGNAL(clicked(bool)),this,SLOT(testAudio()));
    connect(this->midiPorts,SIGNAL(inputSelected(int)),this->keyboard,SLOT(setPort(int)));
    connect(this->midiPorts,SIGNAL(outputSelected(int)),this,SLOT(outputSelected(int)));

    this->midiPorts->refresh();
}

void QMidiConfigurationWidget::outputSelected(int port)
{
    this->midiOutput->start(port);
}

void QMidiConfigurationWidget::testAudio()
{
    if(this->midiPlayer != 0)
    {
        this->midiPlayer->stop();
    }

    //Partition
    string file = "D:\\Prog\\MidiMusicXML\\A Changeling Can Change - WeimTeam.mid";
    MidiFile *f = new MidiFile(file);
    this->partition = new Partition(f->getTracks()[1]);
    this->partition->setTickTime(f->getTickTimeUs());

    this->midiPlayer = new MidiPlayer(this->partition,this->midiOutput);

    //TEST : MidiEvents
    MidiTrack *track = f->getTracks()[1];
    this->midiPlayer->setEvents(QVector<MidiEvent*>::fromStdVector(track->getEvents()));

    QThread *t = new QThread();

    connect(t, SIGNAL(started()),  this->midiPlayer, SLOT(process()));
    connect(this->midiPlayer, SIGNAL(finished()), t, SLOT(quit()));
    connect(this->midiPlayer, SIGNAL(finished()), this->midiPlayer, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    this->midiPlayer->moveToThread(t);
    t->start();
}

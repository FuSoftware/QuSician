#include "qmidiportselection.h"

QMidiPortSelection::QMidiPortSelection(QWidget *parent) : QWidget(parent)
{
    loadUI();
}

void QMidiPortSelection::loadUI()
{
    lInputs = new QMidiPortList("Inputs",this);
    lOutputs = new QMidiPortList("Outputs",this);
    QPushButton *pbRefresh = new QPushButton("Refresh",this);

    QVBoxLayout *layoutMain = new QVBoxLayout;
    QHBoxLayout *layoutLists = new QHBoxLayout;

    layoutLists->addWidget(lInputs);
    layoutLists->addWidget(lOutputs);

    layoutMain->addWidget(pbRefresh);
    layoutMain->addLayout(layoutLists);

    setLayout(layoutMain);

    connect(pbRefresh,SIGNAL(clicked()),this,SLOT(refresh()));
    connect(lInputs,SIGNAL(selected(int)),this,SIGNAL(inputSelected(int)));
    connect(lOutputs,SIGNAL(selected(int)),this,SIGNAL(outputSelected(int)));
}

void QMidiPortSelection::refresh()
{
    vector<MidiPort> inputs = RtMidiUtils::getInputPorts();
    vector<MidiPort> outputs = RtMidiUtils::getOutputPorts();

    lInputs->set(QVector<MidiPort>::fromStdVector(inputs));
    lOutputs->set(QVector<MidiPort>::fromStdVector(outputs));
}

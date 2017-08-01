#include "tests.h"

void TestMidiFile(string file)
{
    MidiFile *f = new MidiFile(file);

    cout << f->toString() << endl;
}

void TestRtMidi()
{
    RtMidiIn *midiin = 0;
    RtMidiOut *midiout = 0;

    try
    {
        midiin = new RtMidiIn();
    }
    catch (RtMidiError &error) {
        // Handle the exception here
        error.printMessage();
    }
    // Check inputs.
    unsigned int nPorts = midiin->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
    std::string portName;
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiin->getPortName(i);
        }
        catch ( RtMidiError &error ) {
            error.printMessage();
            goto cleanup;
        }
        std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
    }

    // RtMidiOut constructor
    try {
        midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    // Check outputs.
    nPorts = midiout->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiout->getPortName(i);
        }
        catch (RtMidiError &error) {
            error.printMessage();
            goto cleanup;
        }
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    std::cout << '\n';



    // Clean up
    cleanup:
        delete midiin;
        delete midiout;

}

void TestMidiOutput()
{
    RtMidiOut *midiout = 0;

    // RtMidiOut constructor
    try {
        midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    // Check outputs.
    int nPorts = midiout->getPortCount();
    int port;
    vector<unsigned char> message;
    string portName;

    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiout->getPortName(i);
        }
        catch (RtMidiError &error) {
            error.printMessage();
            goto cleanupTestMidiOutput;
        }
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    std::cout << '\n';

    cout << endl << "Select a port : ";
    cin >> port;
    midiout->openPort(port);

    message.push_back(0x90);
    message.push_back(60);
    message.push_back(100);
    midiout->sendMessage(&message);
    cout << "Started C" << endl;
    QThread::msleep(500);

    message[0] = 0x90;
    message[1] = 62;
    message[2] = 100;
    midiout->sendMessage(&message);
    cout << "Started D" << endl;
    QThread::msleep(500);

    message[0] = 0x80;
    message[1] = 60;
    message[2] = 100;
    midiout->sendMessage(&message);
    cout << "Stopped C" << endl;
    QThread::msleep(500);

    message[0] = 0x80;
    message[1] = 62;
    message[2] = 100;
    midiout->sendMessage(&message);
    cout << "Stopped D" << endl;
    QThread::msleep(500);

    cleanupTestMidiOutput:
        delete midiout;
}

void TestPortSelection()
{
    QMidiPortSelection *w = new QMidiPortSelection();
    w->show();
}

void MidiWorkerTest()
{
    int port;
    vector<MidiPort> ports = RtMidiUtils::getInputPorts();

    cout << "Available input ports : " << endl;
    for(int i=0;i<ports.size();i++)
    {
        cout << "    " << ports[i].name << endl;
    }

    cout << endl << "Port to use : ";
    cin >> port;

    MidiInWorker *w = new MidiInWorker(port);
    QThread *t = new QThread();

    QObject::connect(t, SIGNAL(started()),  w, SLOT(process()));
    QObject::connect(w, SIGNAL(finished()), t, SLOT(quit()));
    QObject::connect(w, SIGNAL(finished()), w, SLOT(deleteLater()));
    QObject::connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    w->moveToThread(t);
    t->start();

    char input;
    cin.get(input);
}

void PartitionTestMidi()
{
    string file = "D:\\Prog\\MidiMusicXML\\MIDI_sample_synthesia.mid";

    MidiFile *f = new MidiFile(file);

    int track;

    vector<MidiTrack*> tracks = f->getTracks();

    for(int i=0;i<tracks.size();i++)
    {
        cout <<  i << " : " << tracks[i]->getEventCount() << " events" << endl;
    }

    cout << endl << "Choose a track to parse : ";
    cin >> track;

    MidiTrack *trk = tracks[track];

    Partition *p = new Partition(trk);
    vector<Note*> *notes = p->getNotes();

    cout << "Found " << notes->size() << " notes" << endl;

    int err = 0;
    for(int i=0;i<notes->size();i++)
    {
        if((*notes)[i]->getStop() == -1)
        {
            err++;
        }
    }

    cout << err << " notes do not end" << endl;
}

void KeyboardConfTest()
{
    QMidiConfigurationWidget *w = new QMidiConfigurationWidget(0);
    w->show();
}

void MidiInOutTest()
{
    //Port Selection
    int portIn;
    int portOut;

    RtMidiIn *midiin = 0;
    RtMidiOut *midiout = 0;

    try
    {
        midiin = new RtMidiIn();
    }
    catch (RtMidiError &error) {
        // Handle the exception here
        error.printMessage();
    }
    // Check inputs.
    unsigned int nPorts = midiin->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
    std::string portName;
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiin->getPortName(i);
        }
        catch ( RtMidiError &error ) {
            error.printMessage();
            goto cleanup;
        }
        std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
    }

    // RtMidiOut constructor
    try {
        midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }

    // Check outputs.
    nPorts = midiout->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiout->getPortName(i);
        }
        catch (RtMidiError &error) {
            error.printMessage();
            goto cleanup;
        }
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    std::cout << '\n';



    // Clean up
    cleanup:
        delete midiin;
        delete midiout;

    std::cout << "Input : ";
    std::cin >> portIn ;

    std::cout << "Output : ";
    std::cin >> portOut ;

    QWidget *w = new QWidget();

    MidiOutput *out = new MidiOutput(portOut,w);
    MidiKeyboard *keyboard = new MidiKeyboard(portIn,w);

    QObject::connect(keyboard,SIGNAL(NoteReleased(MidiNote)),out,SLOT(noteOff(MidiNote)));
    QObject::connect(keyboard,SIGNAL(NotePressed(MidiNote)),out,SLOT(noteOn(MidiNote)));

    out->start();
    keyboard->start();
}

void PartitionToCSV(std::string file, std::string csv, std::string delimiter)
{
    MidiFile *f = new MidiFile(file);
    vector<MidiTrack*> tracks = f->getTracks();
    int track=0;

    for(int i=0;i<tracks.size();i++)
    {
        cout <<  i << " : " << tracks[i]->getEventCount() << " events" << endl;
    }

    cout << endl << "Choose a track to parse : ";
    cin >> track;

    MidiTrack *trk = tracks[track];
    Partition *p = new Partition(trk);
    p->setTickTime(f->getTickTimeUs());
    p->toCSV(csv,delimiter);

    cout << endl << "CSV file created";
}

void TestVSV()
{
    //81 00
    VLV v;
    v.addData(0x81);
    v.addData(0x00);
    std::cout << "81 00 -> " << v.toInt() << " (128 / 0x80)" << std::endl;

    //7F
    v.clear();
    v.addData(0x7F);
    std::cout << "7F -> " << v.toInt() << " (127 / 0x7F)" << std::endl;

    //81 7F
    v.clear();
    v.addData(0x81);
    v.addData(0x7F);
    std::cout << "81 7F -> " << v.toInt() << " (255 / 0xFF)" << std::endl;

    //82 80 00
    v.clear();
    v.addData(0x82);
    v.addData(0x80);
    v.addData(0x00);
    std::cout << "82 80 00 -> " << v.toInt() << " (32768 / 0x8000)" << std::endl;
}

void TestMidiPlayer(std::string file)
{
    std::cout << "Select a MIDI File" << std::endl;

    if(file.empty())
        file = QFileDialog::getOpenFileName(0,QString("Open MIDI File"), QString(), QString("MIDI Files (*.mid)")).toStdString();

    //Track
    MidiFile *f = new MidiFile(file);
    std::cout << std::endl << f->getTracksInfo() << std::endl;
    std::cout << "Track : ";

    //Input a line of numbers
    std::string s;
    std::getline( std::cin, s );
    std::istringstream is( s );
    std::vector<int> trk( ( std::istream_iterator<int>( is ) ), std::istream_iterator<int>() );

    //Port
    int port;
    // RtMidiOut constructor
    std::cout << std::endl << "Output ports :" << std::endl;
    std::cout << RtMidiUtils::listOutputs() << std::endl;

    std::cout << "Output Port : ";
    std::cin >> port;

    MidiOutput *midiOutput = new MidiOutput(port);
    MidiPlayer *midiPlayer = new MidiPlayer(midiOutput);

    for(int i=0;i<trk.size();i++)
    {
        MidiTrack *track = f->getTracks()[trk[i]];
        midiPlayer->addEventList(QVector<MidiEvent*>::fromStdVector(track->getEvents()));
    }

    QThread *t = new QThread();
    QObject::connect(t, SIGNAL(started()),  midiPlayer, SLOT(start()));
    QObject::connect(midiPlayer, SIGNAL(finished()), t, SLOT(quit()));
    QObject::connect(midiPlayer, SIGNAL(finished()), midiPlayer, SLOT(deleteLater()));
    QObject::connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
    midiPlayer->moveToThread(t);
    t->start();
}

void TestMusicList(QStringList folders, int port)
{
    QMusicListWidget *w = new QMusicListWidget(0);
    FolderScanner *f = new FolderScanner(folders);

    QThread *t = new QThread();
    QObject::connect(t, SIGNAL(started()),  f, SLOT(process()));
    QObject::connect(f, SIGNAL(finished()), t, SLOT(quit()));
    QObject::connect(f, SIGNAL(finished()), f, SLOT(deleteLater()));
    QObject::connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
    f->moveToThread(t);

    QObject::connect(f,SIGNAL(fileLoaded(QMusicFile*)),w,SLOT(addFile(QMusicFile*)));
    t->start();

    MidiPlayer *player = new MidiPlayer();
    MidiOutput *out = new MidiOutput(port,player);
    player->setOutput(out);
    player->init();

    QObject::connect(w,SIGNAL(playMidi(MidiFile*)),player,SLOT(play(MidiFile*)));

    w->show();
}

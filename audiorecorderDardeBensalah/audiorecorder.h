#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QMainWindow>
#include <QMediaRecorder>
#include <QUrl>
#include <xyseriesiodevice.h>
#include <widget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class AudioRecorder; }
class QAudioRecorder;
class QAudioProbe;
class QAudioBuffer;
QT_END_NAMESPACE

class AudioLevel;

class AudioRecorder : public QMainWindow
{
    Q_OBJECT

public:
    AudioRecorder();


public slots:
    void processBuffer(const QAudioBuffer&);
    void creerFenetreFormPatient();
    void testAudio();


private slots:
    void setOutputLocation();
    void togglePause();
    void toggleRecord();


    void updateStatus(QMediaRecorder::Status);
    void onStateChanged(QMediaRecorder::State);
    void updateProgress(qint64 pos);
    void displayErrorMessage();

private:
    void clearAudioLevels();


    Ui::AudioRecorder *ui = nullptr;

    QAudioRecorder *m_audioRecorder = nullptr;
    QAudioProbe *m_probe = nullptr;
    QList<AudioLevel*> m_audioLevels;
    bool m_outputLocationSet = false;
    QAction *actionFormPatient = nullptr;
    Widget *graphe;


};

#endif // AUDIORECORDER_H

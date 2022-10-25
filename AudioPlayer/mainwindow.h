#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioDeviceInfo>
#include <QFile>
#include <QTimer>

class QPushButton;
class CircleButton;
class HorizontalButton;
class VerticalButton;
class QComboBox;
class QSlider;
class QLabel;
class QAudioOutput;
class QAudioInput;
class QRadioButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initWidget();

    void initSettings();

    void initAudio(const QAudioDeviceInfo &deviceInfo, QAudioFormat format);

    void initFile();

    void initConnect();

    void setFormatEnable(bool enable);

private slots:
    void onChangedOutputMode();

    void onChangedInputMode();

    void onStartClicked();

    void onStopClicked();

    void onSuspendClicked();

    void onResetClicked();

    void onResumeClicked();

    void onVolumeChanged(int volume);

private:
    CircleButton                *m_startBtn;
    HorizontalButton            *m_suspendBtn;
    HorizontalButton            *m_resumeBtn;
    VerticalButton              *m_stopBtn;
    VerticalButton              *m_resetBtn;

    QPushButton                 *m_pullModebtn;
    bool                         m_pullMode;

    QRadioButton                *m_outputRadio;
    QRadioButton                *m_inputRadio;
    QAudio::Mode                 m_mode;

    QComboBox                   *m_deviceBox;
    QLabel                      *m_deviceLabel;

    QComboBox                   *m_rateBox;
    QLabel                      *m_rateLabel;

    QComboBox                   *m_sizeBox;
    QLabel                      *m_sizeLabel;

    QComboBox                   *m_channelBox;
    QLabel                      *m_channelLabel;

    QSlider                     *m_volumeSlider;
    QLabel                      *m_volumeLabel;

    QAudioOutput                *m_audioOutput;
    QFile                        m_outputFile;

    QAudioInput                 *m_audioInput;
    QFile                        m_inputFile;

    bool                         m_isStop;
};
#endif // MAINWINDOW_H

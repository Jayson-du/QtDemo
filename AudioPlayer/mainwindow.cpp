#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QRadioButton>
#include <QAudioOutput>
#include <QAudioInput>
#include <QDebug>


#include "circlebutton.h"
#include "horizontalbutton.h"
#include "verticalbutton.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_startBtn(nullptr),
      m_suspendBtn(nullptr),
      m_resumeBtn(nullptr),
      m_stopBtn(nullptr),
      m_pullModebtn(nullptr),
      m_pullMode(true),
      m_resetBtn(nullptr),
      m_outputRadio(nullptr),
      m_inputRadio(nullptr),
      m_deviceBox(nullptr),
      m_deviceLabel(nullptr),
      m_rateBox(nullptr),
      m_rateLabel(nullptr),
      m_sizeBox(nullptr),
      m_sizeLabel(nullptr),
      m_channelBox(nullptr),
      m_channelLabel(nullptr),
      m_volumeSlider(nullptr),
      m_volumeLabel(nullptr),
      m_audioOutput(nullptr),
      m_audioInput(nullptr),
      m_isStop(true)
{
    initWidget();
    initSettings();
    initFile();
    initConnect();
}

MainWindow::~MainWindow()
{
    if (m_outputFile.isOpen()) {
        m_outputFile.close();
    }

    if (m_inputFile.isOpen()) {
        m_inputFile.close();
    }

}

void MainWindow::initWidget()
{
    QWidget* widget = new QWidget;

    QVBoxLayout *wholeVBLayout = new QVBoxLayout;
    QHBoxLayout *wholeHBLayout = new QHBoxLayout;
    {
        m_suspendBtn = new HorizontalButton(QString("suspend"));
        m_stopBtn = new VerticalButton(QString("stop"), true);
        m_startBtn = new CircleButton(QString("start"));
        m_resetBtn = new VerticalButton(QString("reset"));
        m_resumeBtn = new HorizontalButton(QString("resume"), true);

        QGridLayout* gridLayout = new QGridLayout;

        gridLayout->addWidget(m_suspendBtn, 0, 1, Qt::AlignHCenter);
        gridLayout->addWidget(m_stopBtn, 1, 0, Qt::AlignHCenter);
        gridLayout->addWidget(m_startBtn, 1, 1, Qt::AlignHCenter);
        gridLayout->addWidget(m_resetBtn, 1, 2, Qt::AlignHCenter);
        gridLayout->addWidget(m_resumeBtn, 2, 1, Qt::AlignHCenter);

        wholeHBLayout->addLayout(gridLayout);
    }

    {
        QHBoxLayout *modeLayout = new QHBoxLayout;
        m_outputRadio = new QRadioButton(tr("AudioOutput"));
        m_inputRadio  = new QRadioButton(tr("AudioInput"));
        modeLayout->addWidget(m_outputRadio);
        modeLayout->addWidget(m_inputRadio);

        QHBoxLayout *deviceLayout = new QHBoxLayout;
        m_deviceBox      = new QComboBox;
        m_deviceLabel    = new QLabel(tr("device:"));
        deviceLayout->addWidget(m_deviceLabel);
        deviceLayout->addWidget(m_deviceBox);

        QHBoxLayout *rateLayout = new QHBoxLayout;
        m_rateBox      = new QComboBox;
        m_rateLabel    = new QLabel(tr("sample rate:"));
        rateLayout->addWidget(m_rateLabel);
        rateLayout->addWidget(m_rateBox);

        QHBoxLayout *sizeLayout = new QHBoxLayout;
        m_sizeBox      = new QComboBox;
        m_sizeLabel    = new QLabel(tr("sample size:"));
        sizeLayout->addWidget(m_sizeLabel);
        sizeLayout->addWidget(m_sizeBox);

        QHBoxLayout *channelLayout = new QHBoxLayout;
        m_channelBox   = new QComboBox;
        m_channelLabel = new QLabel(tr("sample channel:"));
        channelLayout->addWidget(m_channelLabel);
        channelLayout->addWidget(m_channelBox);

        QVBoxLayout *settingLayout = new QVBoxLayout;
        settingLayout->addLayout(modeLayout);
        settingLayout->addLayout(deviceLayout);
        settingLayout->addLayout(rateLayout);
        settingLayout->addLayout(sizeLayout);
        settingLayout->addLayout(channelLayout);

        wholeHBLayout->addLayout(settingLayout);
    }

    wholeVBLayout->addLayout(wholeHBLayout);

    {
        QHBoxLayout *volumeBox = new QHBoxLayout;

        m_volumeSlider = new QSlider(Qt::Horizontal);
        m_volumeSlider->setMinimum(0);
        m_volumeSlider->setMaximum(100);
        m_volumeSlider->setSingleStep(10);
        m_volumeSlider->setValue(50);

        m_volumeLabel = new QLabel;
        m_volumeLabel->setText(tr("Volume:"));

        volumeBox->addWidget(m_volumeLabel);
        volumeBox->addWidget(m_volumeSlider);

        wholeVBLayout->addLayout(volumeBox);
    }
    widget->setLayout(wholeVBLayout);

    setCentralWidget(widget);
}

void MainWindow::initSettings()
{
    auto showFormat = [&](QAudioDeviceInfo defaultDeviceInfo) {
        QList<QAudioDeviceInfo> deviceInfos = QAudioDeviceInfo::availableDevices(m_mode);
        QList<int> Rates = defaultDeviceInfo.supportedSampleRates();
        QList<int> Sizes = defaultDeviceInfo.supportedSampleSizes();
        QList<int> channels = defaultDeviceInfo.supportedChannelCounts();

        int index = 0;

        for (int i = 0; i < deviceInfos.size(); i++) {
            QString deviceName = deviceInfos[i].deviceName();
            if (m_mode == QAudio::AudioOutput &&
                deviceName == QAudioDeviceInfo::defaultOutputDevice().deviceName()) {
                index = i;
            } else if (m_mode == QAudio::AudioInput &&
                       deviceName == QAudioDeviceInfo::defaultInputDevice().deviceName()){
                index = i;
            }
            m_deviceBox->addItem(deviceName);
        }
        m_deviceBox->setCurrentIndex(index);

        index = 0;
        for (int i = 0; i < Rates.size(); i++) {
            if (Rates[i] == defaultDeviceInfo.preferredFormat().sampleRate()) {
                index = i;
            }
            m_rateBox->addItem(QString::number(Rates[i]));
        }
        m_rateBox->setCurrentIndex(index);

        index = 0;
        for (int i = 0; i < Sizes.size(); i++) {
            if (Sizes[i] == defaultDeviceInfo.preferredFormat().sampleSize()) {
                index = i;
            }
            m_sizeBox->addItem(QString::number(Sizes[i]));
        }
        m_sizeBox->setCurrentIndex(index);

        index = 0;
        for (int i = 0; i < channels.size(); i++) {
            if (channels[i] == defaultDeviceInfo.preferredFormat().channelCount()) {
                index = i;
            }
            m_channelBox->addItem(QString::number(channels[i]));
        }
        m_channelBox->setCurrentIndex(index);
    };

    m_outputRadio->setChecked(true);
    m_mode = QAudio::AudioOutput;

    if (m_mode == QAudio::AudioOutput) {

        QAudioDeviceInfo defaultDeviceInfo = QAudioDeviceInfo::defaultOutputDevice();

        showFormat(defaultDeviceInfo);

        initAudio(defaultDeviceInfo, defaultDeviceInfo.preferredFormat());

    } else {

        QAudioDeviceInfo defaultDeviceInfo = QAudioDeviceInfo::defaultInputDevice();

        showFormat(defaultDeviceInfo);

        initAudio(defaultDeviceInfo, defaultDeviceInfo.preferredFormat());
    }
}

void MainWindow::initAudio(const QAudioDeviceInfo &deviceInfo, QAudioFormat format)
{
    m_audioOutput = new QAudioOutput(deviceInfo, format, this);
    m_audioInput  = new QAudioInput(deviceInfo, format, this);
}

void MainWindow::initFile()
{
    if (m_mode == QAudio::AudioOutput) {

        if (!m_outputFile.isOpen()) {
            m_outputFile.setFileName("/apps/OssAudioPlay/audio.wav");
            m_outputFile.open(QIODevice::ReadOnly);
        }

    } else {

        if (!m_inputFile.isOpen()) {
            m_inputFile.setFileName("/apps/OssAudioPlay/test.wav");
            m_inputFile.open(QIODevice::ReadWrite);
            printf("inputfile open!\n");
        }
    }
}

void MainWindow::initConnect()
{
    connect(m_startBtn, &CircleButton::clicked, this, &MainWindow::onStartClicked);
    connect(m_suspendBtn, &CircleButton::clicked, this, &MainWindow::onSuspendClicked);
    connect(m_resumeBtn, &CircleButton::clicked, this, &MainWindow::onResumeClicked);
    connect(m_stopBtn, &CircleButton::clicked, this, &MainWindow::onStopClicked);
    connect(m_resetBtn, &CircleButton::clicked, this, &MainWindow::onResetClicked);
    connect(m_volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);
    connect(m_outputRadio, &QRadioButton::toggled, this, &MainWindow::onChangedOutputMode);
    connect(m_inputRadio, &QRadioButton::toggled, this, &MainWindow::onChangedInputMode);
}

void MainWindow::setFormatEnable(bool enable)
{
    m_outputRadio->setEnabled(enable);;
    m_inputRadio->setEnabled(enable);
    m_deviceBox->setEnabled(enable);
    m_rateBox->setEnabled(enable);
    m_sizeBox->setEnabled(enable);
    m_channelBox->setEnabled(enable);
}

void MainWindow::onChangedOutputMode()
{
    m_mode = QAudio::AudioOutput;
    initFile();
}

void MainWindow::onChangedInputMode()
{
    m_mode = QAudio::AudioInput;
    initFile();
}

void MainWindow::onStartClicked()
{
    if (m_mode == QAudio::AudioOutput) {
        m_audioOutput->start(&m_outputFile);
    } else {
        m_audioInput->start(&m_inputFile);
    }

    setFormatEnable(false);
}

void MainWindow::onStopClicked()
{
    if (m_mode == QAudio::AudioOutput) {
        m_audioOutput->stop();
    } else {
        m_audioInput->stop();
    }

    setFormatEnable(true);
}

void MainWindow::onSuspendClicked()
{
    if (m_mode == QAudio::AudioOutput) {
        m_audioOutput->suspend();
    } else {
        m_audioInput->suspend();
    }
}

void MainWindow::onResetClicked()
{
    if (m_mode == QAudio::AudioOutput) {
        m_audioOutput->reset();
    } else {
        m_audioInput->reset();
    }
}

void MainWindow::onResumeClicked()
{
    if (m_mode == QAudio::AudioOutput) {
        m_audioOutput->resume();
    } else {
        m_audioInput->resume();
    }
}

void MainWindow::onVolumeChanged(int volume)
{
    if(m_mode == QAudio::AudioOutput) {
        m_audioOutput->setVolume(volume);
    } else {
        m_audioInput->setVolume(volume);
    }
}


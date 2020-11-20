#include "QtSimPanel.h"
#include "udpclient.h"
#include <KeyReceiver.h>
#include <QQmlContext>
#include <QDebug>
#include <QDir>
#include <QTimer>

QtSimPanel::QtSimPanel(int argc, char** argv): QGuiApplication(argc, argv),
   m_settings(QDir::currentPath()+"/settings.ini", QSettings::IniFormat)
{
    m_dataStore = new DataStore();
}

QtSimPanel::~QtSimPanel()
{
    delete m_dataStore;
    exit();
}

void QtSimPanel::startApp()
{
    // Load existing settings
    loadSettings();

    m_QmlEngine.rootContext()->setContextProperty("qSimPanel", this);
    m_QmlEngine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    // Enable Key strike handleing
    KeyReceiver* keyReceiver = new KeyReceiver(this);
    installEventFilter(keyReceiver);

    // Load UDPClient with datastore
    UdpClient udpClient(m_dataStore);

    QTimer *ticker = new QTimer(this);
    connect(ticker, SIGNAL(timeout()), this, SLOT(refreshPanelValues()));
    ticker->start(300);

    exec();
}

void QtSimPanel::setPanelPositionX(int x)
{
    m_i_panelPositionX = x;
    emit panelPositionChanged();
}

int QtSimPanel::getPanelPositionX()
{
    return m_i_panelPositionX;
}

void QtSimPanel::setPanelPositionY(int y)
{
    m_i_panelPositionY = y;
    emit panelPositionChanged();
}

int QtSimPanel::getPanelPositionY()
{
    return m_i_panelPositionY;
}

void QtSimPanel::toggleInstructionVisibility()
{
    m_b_areInstructionsVisibile = !m_b_areInstructionsVisibile;
    emit instructionVisibilityChanged();
}

void QtSimPanel::setPanelScale(float scale) {
   m_d_panelScale = scale;
   emit panelScaleChanged();
}

float QtSimPanel::getPanelScale() {
    return m_d_panelScale;
}

void QtSimPanel::loadSettings()
{
    if (QFile::exists(m_settings.fileName())) {
        m_i_panelPositionX = m_settings.value("panel/x").toInt();
        m_i_panelPositionY = m_settings.value("panel/y").toInt();
        m_d_panelScale = m_settings.value("panel/scale").toDouble();
        m_b_areInstructionsVisibile = m_settings.value("panel/instructions").toBool();
    }
}

void QtSimPanel::saveSettings()
{
    m_settings.setValue("panel/x", m_i_panelPositionX);
    m_settings.setValue("panel/y", m_i_panelPositionY);
    m_settings.setValue("panel/scale", m_d_panelScale);
    m_settings.setValue("panel/instructions", m_b_areInstructionsVisibile);
}


void QtSimPanel::refreshPanelValues()
{
    m_flightData.clear();
    m_flightData.insert("vacuum_heading", m_dataStore->readData("vacuum_heading"));
    m_flightData.insert("pitch", m_dataStore->readData("pitch"));
    m_flightData.insert("roll", m_dataStore->readData("roll"));
    m_flightData.insert("altitude_ind", m_dataStore->readData("altitude_ind"));
    m_flightData.insert("sideslip", m_dataStore->readData("sideslip"));
    m_flightData.insert("kt_ias", m_dataStore->readData("kt_ias"));
    m_flightData.insert("vertical_speed", m_dataStore->readData("vertical_speed"));
    m_flightData.insert("inhg_baro_pressure", m_dataStore->readData("inhg_baro_pressure"));

    emit flightDataChanged();
}

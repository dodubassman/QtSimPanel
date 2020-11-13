#include "QtSimPanel.h"
#include <KeyReceiver.h>
#include <QQmlContext>
#include <QDebug>
#include <QDir>

QtSimPanel::QtSimPanel(int argc, char** argv): QGuiApplication(argc, argv),
   m_settings(QDir::currentPath()+"/settings.ini", QSettings::IniFormat)
{
}

QtSimPanel::~QtSimPanel()
{
    exit();
}

void QtSimPanel::startApp()
{
    loadSettings();

    m_QmlEngine.rootContext()->setContextProperty("qSimPanel", this);
    m_QmlEngine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    // Enable Key strike handleing
    KeyReceiver* keyReceiver = new KeyReceiver(this);

    installEventFilter(keyReceiver);

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

void QtSimPanel::loadSettings(){
    if (QFile::exists(m_settings.fileName())) {
        m_i_panelPositionX = m_settings.value("panel/x").toInt();
        m_i_panelPositionY = m_settings.value("panel/y").toInt();
        m_d_panelScale = m_settings.value("panel/scale").toDouble();
        m_b_areInstructionsVisibile = m_settings.value("panel/instructions").toBool();
    }
}

void QtSimPanel::saveSettings(){
    m_settings.setValue("panel/x", m_i_panelPositionX);
    m_settings.setValue("panel/y", m_i_panelPositionY);
    m_settings.setValue("panel/scale", m_d_panelScale);
    m_settings.setValue("panel/instructions", m_b_areInstructionsVisibile);
}

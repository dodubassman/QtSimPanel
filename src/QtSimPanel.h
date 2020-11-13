#ifndef QTSIMPANEL_H
#define QTSIMPANEL_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QSettings>

class QtSimPanel : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(bool areInstructionsVisible MEMBER m_b_areInstructionsVisibile NOTIFY instructionVisibilityChanged())
    Q_PROPERTY(int panelPositionX MEMBER m_i_panelPositionX NOTIFY panelPositionChanged())
    Q_PROPERTY(int panelPositionY MEMBER m_i_panelPositionY NOTIFY panelPositionChanged())
    Q_PROPERTY(float panelScale MEMBER m_d_panelScale NOTIFY panelScaleChanged())

public:
    QtSimPanel(int argc, char** argv);
    virtual ~QtSimPanel();

    void startApp();
    void stopApp();

    void setPanelPositionX(int x);
    int getPanelPositionX();
    void setPanelPositionY(int y);
    int getPanelPositionY();
    void toggleInstructionVisibility();
    void setPanelScale(float scale);
    float getPanelScale();

    void loadSettings();
    void saveSettings();

signals:
    void instructionVisibilityChanged();
    void panelPositionChanged();
    void panelScaleChanged();

public slots:

private:
    QQmlApplicationEngine m_QmlEngine;
    QSettings m_settings;
    int m_i_panelPositionX = 100;
    int m_i_panelPositionY = 100;
    double m_d_panelScale = 1;
    bool m_b_areInstructionsVisibile = true;
};

#endif // QTSIMPANEL_H

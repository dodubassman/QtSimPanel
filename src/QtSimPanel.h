#ifndef QTSIMPANEL_H
#define QTSIMPANEL_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QSettings>
#include "datastore.h"

class QtSimPanel : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(bool areInstructionsVisible MEMBER m_b_areInstructionsVisibile NOTIFY instructionVisibilityChanged())
    Q_PROPERTY(int panelPositionX MEMBER m_i_panelPositionX NOTIFY panelPositionChanged())
    Q_PROPERTY(int panelPositionY MEMBER m_i_panelPositionY NOTIFY panelPositionChanged())
    Q_PROPERTY(float panelScale MEMBER m_d_panelScale NOTIFY panelScaleChanged())
    Q_PROPERTY(QString activeQmlPanel MEMBER m_s_activeQmlPanel NOTIFY panelLoaded())
    Q_PROPERTY(QVariantMap flightData MEMBER m_flightData NOTIFY flightDataChanged)

public:
    explicit QtSimPanel(int argc, char** argv);
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
    void flightDataChanged();
    void panelLoaded();

public slots:
    void refreshPanelValues();

private:
    QQmlApplicationEngine m_QmlEngine;
    QSettings m_settings;
    DataStore* m_dataStore;
    int m_i_panelPositionX = 100;
    int m_i_panelPositionY = 100;
    double m_d_panelScale = 1;
    bool m_b_areInstructionsVisibile = true;
    QVariantMap m_flightData;
    QString m_s_activeQmlPanel = "dr400";
};

#endif // QTSIMPANEL_H

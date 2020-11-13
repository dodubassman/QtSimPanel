#include "KeyReceiver.h"
#include <QtSimPanel.h>
#include <QKeyEvent>
#include <QGuiApplication>

KeyReceiver::KeyReceiver(QtSimPanel* qtSimPanel)
{
    m_qtSimPanel = qtSimPanel;
}


bool KeyReceiver::eventFilter(QObject* obj, QEvent* event) {
    if(event->type()==QEvent::KeyPress) {
        // Convert event to QKeyEvent
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key()==Qt::Key_Escape) {
            qApp->quit();
        } else if (key->key()==Qt::Key_S) {
            m_qtSimPanel->saveSettings();
        } else if (key->key()==Qt::Key_Right) {
            m_qtSimPanel->setPanelPositionX(m_qtSimPanel->getPanelPositionX()+1);
        } else if (key->key()==Qt::Key_Left) {
            m_qtSimPanel->setPanelPositionX(m_qtSimPanel->getPanelPositionX()-1);
        } else if (key->key()==Qt::Key_Down) {
            m_qtSimPanel->setPanelPositionY(m_qtSimPanel->getPanelPositionY()+1);
        } else if (key->key()==Qt::Key_Up) {
            m_qtSimPanel->setPanelPositionY(m_qtSimPanel->getPanelPositionY()-1);
        } else if (key->key()==Qt::Key_Plus) {
            m_qtSimPanel->setPanelScale(m_qtSimPanel->getPanelScale()+0.02);
        } else if (key->key()==Qt::Key_Minus) {
            m_qtSimPanel->setPanelScale(m_qtSimPanel->getPanelScale()-0.02);
        } else if (key->key()==Qt::Key_I) {
            m_qtSimPanel->toggleInstructionVisibility();
        } else {
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        // Not a key press, let qt handle the event
        return QObject::eventFilter(obj, event);
    }
    return false;
}


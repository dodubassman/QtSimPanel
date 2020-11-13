#ifndef KEYRECEIVER_H
#define KEYRECEIVER_H

#include <QObject>
#include <QtSimPanel.h>

class KeyReceiver : public QObject
{
    Q_OBJECT

public:
    KeyReceiver(QtSimPanel* qtSimPanel);

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private:
    QtSimPanel* m_qtSimPanel;

};

#endif // KEYRECEIVER_H

#ifndef WHAM_H
#define WHAM_H

#define START  0xA1
#define SCAN   0xC1
#define SYNC   0xC2
#define NAME   0xB0
#define ACTIVE 0xB1
#define PIN    0xB2
#define TAG    0xB3
#define END    0xA2

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QLabel>
#include <QList>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

class wham : public QWidget
{
    Q_OBJECT
public:
    wham(QWidget *parent = 0);
    ~wham();
public slots:
    void serConnect(); //CONNECTS SERIAL PORT
    void serDisconnect(); //DISCONNECTS SERIAL PORT
    void enumerateSerPorts(); //FINDS AVAILABLE SERIAL PORTS
    void populateUI(QString);
    void saveFile();
    void sync();
    void scan();
private:
    void drawForm();
    QSerialPort *serial;
    QList<QSerialPortInfo> serinfo;
    QLabel *statuslbl, *portlbl;
    QComboBox *portlist, *UCB;
    QPushButton *connectPB, *disconnectPB, *enumeratePB, *syncPB, *savePB, *scanPB;
    QVBoxLayout *portvbox, *enumeratevbox, *finalform;
    QHBoxLayout *connectivityhbox, *porthbox, *ucbsynchbox;
    QPlainTextEdit *USERINFO;
};

#endif // WHAM_H

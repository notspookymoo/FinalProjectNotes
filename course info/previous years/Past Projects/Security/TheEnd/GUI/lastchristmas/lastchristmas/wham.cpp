#include "wham.h"

wham::wham(QWidget *parent)
    : QWidget(parent)
{
    drawForm();
    enumerateSerPorts();
    populateUI("user0");
    connect(UCB, SIGNAL(currentIndexChanged(QString)), this, SLOT(populateUI(QString)));
    connect(savePB, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(connectPB, SIGNAL(clicked()), this, SLOT(serConnect()));
    connect(disconnectPB, SIGNAL(clicked()), this, SLOT(serDisconnect()));
    connect(enumeratePB, SIGNAL(clicked()), this, SLOT(enumerateSerPorts()));
    connect(syncPB, SIGNAL(clicked()), this, SLOT(sync()));
    connect(scanPB, SIGNAL(clicked()), this, SLOT(scan()));
}

wham::~wham(){}

void wham::drawForm(){
    serial = new QSerialPort(this);

    finalform = new QVBoxLayout;

    portlbl = new QLabel("Port List");
    finalform->addWidget(portlbl);
    portlist = new QComboBox;
    enumeratePB = new QPushButton("Enumerate");
    porthbox = new QHBoxLayout;
    porthbox->addWidget(portlist);
    porthbox->addWidget(enumeratePB);
    finalform->addLayout(porthbox);
    connectivityhbox = new QHBoxLayout;
    connectPB = new QPushButton("Connect");
    connectivityhbox->addWidget(connectPB);
    disconnectPB = new QPushButton("Disconnect");
    connectivityhbox->addWidget(disconnectPB);
    finalform->addLayout(connectivityhbox);
    statuslbl = new QLabel;
    statuslbl->setText("STATUS: Serial port disconnected.");
    finalform->addWidget(statuslbl);
    ucbsynchbox = new QHBoxLayout;
    UCB = new QComboBox;
    finalform->addWidget(UCB);
    savePB = new QPushButton("Save");
    ucbsynchbox->addWidget(savePB);
    scanPB = new QPushButton("Scan");
    ucbsynchbox->addWidget(scanPB);
    syncPB = new QPushButton("Sync");
    ucbsynchbox->addWidget(syncPB);
    finalform->addLayout(ucbsynchbox);
    USERINFO = new QPlainTextEdit;
    for(int i = 0; i < 10; i++)
        UCB->addItem(QString("user%1").arg(i));
    finalform->addWidget(USERINFO);

    this->setLayout(finalform);
}

void wham::enumerateSerPorts(){
    portlist->clear();
    serinfo = QSerialPortInfo::availablePorts();

    for(int i = 0; i < serinfo.size(); i++){
        if(portlist->itemText(i) != serinfo.at(i).portName())
            portlist->addItem(serinfo.at(i).portName());
    }
}

void wham::serConnect(void){
    if(serinfo.count() == 0){ //NO PORTS
        QMessageBox::warning(this,"ERROR","No serial port found!");
    }
    else{ //1+ PORTS
        serial->setPort(serinfo[portlist->currentIndex()]);
        if(serial->isOpen()) //IF PORT ALREADY OPEN
            QMessageBox::warning(this,"ERROR","Serial port is already open. Please disconnect first");
        else{ //IF CLOSED, OPEN PORT
            if (serial->open(QIODevice::ReadWrite) == false){
                QMessageBox::warning(this,"ERROR","Failed to open port.");
                serial->close(); //CLOSE IF FAILED TO OPEN
            }
            else { //SET FOLLOWING PARAMETERS
                serial->setBaudRate(QSerialPort::Baud9600); //9600 BAUDRATE
                serial->setDataBits(QSerialPort::Data8); //8-BIT DATA
                serial->setParity(QSerialPort::NoParity); //NO PARITY
                serial->setFlowControl(QSerialPort::NoFlowControl); //NO FLOW CONTROL
                serial->setStopBits(QSerialPort::OneStop); //1 STOP BIT
                statuslbl->setText("STATUS: " + serinfo[portlist->currentIndex()].portName() + " is connected at 9600 8-N-1."); //UPDATE STATUS LABEL
            }
        }
    }
}

void wham::serDisconnect(void){
    if(serial->isOpen() == false)
        QMessageBox::warning(this,"ERROR","Serial port is already closed!");
    else{
        serial->close(); //CLOSE PORT
        statuslbl->setText("STATUS: Serial port disconnected."); //UPDATE STATUS LABEL
    }
}

void wham::populateUI(QString mystr){
    QString fileName = QString("C:\\Users\\YLavoie\\Desktop\\GUI_YL\\lastchristmas\\lastchristmas\\%1.txt").arg(mystr);
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SDI"), tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    USERINFO->setPlainText(in.readAll());
    this->setWindowModified(false);
    file.close();
}

void wham::saveFile(){
    QString fileName = QString("C:\\Users\\YLavoie\\Desktop\\GUI_YL\\lastchristmas\\lastchristmas\\%1.txt").arg(UCB->currentText());
    QFile file(fileName);
    if (!fileName.isEmpty() && !file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("SDI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << USERINFO->toPlainText();
    file.close();
}

void wham::sync(){

}

void wham::scan(){
    char DATA[5];
    QByteArray BA;

    BA.append(START);
    BA.append(SCAN);
    BA.append(END);

    serial->write(BA, BA.length());
    serial->waitForBytesWritten(-1);
    do{
        serial->waitForReadyRead(-1);
    }while(serial->bytesAvailable() < 5);
    serial->flush();
    serial->read(DATA, 5);
    serial->flush();
    qDebug() << "Received " + QByteArray(DATA,5) << endl;
    QString plswork;

   for(int cycle = 0; cycle < 4; cycle++){
        plswork += QString::number((unsigned char)DATA[cycle]);
        plswork.append(",");
    }
   plswork.append("0,0,0");

   USERINFO->appendPlainText(plswork);
}

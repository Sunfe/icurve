#ifndef ICV_COMMAND_H
#define ICV_COMMAND_H

#include <QtGlobal>
#include <QString>
#include <QStringList>
#include <QList>
#include <QPointF>

#define CMD_STARTED      (1)
#define CMD_CLOSED       (2)

#define ICV_PROMT_RFC    (1)
#define ICV_PROMT_BCM    (2)
#define ICV_PROMT_API    (3)
#define ICV_PROMT_FAST   (4)

class IcvCommand
{
public:
    IcvCommand();
    IcvCommand(QString cmd);
    IcvCommand(QString cmd, qint16 line, qint16 dir);
    ~IcvCommand();

    void reset();
    void initFamily();
    void initPromtFamily();
    void setFamily(QStringList cmdFamily);
    QStringList getFamily();
    void setPrompt(qint16 promt);
    QStringList getPromtFamily();

    bool matchTitle(QString dataLine);
    bool matchGroupSize(QString dataLine);
    QString dataPattern();
    qint16 getGroupSize();

    void setName(QString cmd);	
    QString getName();

    void setLineId(qint16 id);	
    qint16 getLineId();

    void setDirection(qint16 dir);	
    qint16 getDirection();

    void setData(QList<QPointF> points, bool isappend);
    QList<QPointF> getData();

    void setState(qint16 cmdState);
    qint16 getState();
    
    void setDataPosInFile(qint32 pos);
    qint32  getDataPosInFile();

    void setBriefInfo(QString info);
    QString getBriefInfo();

    void setFileName(QString name);
    QString getFileName();

    QString getCommandTitle();

private:
    QString        name;
    QString        promt;
    QList<QPointF> data;
    qint16         groupSize;
    QStringList    family;
    QStringList    promtFamily;

    qint16 lineId;
    qint16 direction;
    qint16 state;
    QString fileName;
    qint32 dataPosInFile;
    QString briefInfo;
};

#endif 


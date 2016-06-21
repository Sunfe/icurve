
#include "icv_command.h"

IcvCommand::IcvCommand(void)
{
    initFamily();
}


IcvCommand::~IcvCommand()
{
}


IcvCommand::IcvCommand(QString cmd)
{
    initFamily();
    name = cmd;
}


IcvCommand::IcvCommand(QString cmd,qint16 line, qint16 dir)
{
    initFamily();
    name      = cmd;
    lineId    = line;
    direction = dir;
    state     = CMD_CLOSED;
}


void IcvCommand::initFamily()
{
    family.push_back("getTxPsd");
    family.push_back("getSnr");
    family.push_back("getQln");
    family.push_back("getHlog");
    family.push_back("getNoiseMargin");		
}


void IcvCommand::reset()
{
    setName("NULL");
    setLineId(0xff);
    setDirection(0xff);
    setState(CMD_CLOSED);
    data.erase(data.begin(),data.end());

    return ;
}


void IcvCommand::setName(QString cmd)
{
    name = cmd;
    return ;
}


QString IcvCommand::getName()
{
    return name;
}


void IcvCommand::setLineId(qint16 id)
{
    lineId = id;
    return ;
}


qint16 IcvCommand::getLineId()
{
    return lineId;
}


void IcvCommand::setDirection(qint16 dir)
{
    direction = dir;
    return ;
}


qint16 IcvCommand::getDirection()
{
    return direction;
}


void IcvCommand::setData(QList<QPointF> points,bool isappend)
{
    if(true == isappend)
        data += points;
    else
        data = points;
    return ;
}


QList<QPointF> IcvCommand::getData()
{
    return data;
}


QStringList IcvCommand::getFamily()
{
    return family;
}


void IcvCommand::setFamily(QStringList cmdFamily)
{
    family = cmdFamily;
    return ;
}


void IcvCommand::setDataPosInFile(qint16 pos)
{
    dataPosInFile = pos;
    return;
}


qint16 IcvCommand::getDataPosInFile()
{
   return dataPosInFile;
}


void IcvCommand::setBriefInfo(QString info)
{
    briefInfo = info;
    return ;
}


QString IcvCommand::getBriefInfo()
{
     return briefInfo;
}


void IcvCommand::setState(qint16 cmdState)
{
    state = cmdState;
    return;
}


void IcvCommand::setFileName(QString name)
{
    fileName = name;
}

QString IcvCommand::getFileName()
{
    return fileName;
}


qint16 IcvCommand::getState()
{
    return state;
}


QString IcvCommand::getCommandTitle()
{
    QString lineIdStr = QString::number((int)lineId);
    QString    title  = name.remove("get") +".line " +  lineIdStr +\
        ((direction == 0)? ".US": ".DS");

    return title;
}



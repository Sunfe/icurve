
#include "Command.h"

Command::Command(void)
{
    initFamily();
}

Command::Command(QString cmd)
{
    initFamily();
    name = cmd;
}

Command::Command(QString cmd,qint16 line, qint16 dir)
{
    initFamily();
    name      = cmd;
    lineId    = line;
    direction = dir;
}

void Command::initFamily()
{
    family.push_back("getTxPsd");
    family.push_back("getSnr");
    family.push_back("getQln");
    family.push_back("getHlog");
    family.push_back("getNoiseMargin");		
}

Command::~Command()
{
}


void Command::setName(QString cmd)
{
    name = cmd;
    return ;
}


QString Command::getName()
{
    return name;
}


void Command::setLineId(qint16 id)
{
    lineId = id;
    return ;
}


qint16 Command::getLineId()
{
    return lineId;
}



void Command::setDirection(qint16 dir)
{
    direction = dir;
    return ;
}


qint16 Command::getDirection()
{
    return direction;
}


void Command::setData(QList<QPointF> number)
{
    data = number;
    return ;
}


QList<QPointF> Command::getData()
{
    return data;
}

QStringList Command::getFamily()
{
    return family;
}

void Command::setFamily(QStringList cmdFamily)
{
    family = cmdFamily;
    return ;
}




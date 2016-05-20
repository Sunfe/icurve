
#include "Command.h"

Command::Command(QString cmd,qint16 line, qint16 dir)
{
    family.push_back("getTxPsd");
    family.push_back("getSnr");
    family.push_back("getQln");
    family.push_back("getHlog");
    family.push_back("getNoiseMargin");

    name      = cmd;
    lineId    = line;
    direction = dir;
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


void Command::setData(QList<qreal> number)
{
    data = number;
    return ;
}


QList<qreal> Command::getData()
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




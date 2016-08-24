
#include "icv_command.h"

IcvCommand::IcvCommand(void)
{
    initFamily();
    initPromtFamily();
    initTitlePattern();
    groupSize = 1;
}


IcvCommand::IcvCommand(QString cmd)
{
    initFamily();
    initPromtFamily();
    initTitlePattern();
    groupSize = 1;
    name = cmd;
}


IcvCommand::IcvCommand(QString cmd,qint16 line, qint16 dir)
{
    initFamily();
    initPromtFamily();
    initTitlePattern();
    groupSize = 1;
    name      = cmd;
    lineId    = line;
    direction = dir;
    state     = CMD_CLOSED;
}


IcvCommand::~IcvCommand()
{

}


void IcvCommand::initFamily()
{
    family.push_back("getTxPsd");
    family.push_back("getSnr");
    family.push_back("getQln");
    family.push_back("getHlog");
    family.push_back("getNoiseMargin");
    family.push_back("getBitAlloc");
    family.push_back("getRmcBitAlloc");
    family.push_back("getAln");  
    return;
}


void IcvCommand::initPromtFamily()
{
    promtFamily.push_back("rfc");
    promtFamily.push_back("bcm");
    promtFamily.push_back("api");
    promtFamily.push_back("fast");

    return;
}


void IcvCommand::initTitlePattern()
{
    if(promtFamily.isEmpty() || family.isEmpty())
    {
        titlePattern = "";
        return;
    }

    QString pattern;
    pattern += "(";
    for(qint16 i = 0; i < promtFamily.count(); i++)
    {
        pattern += promtFamily.value(i);
        if(i < promtFamily.count() - 1)
            pattern += "|";
    }
    pattern += ").+(";

    for(qint16 i = 0; i < family.count(); i++)
    {
        pattern += family.value(i);
        if(i < family.count() - 1)
            pattern += "|";
    }
    pattern += ")\\s+([0-9]|[1-9][0-9]+)\\s+([0-1])";
    titlePattern = pattern;

    return;
}


void IcvCommand::reset()
{
    setName("NULL");
    setLineId(0xff);
    setDirection(0xff);
    setState(CMD_CLOSED);
    data.erase(data.begin(),data.end());

    groupSize = 1;
    promt = "";

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


QStringList IcvCommand::getPromtFamily()
{
    return promtFamily;
}


QString IcvCommand::getTitlePattern()
{
    return titlePattern;
}


bool IcvCommand::matchGroupSize(QString dataLine)
{
    QString pattern="grouped by ([1-9]) tones";
    QRegExp cmdRegExp;
    cmdRegExp.setPattern(pattern);
    cmdRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    bool isGroupsizeFound = dataLine.contains(cmdRegExp);
    if(isGroupsizeFound)
    {
        QStringList caps = cmdRegExp.capturedTexts();
        bool ok = false;
        groupSize = caps[1].toInt(&ok);
        return true;
    }

    return false;
}


qint16 IcvCommand::getGroupSize()
{
    return groupSize;
}


QString IcvCommand::getDataPattern()
{
    QString pattern;
    if("fast" == promt)
    {
        pattern = "([ ]+-{,1}\\d{1,}\.\\d\,){1,10}";
    }
    else /* rfc, api,bcm, .. */
    {
        if("getBitAlloc" == name)
        {
            /* pattern like: 360 : 11 11 11 12 12 12 13 13 */
            pattern = "\\s+\\d{1,5}\\s+:(\\s+\\d+){1,20}$";
        }
        else if("getRmcBitAlloc" == name)
        {
            /*pattern like: 43:  x  x  x  x  x  x */
            pattern = "\\s+\\d+:(\\s+\\d+){1,20}$";
        }
        else
        {
            pattern = "\\s+\\d{1,5}\\s+:(\\s+-{,1}\\d{1,}\\.\\d+\\s?){1,10}$";
        }
    }

    return pattern;
}


void IcvCommand::setFamily(QStringList cmdFamily)
{
    family = cmdFamily;
    return ;
}


void IcvCommand::setPrompt(QString cmdPromt)
{
    promt = cmdPromt;
    return ;
}


QString IcvCommand::getPromt()
{
    return promt;
}


void IcvCommand::setDataPosInFile(qint32 pos)
{
    dataPosInFile = pos;
    return;
}


qint32 IcvCommand::getDataPosInFile()
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



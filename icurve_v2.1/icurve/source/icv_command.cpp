#include <QDebug>
#include "icv_command.h"
#include "icurve_common.h"
#include "icv_pattern_table.h"


IcvCommand::IcvCommand(void)
{
    initFamily();
    initPromtFamily();
    initTitlePattern();
    initDataPattern();
    groupSize = 1;
    dataScopeMode = ICV_DATA_SCOPE_BCM;
}

IcvCommand::IcvCommand(QString cmd)
{
    initFamily();
    initPromtFamily();
    initTitlePattern();
    initDataPattern();
    groupSize = 1;
    name = cmd;
    dataScopeMode = ICV_DATA_SCOPE_BCM;
}

IcvCommand::IcvCommand(QString cmd,qint16 line, qint16 dir)
{
    initFamily();
    initPromtFamily();
    initTitlePattern();
    initDataPattern();
    groupSize = 1;
    name      = cmd;
    lineId    = line;
    direction = dir;
    state     = CMD_CLOSED;
    dataScopeMode = ICV_DATA_SCOPE_BCM;
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
   #if 0
 if(ICV_DATA_SCOPE_CLI == dataScopeMode)
    {
        titlePattern = "scstatus-segment\\s+(Bitload|Qln|SNR|GainAlloc|Hlog|LinImg|LinReal)\\s+(vdsl|adsl)_\\d+/\\d+/(\\d+)\\s?$";
        return;
    }

    if(promtFamily.isEmpty() || family.isEmpty())
    {
        titlePattern = "icurve";
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
    pattern += ")\\s+([0-9]|[1-9][0-9]+)\\s+([0-1])?";
    titlePattern = pattern;
    return;
#endif

    bool isEnd = false;
    for(qint16 i = 0; (i < ICV_MAX_TITLE_PATTERN_NUM) && !isEnd; i++)
    {
        titlePatternRepo.append(icvCmdTitlePatternTbl[i]);
        isEnd = icvCmdTitlePatternTbl[i].isEmpty();
    }
    return;
}

void IcvCommand::initDataPattern()
{
    bool isEnd = false;
    for(qint16 i = 0; (i < ICV_MAX_DATA_PATTERN_NUM) && !isEnd; i++)
    {
        dataPatternRepo.append(qMakePair(icvCmdDataPatternTbl[i][0], icvCmdDataPatternTbl[i][1]));
        isEnd = icvCmdDataPatternTbl[i][0].isEmpty();
    }
    return;
}

void IcvCommand::reset()
{
    setName("NULL");
    setLineId(0xff);
    setDirection(0xff);
    setState(CMD_NOT_FOUND);

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

void IcvCommand::clearData()
{
    data.clear();
    return;
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
#if 0
    for(qint16 i = 0; i < titlePatternRepo.count(); i++)
    {
        qDebug() << titlePatternRepo.at(i);
        if(titlePatternRepo.at(i) == promt)
            return titlePatternRepo.at(i).second;
    }
#endif
    return titlePatternRepo.at(0);
}

QString IcvCommand::getDataPattern()
{
    if(ICV_DATA_SCOPE_CLI == dataScopeMode)
    {
        return "^\\s+(\\s+[\\dA-F]{2}){16}";
    }

    for(qint16 i = 0; i < dataPatternRepo.count(); i++)
    {
        if(dataPatternRepo.at(i).first == (promt + " " + name))
            return dataPatternRepo.at(i).second;
    }
    return "";
}

bool IcvCommand::matchGroupSize(QString dataLine)
{
    QString pattern;
    if(ICV_DATA_SCOPE_CLI == dataScopeMode)
        pattern = "LogScGroupSize\\s+:(\\d+)\\s?$";
    else
        pattern="grouped by ([1-9]+) tones";

    QRegExp cmdRegExp;
    cmdRegExp.setPattern(pattern);
    cmdRegExp.setCaseSensitivity(Qt::CaseInsensitive);
    bool isGroupsizeFound = dataLine.contains(cmdRegExp);
    if(isGroupsizeFound)
    {
        QStringList caps = cmdRegExp.capturedTexts();
        bool ok = false;
        if(caps.count() > 2)
            groupSize = caps[1].toInt(&ok);
        return true;
    }
    return false;
}

qint16 IcvCommand::getGroupSize()
{
    return groupSize;
}

void IcvCommand::setDataScopeMode(qint16 scope)
{
    dataScopeMode = scope;
}

qint16 IcvCommand::getDataScopeMode()
{
    return dataScopeMode;
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
    return;
}

QString IcvCommand::getFileName()
{
    return fileName;
}

qint16 IcvCommand::getState()
{
    return state;
}

QString IcvCommand::getTitle()
{
    QString line = QString::number((int)lineId);
    QString cmdName   = getName();
    QString    title  = cmdName.remove("get") +".line " +  line +\
        ((direction == 0)? ".US": ".DS");

    return title;
}


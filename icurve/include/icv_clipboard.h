#pragma once

#include <QMetaType>
#include <QList>
#include <icv_command.h>

class IcvClipBoard
{
public:
    QList<IcvCommand> data; 
};

Q_DECLARE_METATYPE(IcvClipBoard);

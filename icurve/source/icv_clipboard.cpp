#include "icv_clipboard.h"


#if 0
IcvClipBoard::IcvClipBoard(QList<QwtPlotCurve *>curve)
{
    for(qint16 cnt = 0; cnt < curve.count(); cnt++)
    {
        data.insert(cnt, *(curve.at(cnt)));
    }
}

IcvClipBoard::~IcvClipBoard(void)
{

}

void IcvClipBoard::setData(QwtPlotCurve *curve)
{ 
    return;
}
#endif
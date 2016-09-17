#include <QPainterPath>
#include <QPen>
#include <QTransform>
#include <QPointF>

#include "icv_symbol.h"

IcvSymbol::IcvSymbol(IcvSymbol::Style styleType, QColor color)
{
    if(styleType == IcvSymbol::Arrow)
    {
        QPen pen(color);
        pen.setJoinStyle( Qt::MiterJoin );

        setPen(pen);
        setBrush(color);

        QPainterPath path;
        path.moveTo( 0, 8 );
        path.lineTo( 0, 4 );
        path.lineTo( -2, 4 );
        path.lineTo( 0, 0 );
        path.lineTo( 2, 4 );
        path.lineTo( 0, 4 );

        QTransform transform;
        transform.rotate( 210.0 );
        path = transform.map( path );

        setPath( path );
        setPinPoint( QPointF( 0, 0 ) );

        setSize( 10, 14 );
    }
}

IcvSymbol::~IcvSymbol(void)
{

}

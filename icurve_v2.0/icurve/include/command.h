#ifndef COMMAND_H
#define COMMAND_H

#include <QtGlobal>
#include <QString>
#include <QStringList>
#include <QList>
#include <QPointF>

class Command
{

    public:
        Command();
        Command(QString cmd);
        Command(QString cmd, qint16 line, qint16 dir);
        ~Command();

		void reset();

        void initFamily();

        void setName(QString cmd);	
        QString getName();

        void setLineId(qint16 id);	
        qint16 getLineId();

		 void setDirection(qint16 dir);	
        qint16 getDirection();


        void setData(QList<QPointF> points, bool isappend);
        QList<QPointF> getData();

        void setFamily(QStringList cmdFamily);
        QStringList getFamily();

    private:
        QString name;
        QList<QPointF> data;
        QStringList  family;
        qint16 lineId;
        qint16 direction;

};

#endif // ICURVE_H


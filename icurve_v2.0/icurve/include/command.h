#ifndef COMMAND_H
#define COMMAND_H

#include <QtGlobal>
#include <QString>
#include <QStringList>
#include <QList>


class Command
{

    public:
        Command(QString cmd, qint16 line, qint16 dir);
        ~Command();

        void setName(QString cmd);	
        QString getName();

        void setData(QList<qreal>);
        QList<qreal> getData();

        void Command::setFamily()
            QStringList getFamily();

    private:
        QString name;
        QList<QPointF> data;
        QStringList  family;
        qint16 lineId;
        qint16 direction;

};

#endif // ICURVE_H


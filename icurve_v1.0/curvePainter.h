
#ifndef _CURVE_PAINTER_H
#define _CURVE_PAINTER_H

#include <Qt>
#include <QLine>
#include <QPen>
#include <QPoint>
#include <QPainter>
#include <QVariant>
#include <QtGui>
#include <QSize>

class CurvePainter
{
    public:
        CurvePainter(Qt::PenStyle s = Qt::SolidLine);
        ~CurvePainter();

        void paint(QPainter *painter, const QRect &rect, const QPalette &palette);

    private:
        Qt::PenStyle style;

};

Q_DECLARE_METATYPE(CurvePainter)


    class CurveDelegate : public QStyledItemDelegate
{
    Q_OBJECT

    public:
        CurveDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent){
        }

        void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

        QWidget *createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
        void setEditorData ( QWidget * editor, const QModelIndex & index ) const;
        void setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;


    private:

};


class CurveDelegateEditor : public QWidget
{
    Q_OBJECT
    public:
        CurveDelegateEditor(QWidget * parent = 0, Qt::WindowFlags f = 0);
        ~CurveDelegateEditor();

        void SetCurve(CurvePainter painter){
            curvePainter = painter;
        };
        CurvePainter getPainter(){
            return curvePainter;
        };

    protected:
        void painterEvent(QPaintEvent *event);

    private:
        CurvePainter curvePainter;

};


class PenComboBox : public QComboBox
{
    Q_OBJECT

    public:
        PenComboBox(QWidget * parent = 0 );
        ~PenComboBox();

    protected:
        void paintEvent ( QPaintEvent * e );
    private:
        int m ;

};




#endif

#include "CurvePainter.h"
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <string>
#include <QIODevice>


/**********************************/
/********paint specific  line************/
/**********************************/
CurvePainter::CurvePainter(Qt::PenStyle s)
{
    style = s;
}

void CurvePainter::paint(QPainter *painter, const QRect &rect, const QPalette &palette)
{
    painter->save();

    QPen pen(Qt::black);
    pen.setStyle(style);
    painter->setPen(pen);


    QPoint point1,point2;
    point1.setX(rect.left());
    point1.setY((rect.top() + rect.bottom())/2);
    point2.setX(rect.right());
    point2.setY(point1.ry());

#if 0
    FILE *wfile=NULL;
    if((wfile=fopen("d:\\w.txt","w+"))==NULL)
    {
        return;
    }

    QString wStr;
    wStr+=  QString::number(point1.ry());
    QTextStream out(wfile,QIODevice::WriteOnly);
    out<<wStr;
#endif


    painter->restore();

}

CurvePainter::~CurvePainter()
{

}

/**********************************/
/**********Line Delegate**************/
/**********************************/
void CurveDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
#if 0
    if(qVariantCanConvert<LinePainter>(index.data()))
    {
        LinePainter line = qVariantValue<LinePainter>(index.data());
        line.paint(painter, option.rect, option.palette);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
    QStyledItemDelegate::paint(painter, option, index);
#endif

    QRect rect = option.rect;
    rect.adjust(+5, 0, -5, 0);

    painter->save();

    QPen pen(Qt::red);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);

    int middle = (rect.bottom() + rect.top()) / 2;
    painter->drawLine(rect.left(), middle, rect.right(), middle);

    painter->restore();


}

QWidget *CurveDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    if (qVariantCanConvert<CurvePainter>(index.data())) {
        CurveDelegateEditor *editor = new CurveDelegateEditor(parent);
        return editor;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void CurveDelegate::setEditorData ( QWidget * editor, const QModelIndex & index ) const
{

    if (qVariantCanConvert<CurvePainter>(index.data())) {
        CurvePainter line = qVariantValue<CurvePainter>(index.data());
        CurveDelegateEditor *editor= qobject_cast<CurveDelegateEditor *>(editor);
        editor->SetCurve(line);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void CurveDelegate::setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const
{
#if 0
    if (qVariantCanConvert<CurvePainter>(index.data())) {
        CurveDelegateEditor *editor= qobject_cast<CurveDelegateEditor *>(editor);
        model->setData(index, qVariantFromValue(editor->curvePainter()));
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
#endif
}


/**********************************/
/**********Line Delegate editor**************/
/**********************************/

    CurveDelegateEditor::CurveDelegateEditor(QWidget * parent, Qt::WindowFlags f)
: QWidget(parent)
{
    setMouseTracking(true);
    //setAutoFillBackground(true);

}

void CurveDelegateEditor::painterEvent(QPaintEvent *event)
{

    QPainter painter(this);
    curvePainter.paint(&painter, rect(), this->palette());
}


CurveDelegateEditor::~CurveDelegateEditor()
{


}

/**********************************/
/**********Line Delegate**************/
/**********************************/
    PenComboBox::PenComboBox(QWidget * parent )
: QComboBox(parent)
{
    m = 0;
}

PenComboBox::~PenComboBox()
{

}

void PenComboBox::paintEvent ( QPaintEvent * e )
{

    QComboBox::paintEvent( e); 

    QPainter painter(this);
    QRect rect = e->rect();
    rect.adjust(+5, 0, -5, 0);

    painter.save();
    QPen pen(Qt::red);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    int middle = (rect.bottom() + rect.top()) / 2;
    painter.drawLine(rect.left(), middle, rect.right(), middle);

}




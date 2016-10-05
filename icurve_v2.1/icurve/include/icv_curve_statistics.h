#ifndef ICV_CURVE_STATISTICS
#define ICV_CURVE_STATISTICS

#include <QTableView>
class IcvCurveStatistics : public QTableView 
{
     Q_OBJECT

public:
      IcvCurveStatistics(QAbstractItemModel * model, QWidget * parent);
      ~IcvCurveStatistics();

protected:
      virtual void resizeEvent(QResizeEvent *event);
      virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
      void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible);

private:
      QTableView *statTableView;
      void init();
      void updateFrozenTableGeometry();

private slots:
      void updateSectionWidth(int logicalIndex,int, int newSize);
      void updateSectionHeight(int logicalIndex, int, int newSize);

};

#endif

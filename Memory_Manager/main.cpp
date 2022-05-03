#include <QApplication>
#include <QtCharts>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QChartView w;

    QBarSet *set0 = new QBarSet("Bytes in each section");

    *set0 << 1 << 4 << 3 << 7 << 2 << 5 << 1 << 3 << 3 << 2 << 1 << 6 << 7 << 5;

    QBarSeries *series = new QBarSeries;
    series->append(set0);


    QChart *chart= new QChart;
    w.setChart(chart);
    chart->addSeries(series);
    chart->legend()->setVisible(false);
    w.show();


    QGraphicsRectItem hoverItem;
    hoverItem.setBrush(QBrush(Qt::darkBlue));
    hoverItem.setPen(Qt::NoPen);

    QObject::connect(set0, &QBarSet::hovered, [&w, &hoverItem](bool status, int index){
        QPoint p = w.mapFromGlobal(QCursor::pos());
        if(status){
            QGraphicsItem *it = w.itemAt(p);
            hoverItem.setParentItem(it);
            hoverItem.setRect(it->boundingRect());
            hoverItem.show();
        }
        else{
            hoverItem.setParentItem(nullptr);
            hoverItem.hide();
        }
    });
    return a.exec();
}

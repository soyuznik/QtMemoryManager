#include <QApplication>
#include "SelfBarSet.h"
#include <QListWidget>
#include <random>
#include <iostream>


////////////////////////////////////////
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <ctime>
#include <chrono>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget* window = new QWidget();
    //////////////////////////////////////////////////////////////////
    /// \brief
    /// definitions
    QChartView w;
    SelfBarSet *set = new SelfBarSet();
    QBarSeries *series = new QBarSeries;
    QGraphicsRectItem hoverItem;
    QChart *chart= new QChart;
    QHBoxLayout* baseL = new QHBoxLayout(window);
    QListWidget* list = new QListWidget();
    /////////////////////////////////////////////////////////
    /// \brief
    /// first entry


    baseL->addWidget((list));
    baseL->addWidget(&w);

    std::vector<float> data;
    for(int i = 0 ; i < 10 ; i++){
        data.push_back(i);
        list->addItem(std::to_string(i).c_str());
    }
    set->add_data(data);

    series->append(set->set0);
    w.setChart(chart);
    chart->addSeries(series);
    chart->legend()->setVisible(false);
    hoverItem.setBrush(QBrush(Qt::darkBlue));
    hoverItem.setPen(Qt::NoPen);



    ////////////////////////////////////////////
    /// other definitions /////////////////////
    QObject::connect(set->set0, &QBarSet::hovered, [&set , &w, &hoverItem](bool status, int index){

        std::cout << std::to_string(set->get_value(index));
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










    //////////////////////////////////////////
    window->show();


    auto start_time = std::chrono::steady_clock::now();
    QDirIterator it("D:/Steam",QDirIterator::Subdirectories);
    QStringList list_;
    qint64 size = 0;
    quint16 cnt(0);
    while (it.hasNext()) {
        it.next();
        ++cnt;
        if (QFileInfo(it.filePath()).isFile())
            if (QFileInfo(it.filePath()).suffix() == "a"){
                list_ << it.filePath();

            }
    }
    qDebug() << size << "\n";
    qDebug() << QString("Number of files/directories searched in %1 = %2").arg(it.path()).arg(cnt);
    qDebug() << QString("Number of files found = %2").arg(list_.count());
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    qDebug() << elapsed.count() <<" milliseconds";


    return a.exec();
}

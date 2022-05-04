#include <QApplication>
#include "SelfBarSet.h"
#include <QListWidget>
#include <random>
#include <iostream>


////////////////////////////////////////
#include <QDir>
#include <QDebug>
#include <QDirIterator>

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
    QHBoxLayout* baseL = new QHBoxLayout();
    QHBoxLayout* upperL = new QHBoxLayout();
    QVBoxLayout* centralL = new QVBoxLayout();
    QListWidget* list = new QListWidget();
    QTextEdit* diskBar = new QTextEdit();
    QTextEdit* upperBar = new QTextEdit();
    QPushButton* browse = new QPushButton();
    /////////////////////////////////////////////////////////
    /// \brief
    /// first entry
    diskBar->setEnabled(false);
    diskBar->setMaximumHeight(26);
    upperBar->setMaximumHeight(26);
    browse->setMinimumHeight(27);


    upperL->addWidget(upperBar);
    upperL->addWidget(browse);
    baseL->addWidget((list));
    baseL->addWidget(&w);
    centralL->addLayout(upperL); // upper first
    centralL->addLayout(baseL);
    centralL->addWidget(diskBar);


    window->setLayout(centralL);





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
    QObject::connect(set->set0, &QBarSet::hovered, [&diskBar, &set , &w, &hoverItem](bool status, int index){

        diskBar->setText(QString::fromStdString(std::string("clicked index nr --> ") + std::to_string((int)set->get_value(index))));
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
    return a.exec();
}


#include <SelfBarSet.h>
#include <iostream>
#include <thread>









int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        QWidget* window = new QWidget();
        //////////////////////////////////////////////////////////////////
        /// \brief
        /// definitions
        QChartView w;
        SelfBarSet *set = new SelfBarSet();

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



        upperBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        diskBar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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



        updateList(upperBar, list, &w, chart , set);
        chart->legend()->setVisible(false);






        ////////////////////////////////////////////
        /// other definitions /////////////////////


        QObject::connect(set->set0, &QBarSet::hovered, [&diskBar, &set , &w](bool status, int index){
            QGraphicsRectItem hoverItem;
            hoverItem.setBrush(QBrush(Qt::darkBlue));
            hoverItem.setPen(Qt::NoPen);
            diskBar->setText(QString::fromStdString(std::string("clicked index nr --> ") + set->get_value(index)));
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
        QObject::connect(upperBar, &QTextEdit::textChanged, [&upperBar , &list , &w , &chart , &set](){
            //updateList(QTextEdit* upperBar , QListWidget* list , QChartView* w , SelfBarSet *set , QBarSeries *series , QChart *chart)
            chart->removeAllSeries();
            std::thread update_list(&updateList , upperBar, list, &w, chart , set);
            update_list.detach();
        });



        //////////////////////////////////////////
        window->show();
        return a.exec();


}

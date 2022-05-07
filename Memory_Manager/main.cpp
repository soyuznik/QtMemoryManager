#include <GetDirSize.h>
#include <SelfBarSet.h>
#include <iostream>
#include <thread>







std::map<std::string , long> /*std::map<std::string , double>*/ ListItems(std::string dir){
    std::map<std::string , long> __list;
    QDir source(QString::fromStdString((dir)));
    QStringList const files = source.entryList(QDir::Files);
    QStringList const folders = source.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    foreach(QString str, files) {
        QFile File((dir + "/" + str.toStdString()).c_str());
      __list.insert(std::make_pair(str.toStdString() , File.size()));
    }
    foreach(QString str, folders) {
       __list.insert(std::make_pair(str.toStdString() , dirSize((dir + "/" + str.toStdString()).c_str())));
    }
    return __list;

}

void updateList(QTextEdit* upperBar , QListWidget* list , QChartView* w , QChart *chart){

    list->clear();
    QString target_dir = upperBar->toPlainText();
    //std::cout << target_dir.toStdString() << std::endl;
    std::map<std::string , long> list_Data = ListItems(target_dir.toStdString());
    if(list_Data.size() == 0){
        return;
    }
    std::vector<float> chart_Data;
    std::vector<std::string> chart_Names;
    for (auto const& [dir, size] : list_Data)
    {
        chart_Data.push_back((float)size);
        std::string itemData = dir;
        chart_Names.push_back(itemData);
        list->addItem(QString(itemData.c_str()));
    }
    SelfBarSet *set1 = new SelfBarSet();
    QBarSeries *series1 = new QBarSeries();
    set1->add_data(chart_Names , chart_Data);
    series1->append(set1->set0);
    chart->removeAllSeries();
    w->setChart(chart);
    chart->addSeries(series1);
}




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



        QString target_dir = upperBar->toPlainText();
        if(target_dir.toStdString() == ""){
            target_dir = ".";
        }
        std::map<std::string , long> list_Data = ListItems(target_dir.toStdString());
        std::vector<float> chart_Data;
        std::vector<std::string> chart_Names;
        for (auto const& [dir, size] : list_Data)
        {
            chart_Data.push_back((float)size);
            std::string itemData = dir;
            chart_Names.push_back(itemData);
            list->addItem(QString(itemData.c_str()));
        }

        set->add_data(chart_Names , chart_Data);
        series->append(set->set0);
        w.setChart(chart);
        chart->addSeries(series);
        chart->legend()->setVisible(false);
        hoverItem.setBrush(QBrush(Qt::darkBlue));
        hoverItem.setPen(Qt::NoPen);



        ////////////////////////////////////////////
        /// other definitions /////////////////////


        QObject::connect(set->set0, &QBarSet::hovered, [&diskBar, &set , &w, &hoverItem](bool status, int index){

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
        QObject::connect(upperBar, &QTextEdit::textChanged, [&upperBar , &list , &w , &chart](){
            //updateList(QTextEdit* upperBar , QListWidget* list , QChartView* w , SelfBarSet *set , QBarSeries *series , QChart *chart)
            chart->removeAllSeries();
            std::thread update_list(&updateList , upperBar, list, &w, chart);
            update_list.detach();
        });



        //////////////////////////////////////////
        window->show();
        return a.exec();


}

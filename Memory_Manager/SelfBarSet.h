#pragma once

#include <QtCharts>
#include <vector>
#include <GetDirSize.h>

class SelfBarSet{
public:
    std::string dataForDiskBar = " ";
    std::map<int , std::string> BarSetData;
    QBarSet* set0 = new QBarSet("");
    SelfBarSet();
    void add_data(std::vector<std::string> _data , std::vector<float> data);
    std::string get_value(int index);



};
SelfBarSet::SelfBarSet(){

}
std::string SelfBarSet::get_value(int index){
    for (const auto& [__index, value] : BarSetData) {
        if(index == __index){
            return value;
        }
    }
}
void SelfBarSet::add_data(std::vector<std::string> _data , std::vector<float> data){
    BarSetData.clear();
    for(int i = 0; i < (int)data.size(); i++){
        //here insted of first data[i] is gonna be the folder/file path    //1
        BarSetData.insert(std::make_pair(i , _data[i] /* 1 */));
        // instead of the second is gonna be the bytes/kb value && get_value is going to get the path and the bytes shown in the list;

        set0->insert(i , data[i]);
    }
}


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

void updateList(QTextEdit* upperBar , QListWidget* list , QChartView* w , QChart *chart , SelfBarSet* __return){

    list->clear();
    QString target_dir = upperBar->toPlainText();
    if(target_dir.toStdString() == ""){
        target_dir = ".";
    }
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
    __return = set1;
}


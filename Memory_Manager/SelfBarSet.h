#pragma once

#include <QtCharts>
#include <vector>


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


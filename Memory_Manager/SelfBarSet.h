#pragma once

#include <QtCharts>
#include <vector>


class SelfBarSet{
public:
    std::string dataForDiskBar = " ";
    std::map<int , float> BarSetData;
    QBarSet* set0 = new QBarSet("");
    SelfBarSet();
    void add_data(std::vector<float> data);
    float get_value(int index);



};
SelfBarSet::SelfBarSet(){

}
float SelfBarSet::get_value(int index){
    for (const auto& [__index, value] : BarSetData) {
        if(index == __index){
            return value;
        }
    }
}
void SelfBarSet::add_data(std::vector<float> data){
    for(int i = 0; i < data.size(); i++){
        //here insted of first data[i] is gonna be the folder/file path    //1
        BarSetData.insert(std::make_pair(i , data[i] /* 1 */));
        // instead of the second is gonna be the bytes/kb value && get_value is going to get the path and the bytes shown in the list;
        set0->insert(i , data[i]);
    }
}


#pragma once

#include <GetDirSize.h>
#include <SelfBarSet.h>
#include <iostream>
/*
 *
 * docs
QDir const source(path);
    if (!source.exists())
        return;

    QStringList const files = source.entryList(QStringList() << "*.mp4", QDir::Files);
    QStringList const folders = source.entryList(QDir::NoDot | QDir::NoDotDot | QDir::Dirs);

    QStringList const all = folders + files;

    for (QString const& name: all)
    {
        QString const fullPathName = path + QDir::separator() + name;
        if (QFileInfo(fullPathName).isDir())
        {
            setItems(fullPathName, level++);
            continue;
        }
        qDebug() << "Level " << level << " " << fullPathName;
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

inline /*std::map<std::string , double>*/ void ListItems(std::string dir){
    QDir source(QString::fromStdString((dir)));
    QStringList const files = source.entryList(QDir::Files);
    QStringList const folders = source.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    std::vector<std::string> __list;
    foreach(QString str, files) {
      __list.push_back(str.toStdString());
    }
    foreach(QString str, folders) {
      __list.push_back(str.toStdString());
    }

    for(int i = 0; i < (int)__list.size(); i++){
        std::cout << "__list -->" << __list[i] << std::endl;
    }

}

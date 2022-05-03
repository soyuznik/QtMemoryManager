/********************************************************************************
** Form generated from reading UI file 'diagramwin.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGRAMWIN_H
#define UI_DIAGRAMWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiagramWin
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DiagramWin)
    {
        if (DiagramWin->objectName().isEmpty())
            DiagramWin->setObjectName(QString::fromUtf8("DiagramWin"));
        DiagramWin->resize(800, 600);
        centralwidget = new QWidget(DiagramWin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        DiagramWin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DiagramWin);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        DiagramWin->setMenuBar(menubar);
        statusbar = new QStatusBar(DiagramWin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DiagramWin->setStatusBar(statusbar);

        retranslateUi(DiagramWin);

        QMetaObject::connectSlotsByName(DiagramWin);
    } // setupUi

    void retranslateUi(QMainWindow *DiagramWin)
    {
        DiagramWin->setWindowTitle(QCoreApplication::translate("DiagramWin", "DiagramWin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiagramWin: public Ui_DiagramWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGRAMWIN_H

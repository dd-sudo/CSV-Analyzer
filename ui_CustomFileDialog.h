/********************************************************************************
** Form generated from reading UI file 'CustomFileDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMFILEDIALOG_H
#define UI_CUSTOMFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CustomFileDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *filePathEdit;
    QListView *listView;
    QLineEdit *fileNameEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelBtn;
    QPushButton *okBtn;

    void setupUi(QDialog *CustomFileDialog)
    {
        if (CustomFileDialog->objectName().isEmpty())
            CustomFileDialog->setObjectName(QString::fromUtf8("CustomFileDialog"));
        CustomFileDialog->resize(400, 378);
        verticalLayout = new QVBoxLayout(CustomFileDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(15, 10, 15, 10);
        filePathEdit = new QLineEdit(CustomFileDialog);
        filePathEdit->setObjectName(QString::fromUtf8("filePathEdit"));
        filePathEdit->setMouseTracking(false);
        filePathEdit->setTabletTracking(true);
        filePathEdit->setContextMenuPolicy(Qt::NoContextMenu);
        filePathEdit->setAcceptDrops(false);
        filePathEdit->setFrame(true);
        filePathEdit->setCursorPosition(0);
        filePathEdit->setReadOnly(true);

        verticalLayout->addWidget(filePathEdit);

        listView = new QListView(CustomFileDialog);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setContextMenuPolicy(Qt::NoContextMenu);
        listView->setFrameShape(QFrame::NoFrame);
        listView->setFrameShadow(QFrame::Plain);
        listView->setLineWidth(1);
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listView->setProperty("showDropIndicator", QVariant(false));
        listView->setDefaultDropAction(Qt::CopyAction);
        listView->setLayoutMode(QListView::SinglePass);
        listView->setViewMode(QListView::ListMode);
        listView->setModelColumn(0);
        listView->setUniformItemSizes(false);

        verticalLayout->addWidget(listView);

        fileNameEdit = new QLineEdit(CustomFileDialog);
        fileNameEdit->setObjectName(QString::fromUtf8("fileNameEdit"));
        fileNameEdit->setReadOnly(false);

        verticalLayout->addWidget(fileNameEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, 0, -1);
        cancelBtn = new QPushButton(CustomFileDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setAutoDefault(false);

        horizontalLayout->addWidget(cancelBtn);

        okBtn = new QPushButton(CustomFileDialog);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setAutoDefault(false);

        horizontalLayout->addWidget(okBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CustomFileDialog);

        QMetaObject::connectSlotsByName(CustomFileDialog);
    } // setupUi

    void retranslateUi(QDialog *CustomFileDialog)
    {
        CustomFileDialog->setWindowTitle(QApplication::translate("CustomFileDialog", "Dialog", nullptr));
        cancelBtn->setText(QApplication::translate("CustomFileDialog", "Cancel", nullptr));
        okBtn->setText(QApplication::translate("CustomFileDialog", "Open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomFileDialog: public Ui_CustomFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMFILEDIALOG_H

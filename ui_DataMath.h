/********************************************************************************
** Form generated from reading UI file 'DataMath.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMATH_H
#define UI_DATAMATH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DataMath
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *dataLabels;
    QListWidget *operatorList;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *dataMath;
    QPushButton *clear;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DataMath)
    {
        if (DataMath->objectName().isEmpty())
            DataMath->setObjectName(QString::fromUtf8("DataMath"));
        DataMath->resize(640, 480);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DataMath->sizePolicy().hasHeightForWidth());
        DataMath->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        DataMath->setFont(font);
        verticalLayout = new QVBoxLayout(DataMath);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        dataLabels = new QListWidget(DataMath);
        dataLabels->setObjectName(QString::fromUtf8("dataLabels"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        dataLabels->setFont(font1);
        dataLabels->setProperty("showDropIndicator", QVariant(false));
        dataLabels->setDragEnabled(false);
        dataLabels->setDragDropMode(QAbstractItemView::NoDragDrop);

        horizontalLayout->addWidget(dataLabels);

        operatorList = new QListWidget(DataMath);
        operatorList->setObjectName(QString::fromUtf8("operatorList"));
        operatorList->setFont(font1);
        operatorList->setProperty("showDropIndicator", QVariant(false));
        operatorList->setDragEnabled(false);
        operatorList->setDragDropMode(QAbstractItemView::NoDragDrop);

        horizontalLayout->addWidget(operatorList);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(DataMath);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(DataMath);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font2);

        horizontalLayout_2->addWidget(label);

        dataMath = new QLineEdit(DataMath);
        dataMath->setObjectName(QString::fromUtf8("dataMath"));
        dataMath->setFont(font2);
        dataMath->setAcceptDrops(false);
        dataMath->setReadOnly(true);

        horizontalLayout_2->addWidget(dataMath);

        clear = new QPushButton(DataMath);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setFont(font2);

        horizontalLayout_2->addWidget(clear);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(DataMath);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setFont(font2);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DataMath);
        QObject::connect(buttonBox, SIGNAL(accepted()), DataMath, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DataMath, SLOT(reject()));

        QMetaObject::connectSlotsByName(DataMath);
    } // setupUi

    void retranslateUi(QDialog *DataMath)
    {
        DataMath->setWindowTitle(QApplication::translate("DataMath", "Create new derived data (Data Math)", nullptr));
        label_2->setText(QApplication::translate("DataMath", "Math operations are evaluated left to right.", nullptr));
        label->setText(QApplication::translate("DataMath", "Data Math:", nullptr));
#ifndef QT_NO_TOOLTIP
        dataMath->setToolTip(QApplication::translate("DataMath", "A derived data element is a data element derived from other data elements using a mathematical, logical, or other type of transformation, e.g. arithmetic formula, composition, aggregation.", nullptr));
#endif // QT_NO_TOOLTIP
        dataMath->setInputMask(QString());
        clear->setText(QApplication::translate("DataMath", "Undo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataMath: public Ui_DataMath {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMATH_H

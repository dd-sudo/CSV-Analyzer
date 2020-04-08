/********************************************************************************
** Form generated from reading UI file 'SimpleCsvLogAnalyzer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLECSVLOGANALYZER_H
#define UI_SIMPLECSVLOGANALYZER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/QCustomPlot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_SimpleCsvLogAnalyzer
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionZoom_Reset;
    QAction *actionSave_Plot_Image;
    QAction *actionData_Derivator;
    QAction *actionPlot_SelectedData;
    QAction *actionplot_SelectedDataVsSelectedData;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *minValueY;
    QFrame *line_5;
    QLabel *maxValueY;
    QFrame *line_6;
    QLabel *averageValueY;
    QFrame *line_7;
    QLabel *spanValueY;
    QHBoxLayout *horizontalLayout_4;
    QLabel *totalDataLength;
    QHBoxLayout *dataStatisticsLayout;
    QLabel *minValueX;
    QFrame *line_2;
    QLabel *maxValueX;
    QFrame *line_3;
    QLabel *averageValueX;
    QFrame *line_4;
    QLabel *spanValueX;
    QHBoxLayout *mainHorizontalLayout;
    QTabWidget *rightTabs;
    QWidget *plotTab;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *plot1;
    QVBoxLayout *verticalLayout_4;
    QWidget *dataTableViewTab;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QListWidget *dataListY;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QListWidget *dataListX;
    QFrame *line_11;
    QHBoxLayout *horizontalLayout;
    QToolButton *plotSelected;
    QToolButton *plotSelectedXY;
    QToolButton *DataDerivator;
    QWidget *quickPlotPresets;
    QGridLayout *gridLayout_2;
    QToolButton *predefinedPlot1;
    QToolButton *predefinedPlot2;
    QToolButton *predefinedPlot9;
    QToolButton *predefinedPlot5;
    QToolButton *predefinedPlot7;
    QToolButton *predefinedPlot6;
    QToolButton *predefinedPlot3;
    QToolButton *predefinedPlot4;
    QToolButton *predefinedPlot8;
    QToolButton *predefinedPlot10;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *SimpleCsvLogAnalyzer)
    {
        if (SimpleCsvLogAnalyzer->objectName().isEmpty())
            SimpleCsvLogAnalyzer->setObjectName(QString::fromUtf8("SimpleCsvLogAnalyzer"));
        SimpleCsvLogAnalyzer->resize(640, 721);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        SimpleCsvLogAnalyzer->setFont(font);
        actionOpen = new QAction(SimpleCsvLogAnalyzer);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        actionOpen->setFont(font1);
        actionExit = new QAction(SimpleCsvLogAnalyzer);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionZoom_Reset = new QAction(SimpleCsvLogAnalyzer);
        actionZoom_Reset->setObjectName(QString::fromUtf8("actionZoom_Reset"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/zoomreset.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Reset->setIcon(icon1);
        actionZoom_Reset->setFont(font1);
        actionSave_Plot_Image = new QAction(SimpleCsvLogAnalyzer);
        actionSave_Plot_Image->setObjectName(QString::fromUtf8("actionSave_Plot_Image"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Plot_Image->setIcon(icon2);
        actionSave_Plot_Image->setFont(font1);
        actionData_Derivator = new QAction(SimpleCsvLogAnalyzer);
        actionData_Derivator->setObjectName(QString::fromUtf8("actionData_Derivator"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/function.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionData_Derivator->setIcon(icon3);
        actionData_Derivator->setFont(font1);
        actionPlot_SelectedData = new QAction(SimpleCsvLogAnalyzer);
        actionPlot_SelectedData->setObjectName(QString::fromUtf8("actionPlot_SelectedData"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/images/ploty.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlot_SelectedData->setIcon(icon4);
        actionPlot_SelectedData->setFont(font1);
        actionplot_SelectedDataVsSelectedData = new QAction(SimpleCsvLogAnalyzer);
        actionplot_SelectedDataVsSelectedData->setObjectName(QString::fromUtf8("actionplot_SelectedDataVsSelectedData"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/images/plotxy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionplot_SelectedDataVsSelectedData->setIcon(icon5);
        actionplot_SelectedDataVsSelectedData->setFont(font1);
        actionZoom_In = new QAction(SimpleCsvLogAnalyzer);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/images/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon6);
        actionZoom_In->setFont(font1);
        actionZoom_Out = new QAction(SimpleCsvLogAnalyzer);
        actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/images/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Out->setIcon(icon7);
        actionZoom_Out->setFont(font1);
        centralwidget = new QWidget(SimpleCsvLogAnalyzer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, -1);
        minValueY = new QLabel(centralwidget);
        minValueY->setObjectName(QString::fromUtf8("minValueY"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(10);
        minValueY->setFont(font2);
        minValueY->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(minValueY);

        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(7);
        line_5->setFont(font3);
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_5);

        maxValueY = new QLabel(centralwidget);
        maxValueY->setObjectName(QString::fromUtf8("maxValueY"));
        maxValueY->setFont(font2);
        maxValueY->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(maxValueY);

        line_6 = new QFrame(centralwidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFont(font3);
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_6);

        averageValueY = new QLabel(centralwidget);
        averageValueY->setObjectName(QString::fromUtf8("averageValueY"));
        averageValueY->setFont(font2);
        averageValueY->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(averageValueY);

        line_7 = new QFrame(centralwidget);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFont(font3);
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_7);

        spanValueY = new QLabel(centralwidget);
        spanValueY->setObjectName(QString::fromUtf8("spanValueY"));
        spanValueY->setFont(font2);
        spanValueY->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(spanValueY);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        totalDataLength = new QLabel(centralwidget);
        totalDataLength->setObjectName(QString::fromUtf8("totalDataLength"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Arial"));
        font4.setPointSize(8);
        totalDataLength->setFont(font4);

        horizontalLayout_4->addWidget(totalDataLength);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        dataStatisticsLayout = new QHBoxLayout();
        dataStatisticsLayout->setSpacing(5);
        dataStatisticsLayout->setObjectName(QString::fromUtf8("dataStatisticsLayout"));
        dataStatisticsLayout->setContentsMargins(0, 0, 0, -1);
        minValueX = new QLabel(centralwidget);
        minValueX->setObjectName(QString::fromUtf8("minValueX"));
        minValueX->setFont(font2);
        minValueX->setAlignment(Qt::AlignCenter);

        dataStatisticsLayout->addWidget(minValueX);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFont(font3);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        dataStatisticsLayout->addWidget(line_2);

        maxValueX = new QLabel(centralwidget);
        maxValueX->setObjectName(QString::fromUtf8("maxValueX"));
        maxValueX->setFont(font2);
        maxValueX->setAlignment(Qt::AlignCenter);

        dataStatisticsLayout->addWidget(maxValueX);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFont(font3);
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        dataStatisticsLayout->addWidget(line_3);

        averageValueX = new QLabel(centralwidget);
        averageValueX->setObjectName(QString::fromUtf8("averageValueX"));
        averageValueX->setFont(font2);
        averageValueX->setAlignment(Qt::AlignCenter);

        dataStatisticsLayout->addWidget(averageValueX);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFont(font3);
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        dataStatisticsLayout->addWidget(line_4);

        spanValueX = new QLabel(centralwidget);
        spanValueX->setObjectName(QString::fromUtf8("spanValueX"));
        spanValueX->setFont(font2);
        spanValueX->setAlignment(Qt::AlignCenter);

        dataStatisticsLayout->addWidget(spanValueX);


        gridLayout->addLayout(dataStatisticsLayout, 1, 0, 1, 1);

        mainHorizontalLayout = new QHBoxLayout();
        mainHorizontalLayout->setObjectName(QString::fromUtf8("mainHorizontalLayout"));
        rightTabs = new QTabWidget(centralwidget);
        rightTabs->setObjectName(QString::fromUtf8("rightTabs"));
        rightTabs->setFont(font1);
        plotTab = new QWidget();
        plotTab->setObjectName(QString::fromUtf8("plotTab"));
        verticalLayout_3 = new QVBoxLayout(plotTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        plot1 = new QCustomPlot(plotTab);
        plot1->setObjectName(QString::fromUtf8("plot1"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plot1->sizePolicy().hasHeightForWidth());
        plot1->setSizePolicy(sizePolicy);
        QFont font5;
        font5.setFamily(QString::fromUtf8("Arial"));
        font5.setPointSize(7);
        font5.setBold(true);
        font5.setWeight(75);
        plot1->setFont(font5);
        verticalLayout_4 = new QVBoxLayout(plot1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));

        verticalLayout_3->addWidget(plot1);

        rightTabs->addTab(plotTab, QString());
        dataTableViewTab = new QWidget();
        dataTableViewTab->setObjectName(QString::fromUtf8("dataTableViewTab"));
        verticalLayout_6 = new QVBoxLayout(dataTableViewTab);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(dataTableViewTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMaximumSize(QSize(16777215, 16777215));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Arial"));
        font6.setPointSize(9);
        font6.setBold(true);
        font6.setWeight(75);
        label_2->setFont(font6);

        verticalLayout->addWidget(label_2);

        dataListY = new QListWidget(dataTableViewTab);
        dataListY->setObjectName(QString::fromUtf8("dataListY"));
        sizePolicy.setHeightForWidth(dataListY->sizePolicy().hasHeightForWidth());
        dataListY->setSizePolicy(sizePolicy);
        QFont font7;
        font7.setFamily(QString::fromUtf8("Arial"));
        font7.setPointSize(11);
        font7.setBold(true);
        font7.setWeight(75);
        dataListY->setFont(font7);
        dataListY->setContextMenuPolicy(Qt::CustomContextMenu);
        dataListY->setEditTriggers(QAbstractItemView::NoEditTriggers);
        dataListY->setProperty("showDropIndicator", QVariant(false));
        dataListY->setDragEnabled(false);
        dataListY->setDragDropOverwriteMode(false);
        dataListY->setDragDropMode(QAbstractItemView::NoDragDrop);
        dataListY->setDefaultDropAction(Qt::IgnoreAction);

        verticalLayout->addWidget(dataListY);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_3 = new QLabel(dataTableViewTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMaximumSize(QSize(16777215, 16777215));
        label_3->setFont(font6);

        verticalLayout_5->addWidget(label_3);

        dataListX = new QListWidget(dataTableViewTab);
        dataListX->setObjectName(QString::fromUtf8("dataListX"));
        sizePolicy.setHeightForWidth(dataListX->sizePolicy().hasHeightForWidth());
        dataListX->setSizePolicy(sizePolicy);
        dataListX->setFont(font7);
        dataListX->setEditTriggers(QAbstractItemView::DoubleClicked);
        dataListX->setProperty("showDropIndicator", QVariant(false));
        dataListX->setDragDropMode(QAbstractItemView::NoDragDrop);
        dataListX->setDefaultDropAction(Qt::IgnoreAction);
        dataListX->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_5->addWidget(dataListX);


        horizontalLayout_2->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_2);

        line_11 = new QFrame(dataTableViewTab);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setFont(font5);
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_11);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(16);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        plotSelected = new QToolButton(dataTableViewTab);
        plotSelected->setObjectName(QString::fromUtf8("plotSelected"));
        plotSelected->setMaximumSize(QSize(16777215, 16777215));
        plotSelected->setFont(font6);
        plotSelected->setIcon(icon4);
        plotSelected->setIconSize(QSize(48, 48));
        plotSelected->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(plotSelected);

        plotSelectedXY = new QToolButton(dataTableViewTab);
        plotSelectedXY->setObjectName(QString::fromUtf8("plotSelectedXY"));
        plotSelectedXY->setMaximumSize(QSize(16777215, 16777215));
        plotSelectedXY->setFont(font6);
        plotSelectedXY->setIcon(icon5);
        plotSelectedXY->setIconSize(QSize(48, 48));
        plotSelectedXY->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(plotSelectedXY);

        DataDerivator = new QToolButton(dataTableViewTab);
        DataDerivator->setObjectName(QString::fromUtf8("DataDerivator"));
        DataDerivator->setMaximumSize(QSize(16777215, 16777215));
        DataDerivator->setFont(font6);
        DataDerivator->setIcon(icon3);
        DataDerivator->setIconSize(QSize(48, 48));
        DataDerivator->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout->addWidget(DataDerivator);


        verticalLayout_6->addLayout(horizontalLayout);

        rightTabs->addTab(dataTableViewTab, QString());
        quickPlotPresets = new QWidget();
        quickPlotPresets->setObjectName(QString::fromUtf8("quickPlotPresets"));
        quickPlotPresets->setLayoutDirection(Qt::LeftToRight);
        gridLayout_2 = new QGridLayout(quickPlotPresets);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        predefinedPlot1 = new QToolButton(quickPlotPresets);
        predefinedPlot1->setObjectName(QString::fromUtf8("predefinedPlot1"));
        sizePolicy.setHeightForWidth(predefinedPlot1->sizePolicy().hasHeightForWidth());
        predefinedPlot1->setSizePolicy(sizePolicy);
        QFont font8;
        font8.setPointSize(11);
        predefinedPlot1->setFont(font8);
        predefinedPlot1->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot1->setAutoFillBackground(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/images/line-graph.png"), QSize(), QIcon::Normal, QIcon::Off);
        predefinedPlot1->setIcon(icon8);
        predefinedPlot1->setIconSize(QSize(64, 64));
        predefinedPlot1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot1->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot1, 0, 0, 1, 1);

        predefinedPlot2 = new QToolButton(quickPlotPresets);
        predefinedPlot2->setObjectName(QString::fromUtf8("predefinedPlot2"));
        sizePolicy.setHeightForWidth(predefinedPlot2->sizePolicy().hasHeightForWidth());
        predefinedPlot2->setSizePolicy(sizePolicy);
        predefinedPlot2->setFont(font8);
        predefinedPlot2->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot2->setAutoFillBackground(false);
        predefinedPlot2->setIcon(icon8);
        predefinedPlot2->setIconSize(QSize(64, 64));
        predefinedPlot2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot2->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot2, 0, 1, 1, 1);

        predefinedPlot9 = new QToolButton(quickPlotPresets);
        predefinedPlot9->setObjectName(QString::fromUtf8("predefinedPlot9"));
        sizePolicy.setHeightForWidth(predefinedPlot9->sizePolicy().hasHeightForWidth());
        predefinedPlot9->setSizePolicy(sizePolicy);
        predefinedPlot9->setFont(font8);
        predefinedPlot9->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot9->setAutoFillBackground(false);
        predefinedPlot9->setIcon(icon8);
        predefinedPlot9->setIconSize(QSize(64, 64));
        predefinedPlot9->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot9->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot9, 1, 0, 1, 1);

        predefinedPlot5 = new QToolButton(quickPlotPresets);
        predefinedPlot5->setObjectName(QString::fromUtf8("predefinedPlot5"));
        sizePolicy.setHeightForWidth(predefinedPlot5->sizePolicy().hasHeightForWidth());
        predefinedPlot5->setSizePolicy(sizePolicy);
        predefinedPlot5->setFont(font8);
        predefinedPlot5->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot5->setAutoFillBackground(false);
        predefinedPlot5->setIcon(icon8);
        predefinedPlot5->setIconSize(QSize(64, 64));
        predefinedPlot5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot5->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot5, 4, 0, 1, 1);

        predefinedPlot7 = new QToolButton(quickPlotPresets);
        predefinedPlot7->setObjectName(QString::fromUtf8("predefinedPlot7"));
        sizePolicy.setHeightForWidth(predefinedPlot7->sizePolicy().hasHeightForWidth());
        predefinedPlot7->setSizePolicy(sizePolicy);
        predefinedPlot7->setFont(font8);
        predefinedPlot7->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot7->setAutoFillBackground(false);
        predefinedPlot7->setIcon(icon8);
        predefinedPlot7->setIconSize(QSize(64, 64));
        predefinedPlot7->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot7->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot7, 4, 1, 1, 1);

        predefinedPlot6 = new QToolButton(quickPlotPresets);
        predefinedPlot6->setObjectName(QString::fromUtf8("predefinedPlot6"));
        sizePolicy.setHeightForWidth(predefinedPlot6->sizePolicy().hasHeightForWidth());
        predefinedPlot6->setSizePolicy(sizePolicy);
        predefinedPlot6->setFont(font8);
        predefinedPlot6->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot6->setAutoFillBackground(false);
        predefinedPlot6->setIcon(icon8);
        predefinedPlot6->setIconSize(QSize(64, 64));
        predefinedPlot6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot6->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot6, 6, 0, 1, 1);

        predefinedPlot3 = new QToolButton(quickPlotPresets);
        predefinedPlot3->setObjectName(QString::fromUtf8("predefinedPlot3"));
        sizePolicy.setHeightForWidth(predefinedPlot3->sizePolicy().hasHeightForWidth());
        predefinedPlot3->setSizePolicy(sizePolicy);
        predefinedPlot3->setFont(font8);
        predefinedPlot3->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot3->setAutoFillBackground(false);
        predefinedPlot3->setIcon(icon8);
        predefinedPlot3->setIconSize(QSize(64, 64));
        predefinedPlot3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot3->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot3, 1, 1, 1, 1);

        predefinedPlot4 = new QToolButton(quickPlotPresets);
        predefinedPlot4->setObjectName(QString::fromUtf8("predefinedPlot4"));
        sizePolicy.setHeightForWidth(predefinedPlot4->sizePolicy().hasHeightForWidth());
        predefinedPlot4->setSizePolicy(sizePolicy);
        predefinedPlot4->setFont(font8);
        predefinedPlot4->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot4->setAutoFillBackground(false);
        predefinedPlot4->setIcon(icon8);
        predefinedPlot4->setIconSize(QSize(64, 64));
        predefinedPlot4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot4->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot4, 2, 0, 1, 1);

        predefinedPlot8 = new QToolButton(quickPlotPresets);
        predefinedPlot8->setObjectName(QString::fromUtf8("predefinedPlot8"));
        sizePolicy.setHeightForWidth(predefinedPlot8->sizePolicy().hasHeightForWidth());
        predefinedPlot8->setSizePolicy(sizePolicy);
        predefinedPlot8->setFont(font8);
        predefinedPlot8->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot8->setAutoFillBackground(false);
        predefinedPlot8->setIcon(icon8);
        predefinedPlot8->setIconSize(QSize(64, 64));
        predefinedPlot8->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot8->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot8, 2, 1, 1, 1);

        predefinedPlot10 = new QToolButton(quickPlotPresets);
        predefinedPlot10->setObjectName(QString::fromUtf8("predefinedPlot10"));
        sizePolicy.setHeightForWidth(predefinedPlot10->sizePolicy().hasHeightForWidth());
        predefinedPlot10->setSizePolicy(sizePolicy);
        predefinedPlot10->setFont(font8);
        predefinedPlot10->setLayoutDirection(Qt::LeftToRight);
        predefinedPlot10->setAutoFillBackground(false);
        predefinedPlot10->setIcon(icon8);
        predefinedPlot10->setIconSize(QSize(64, 64));
        predefinedPlot10->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        predefinedPlot10->setAutoRaise(false);

        gridLayout_2->addWidget(predefinedPlot10, 6, 1, 1, 1);

        rightTabs->addTab(quickPlotPresets, QString());

        mainHorizontalLayout->addWidget(rightTabs);


        gridLayout->addLayout(mainHorizontalLayout, 0, 0, 1, 1);

        SimpleCsvLogAnalyzer->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SimpleCsvLogAnalyzer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setFont(font6);
        SimpleCsvLogAnalyzer->setStatusBar(statusbar);
        toolBar = new QToolBar(SimpleCsvLogAnalyzer);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setFont(font3);
        toolBar->setIconSize(QSize(50, 50));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        SimpleCsvLogAnalyzer->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionOpen);
        toolBar->addAction(actionZoom_In);
        toolBar->addAction(actionZoom_Out);
        toolBar->addAction(actionZoom_Reset);
        toolBar->addAction(actionSave_Plot_Image);
        toolBar->addAction(actionData_Derivator);
        toolBar->addAction(actionPlot_SelectedData);
        toolBar->addAction(actionplot_SelectedDataVsSelectedData);

        retranslateUi(SimpleCsvLogAnalyzer);

        rightTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SimpleCsvLogAnalyzer);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleCsvLogAnalyzer)
    {
        SimpleCsvLogAnalyzer->setWindowTitle(QApplication::translate("SimpleCsvLogAnalyzer", "SimpleCsvLogAnalyzer", nullptr));
        actionOpen->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Open File", nullptr));
        actionExit->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Exit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("SimpleCsvLogAnalyzer", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionZoom_Reset->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Zoom Reset", nullptr));
#ifndef QT_NO_SHORTCUT
        actionZoom_Reset->setShortcut(QApplication::translate("SimpleCsvLogAnalyzer", "0", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_Plot_Image->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Save Plot", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_Plot_Image->setShortcut(QApplication::translate("SimpleCsvLogAnalyzer", "S", nullptr));
#endif // QT_NO_SHORTCUT
        actionData_Derivator->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Data Derivator", nullptr));
        actionPlot_SelectedData->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Plot Y", nullptr));
        actionplot_SelectedDataVsSelectedData->setText(QApplication::translate("SimpleCsvLogAnalyzer", "plot Y-X", nullptr));
        actionZoom_In->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Zoom In", nullptr));
        actionZoom_Out->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Zoom Out", nullptr));
        minValueY->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Min Y: nan", nullptr));
        maxValueY->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Max Y: nan", nullptr));
        averageValueY->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Average Y: nan", nullptr));
        spanValueY->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Span Y: nan", nullptr));
        totalDataLength->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Data Length: nan", nullptr));
        minValueX->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Min X: nan", nullptr));
        maxValueX->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Max X: nan", nullptr));
        averageValueX->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Average X: nan", nullptr));
        spanValueX->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Span X: nan", nullptr));
        rightTabs->setTabText(rightTabs->indexOf(plotTab), QApplication::translate("SimpleCsvLogAnalyzer", "Plot", nullptr));
        label_2->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Y Axis Data List", nullptr));
        label_3->setText(QApplication::translate("SimpleCsvLogAnalyzer", "X Axis Data List", nullptr));
        plotSelected->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Plot Selected Data vs Index", nullptr));
        plotSelectedXY->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Plot Selected Y-X Data", nullptr));
        DataDerivator->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Data Derivator", nullptr));
        rightTabs->setTabText(rightTabs->indexOf(dataTableViewTab), QApplication::translate("SimpleCsvLogAnalyzer", "Data Labels", nullptr));
        predefinedPlot1->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Speed (OBD) vs Time", nullptr));
        predefinedPlot2->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Speed (GPS) vs Time", nullptr));
        predefinedPlot9->setText(QApplication::translate("SimpleCsvLogAnalyzer", "RPM vs Time", nullptr));
        predefinedPlot5->setText(QApplication::translate("SimpleCsvLogAnalyzer", "LTFT1 vs Time", nullptr));
        predefinedPlot7->setText(QApplication::translate("SimpleCsvLogAnalyzer", "STFT1 vs Time", nullptr));
        predefinedPlot6->setText(QApplication::translate("SimpleCsvLogAnalyzer", "LTFT1+STFT1 vs RPM", nullptr));
        predefinedPlot3->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Altitude vs Time", nullptr));
        predefinedPlot4->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Avg. Consumption vs Time", nullptr));
        predefinedPlot8->setText(QApplication::translate("SimpleCsvLogAnalyzer", "Speed (OBD) / RPM vs Time", nullptr));
        predefinedPlot10->setText(QApplication::translate("SimpleCsvLogAnalyzer", "LTFT1+STFT1 vs Time", nullptr));
        rightTabs->setTabText(rightTabs->indexOf(quickPlotPresets), QApplication::translate("SimpleCsvLogAnalyzer", "Quick Plots", nullptr));
        toolBar->setWindowTitle(QApplication::translate("SimpleCsvLogAnalyzer", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimpleCsvLogAnalyzer: public Ui_SimpleCsvLogAnalyzer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLECSVLOGANALYZER_H

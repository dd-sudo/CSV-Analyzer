#include "SimpleCsvLogAnalyzer.h"
#include "ui_SimpleCsvLogAnalyzer.h"

#include <QThread>
//handle log files that have labels between data lines
SimpleCsvLogAnalyzer::SimpleCsvLogAnalyzer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimpleCsvLogAnalyzer)
{
    ui->setupUi(this);
    qApp->processEvents();
    getAndroidPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    getAndroidPermission("android.permission.READ_EXTERNAL_STORAGE");
    // setup some shortcuts
    moveRight = new QShortcut(this);
    moveRight->setKey(Qt::Key_Right);
    connect(moveRight,SIGNAL(activated()),this,SLOT(moveRigthPressed()));

    QPixmap pixmap(":/images/images/timer-opaque.png");
    loadingSplash = new QSplashScreen(pixmap,Qt::SplashScreen);

    // init dataTableView custom context menu
    //    tableViewContextMenu = new QMenu();
    //    tableViewContextMenu->addAction("Plot",this,SLOT(plotThis_forTable()));
    //    tableViewContextMenu->addAction("Statistics",this,SLOT(statisticsForThis_forTable()));
    //    tableViewContextMenu->addAction("Hide Selected Columns",this,SLOT(hideTableColumns_forTable()));
    //    tableViewContextMenu->addAction("Show Selected Columns Only",this,SLOT(showTableColumns_forTable()));
    //    tableViewContextMenu->addAction("Show All Columns",this,SLOT(restoreTableColumns_forTable()));

    // init dataTableView custom context menu
    labelListContextMenu = new QMenu();
    labelListContextMenu->addAction("Plot vs Record Number",this,SLOT(plotThis_forList()));
    labelListContextMenu->addAction("Plot vs Another Data Label",this,SLOT(plotThisVsAnotherDataLabel_forList()));
    labelListContextMenu->addAction("Statistics",this,SLOT(statisticsForThis_forList()));

    //initDataTable();

    initPlot();
    ui->totalDataLength->hide();

#ifdef Q_OS_ANDROID
    this->showMaximized();
#endif
    qApp->processEvents();
    //ui->plot1->setMaximumSize(ui->plot1->size());

}

SimpleCsvLogAnalyzer::~SimpleCsvLogAnalyzer()
{
    delete ui;
}

void SimpleCsvLogAnalyzer::on_actionExit_triggered()
{
    cleanUpAndExit();
    exit(0);
}

void SimpleCsvLogAnalyzer::cleanUpAndExit()
{
    // TDB
}

void SimpleCsvLogAnalyzer::initPlot(){

    // Clear graph etc.
    //ui->plot1->setOpenGl(true);
    disconnect(ui->plot1, &QCustomPlot::mouseMove, this, &SimpleCsvLogAnalyzer::tracerEvent);
    ui->plot1->clearGraphs();
    QFont f = ui->plot1->font();
    f.setPointSizeF(8);
    ui->plot1->xAxis->setTickLabelFont(f);
    ui->plot1->yAxis->setTickLabelFont(f);
    ui->plot1->xAxis->setLabelFont(f);
    ui->plot1->yAxis->setLabelFont(f);
    //

    // Create value and cursor plot
    valuePlot = ui->plot1->addGraph();
    //cursorPlot = ui->plot1->addGraph();



    // Allow draggingplot in X axis only (horizontal)
    ui->plot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot1->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->plot1->axisRect()->setRangeZoom(Qt::Horizontal);

    // setup tracer
    verticalLine = new QCPCurve(ui->plot1->xAxis, ui->plot1->yAxis);
    QVector<double> x(2) , y(2);
    x[0] = 0;
    y[0] = 0;
    x[1] = 0;
    y[1] = 0;

    verticalLine->setName("Vertical");
    verticalLine->setData(x, y);
    tracer = new QCPItemTracer(ui->plot1);

    tracer->setStyle(QCPItemTracer::tsCrosshair);
    tracer->setPen(QPen(Qt::darkGray));

#ifdef Q_OS_ANDROID
    connect(ui->plot1, &QCustomPlot::mouseRelease, this, &SimpleCsvLogAnalyzer::tracerEvent);
#else
    connect(ui->plot1, &QCustomPlot::mouseMove, this, &SimpleCsvLogAnalyzer::tracerEvent);
#endif
}

//void SimpleCsvLogAnalyzer::initDataTable()
//{
//    // Auto adjust horizontal header labels
//    ui->dataTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//}

void SimpleCsvLogAnalyzer::clearPlotNDisableTracer(){
    xVals.clear();
    yVals.clear();
    valuePlot->setData(xVals,yVals);
    tracer->setGraph(nullptr);
    ui->plot1->replot();
}

void SimpleCsvLogAnalyzer::setupTracer()
{
    tracer->setGraph(valuePlot);
}

void SimpleCsvLogAnalyzer::zoomReset(){
    // Rescales X axis using default method (min and max of x values)
    // rescales Y axis using min and max of Y axis values, with a margin of 1/10th of the span
    // to provide better visibilty for peaks and valleys in plot curve
    valuePlot->rescaleKeyAxis();
    double span = stats.y.span;
    if(span==0){
        span = 10;
    }
    ui->plot1->yAxis->setRange(stats.y.min-0.1*span,stats.y.max+0.1*span);
    ui->plot1->replot();
    qApp->processEvents();

#ifdef Q_OS_ANDROID
    this->showMaximized();
#endif
    //    this->showMaximized();
}

QList<double> SimpleCsvLogAnalyzer::calculateSlopeOfCurve(double keyValue){
    QList<double> ret;
    ret.append(NAN);
    ret.append(NAN);
    int valueIndex = xVals.indexOf(keyValue);
    if( ((valueIndex+1) < yVals.length()) && ((valueIndex)>0) ){
        ret[0] = (yVals[valueIndex] - yVals[valueIndex-1])/(xVals[valueIndex]-xVals[valueIndex-1]); // left slope
        ret[1] = (yVals[valueIndex+1] - yVals[valueIndex])/(xVals[valueIndex+1]-xVals[valueIndex]); // right slope
    }
    return ret;
}

statistics SimpleCsvLogAnalyzer::calculateStatisticalData(QVector<double> x, QVector<double> y, bool showReportMessage){
    statistics ret;
    ret.x.min = std::numeric_limits<double>::max();
    ret.x.max = std::numeric_limits<double>::min();
    ret.x.span = 0;
    ret.x.average = 0;
    int averageArrayLen = x.length();
    if(x.length()>0){
        double accu = 0;
        double tmp;
        for(int i=0; i<x.length(); ++i){
            tmp = x[i];
            if(!qIsNaN(tmp)){
                accu += tmp;
            } else {
                --averageArrayLen;
            }
            if(tmp<ret.x.min){
                ret.x.min = tmp;
            }
            if(tmp>ret.x.max){
                ret.x.max = tmp;
            }
        }
        ret.x.average = accu/averageArrayLen;
        ret.x.span = ret.x.max - ret.x.min;
        if((ret.x.min == std::numeric_limits<double>::max()) | (ret.x.max == std::numeric_limits<double>::min())){
            ret.x.min = NAN;
            ret.x.max = NAN;
            ret.x.span = NAN;
            ret.x.average = NAN;
        }
    } else {
        qDebug() << "No data in array!";
        ret.x.min = NAN;
        ret.x.max = NAN;
        ret.x.span = NAN;
        ret.x.average = NAN;
    }
    ret.x.length = x.length();


    ret.y.min = std::numeric_limits<double>::max();
    ret.y.max = std::numeric_limits<double>::min();
    ret.y.span = 0;
    ret.y.average = 0;
    averageArrayLen = y.length();
    if(y.length()>0){
        double accu = 0;
        double tmp;
        for(int i=0; i<y.length(); ++i){
            tmp = y[i];
            if(!qIsNaN(tmp)){
                accu += tmp;
            } else {
                --averageArrayLen;
            }
            if(tmp<ret.y.min){
                ret.y.min = tmp;
            }
            if(tmp>ret.y.max){
                ret.y.max = tmp;
            }
        }
        ret.y.average = accu/averageArrayLen;
        ret.y.span = ret.y.max - ret.y.min;
        if((ret.y.min == std::numeric_limits<double>::max()) | (ret.y.max == std::numeric_limits<double>::min())){
            ret.y.min = NAN;
            ret.y.max = NAN;
            ret.y.span = NAN;
            ret.y.average = NAN;
        }
    } else {
        qDebug() << "No data in array!";
        ret.y.min = NAN;
        ret.y.max = NAN;
        ret.y.span = NAN;
        ret.y.average = NAN;
    }
    ret.y.length = y.length();
    if(showReportMessage){
        QString s = QString("Statistics for selected data\n"
                            "Min:%1\n"
                            "Max:%2\n"
                            "Average:%3\n"
                            "Span:%4\n"
                            "Length:%5")
                .arg(ret.y.min)
                .arg(ret.y.max)
                .arg(ret.y.average)
                .arg(ret.y.span)
                .arg(ret.y.length);
        QMessageBox msg;
        msg.setText(s);
        msg.exec();
    }
    return ret;
}

void SimpleCsvLogAnalyzer::populateStatisticsLabels(){
    // X Axis
    ui->minValueX->setText("Min X: " + QString::number(stats.x.min,'f',2));
    ui->maxValueX->setText("Max X: " + QString::number(stats.x.max,'f',2));
    ui->spanValueX->setText("Span X: " + QString::number(stats.x.span,'f',2));
    ui->averageValueX->setText("Average X: " + QString::number(stats.x.average,'f',2));
    // Y Axis
    ui->minValueY->setText("Min Y: " + QString::number(stats.y.min,'f',2));
    ui->maxValueY->setText("Max Y: " + QString::number(stats.y.max,'f',2));
    ui->spanValueY->setText("Span Y: " + QString::number(stats.y.span,'f',2));
    ui->averageValueY->setText("Average Y: " + QString::number(stats.y.average,'f',2));
    //Data length
    ui->totalDataLength->setText(QString("Data Length: %1").arg(stats.y.length));

}

void SimpleCsvLogAnalyzer::clearStatisticsLabels()
{
    // X Axis
    ui->minValueX->setText("Min X: nan");
    ui->maxValueX->setText("Max X: nan");
    ui->spanValueX->setText("Span X: nan");
    ui->averageValueX->setText("Average X: nan");
    // Y Axis
    ui->minValueY->setText("Min Y: nan");
    ui->maxValueY->setText("Max Y: nan");
    ui->spanValueY->setText("Span Y: nan");
    ui->averageValueY->setText("Average Y: nan");
    //Data length
    ui->totalDataLength->setText(QString("Data Length: N/A"));
}

void SimpleCsvLogAnalyzer::startBusy()
{
    loadingSplash->move(this->x()+this->width()/2,this->y()+this->height()/2);
    loadingSplash->show();
    qApp->processEvents();
}

void SimpleCsvLogAnalyzer::stopBusy()
{
    qApp->processEvents();
    loadingSplash->close();
}

QString SimpleCsvLogAnalyzer::createDerivedDataLabel(QStringList formula)
{
    QString derivedDataLabel;
    QVector<double> dd,tmp;
    if(formula.isEmpty()){
        ui->statusbar->showMessage("Empty formula for derived data!");
        showMessage("Empty formula for derived data!");
        return derivedDataLabel;
    }
    qDebug() << "Formula:" << formula;
    if(mathOperatorsList.contains(formula[0])){
        ui->statusbar->showMessage("Illegal formula for derived data!");
        showMessage("Illegal formula for derived data!");
        return derivedDataLabel;
    }
    QStringList labelList;
    for(int i=0;i<ui->dataListY->count();++i){
        labelList << ui->dataListY->item(i)->text();
    }
    // Derive data using formula
    for (int i=0;i<formula.length();++i) {
        if(mathOperatorsList.contains(formula[i])){
            qDebug() << "We got math op:" << formula[i];
            switch (mathOperatorsList.indexOf(formula[i])) {
            case 0: // +
                if(++i<formula.length()){
                    tmp = csvFile.getDataByName(formula[i]);
                }
                if(tmp.length() != dd.length()){
                    showMessage("Derived data length error!");
                    return derivedDataLabel;
                }
                // sum dd and tmp
                for(int i=0;i<dd.length();++i){
                    dd[i] += tmp[i];
                }
                break;
            case 1: // -
                if(++i<formula.length()){
                    tmp = csvFile.getDataByName(formula[i]);
                }
                if(tmp.length() != dd.length()){
                    showMessage("Derived data length error!");
                    return derivedDataLabel;
                }
                // subtract dd and tmp
                for(int i=0;i<dd.length();++i){
                    dd[i] -= tmp[i];
                }
                break;
            case 2: // *
                if(++i<formula.length()){
                    tmp = csvFile.getDataByName(formula[i]);
                }
                if(tmp.length() != dd.length()){
                    showMessage("Derived data length error!");
                    return derivedDataLabel;
                }
                // multiply dd and tmp
                for(int i=0;i<dd.length();++i){
                    dd[i] *= tmp[i];
                }
                break;
            case 3: // /
                if(++i<formula.length()){
                    tmp = csvFile.getDataByName(formula[i]);
                }
                if(tmp.length() != dd.length()){
                    showMessage("Derived data length error!");
                    return derivedDataLabel;
                }
                // divide dd and tmp
                for(int i=0;i<dd.length();++i){
                    dd[i] /= tmp[i];
                    if((dd[i] == std::numeric_limits<double>::infinity())||(dd[i] == -1*std::numeric_limits<float>::infinity())){
                        dd[i] = NAN;
                    }
                }
                break;
            }

        } else if (labelList.contains(formula[i])){
            qDebug() << "We got value label:" << formula[i];
            tmp = csvFile.getDataByName(formula[i]);
            if(i==0){
                dd.append(tmp);
            }
        }
    }

    derivedDataLabel += mathStringStart;
    for (int i=0;i<formula.length();++i) {
        derivedDataLabel += formula[i];
    }
    derivedDataLabel += mathStringEnd;
    ui->dataListY->addItem(derivedDataLabel);
    ui->dataListX->addItem(derivedDataLabel);
    qDebug() << "Derived data  name:" << derivedDataLabel << "data length:" << dd.length();
    derivedDataVector.append(dd);
    derivedDataVectorLabels.append(derivedDataLabel);
    return derivedDataLabel;
}


void SimpleCsvLogAnalyzer::on_actionOpen_triggered()
{
    QString filePath;
#ifdef Q_OS_ANDROID
    CustomFileDialog *dlg = new CustomFileDialog(this);
    dlg->showMaximized();
    int ret = dlg->exec();
    if(ret){
        filePath = dlg->filePath;
    } else {
        filePath.clear();
    }
    dlg->deleteLater();
#else
    filePath = QFileDialog::getOpenFileName(this,"Select a file...","","*.csv");
#endif


    //QString filePath = QFileDialog::getOpenFileName(this,"Select a file...","","*.csv");
    qDebug() << "filePath:" << filePath;
    if(filePath.isEmpty()){
        qDebug() << "No file specified!";
        showMessage("No file specified!");
        return;
    }
    ui->rightTabs->setCurrentIndex(0);
    startBusy();

    derivedDataVector.clear();
    derivedDataVectorLabels.clear();

    ui->dataListX->clear();
    ui->dataListY->clear();

    clearPlotNDisableTracer();
    clearStatisticsLabels();
    qApp->processEvents();

    csvFile.setFilePath(filePath);
    m_labels = csvFile.getCsvFileLabels();
    m_sampleValues = csvFile.getSampleValuesForLabels();
    ui->dataListY->addItems(m_labels);
    ui->dataListX->addItems(m_labels);
    //    csvFile.file2TableWidget(ui->dataTableWidget);

    // Get real time data from "Device Time" label than convert it to msecFromEpoch
    QStringList timeStr = csvFile.getRawDataByName("Device Time");
    if(timeStr.isEmpty()){
        showMessage("Device time values could not be read from log file!\n"
                    "All Y plots will be plotted with respect to file record(sample) number!\n"
                    "If labels are not uniformly sampled in time, resulting plots cannot be used for qualitative analysis!");
    } else {
        QVector<double> timeMSecSinceEpoch;
        QVector<double> timeSecsSinceStart;
        qint64 startOfLog = 0;
        QDateTime tmp;
        bool started = false;
        for (int i=0;i<timeStr.length();++i) {
            tmp = defaultEngLocale.toDateTime(timeStr[i],torqueDeviceTimeFormat);
            //tmp = QDateTime::fromString(timeStr[i],torqueDeviceTimeFormat);
            if(tmp.isValid()){
                if(!started){
                    startOfLog = tmp.toMSecsSinceEpoch();
                    started = true;
                }
                timeMSecSinceEpoch.append(tmp.toMSecsSinceEpoch());
                timeSecsSinceStart.append( (tmp.toMSecsSinceEpoch()-startOfLog)/1000.0 );
            }
        }
        QString derivedDataLabel;
        // Add timeMSecSinceEpoch for future use
        if(!timeMSecSinceEpoch.isEmpty()){
            derivedDataLabel += mathStringStart;
            derivedDataLabel += "mSecSinceEpoch";
            derivedDataLabel += mathStringEnd;
            ui->dataListY->addItem(derivedDataLabel);
            ui->dataListX->addItem(derivedDataLabel);
            qDebug() << "Derived data  name:" << derivedDataLabel << "data length:" << timeMSecSinceEpoch.length();
            derivedDataVector.append(timeMSecSinceEpoch);
            derivedDataVectorLabels.append(derivedDataLabel);
        } else {
            showMessage("mSecSinceEpoch derivation error!\n"
                        "Check log file and make sure \"Device Time\ has a format like" + torqueDeviceTimeFormat);
        }

        // Add time: seconds since log file started
        if(!timeSecsSinceStart.isEmpty()){
            derivedDataLabel.clear();
            derivedDataLabel += mathStringStart;
            derivedDataLabel += "Time Since Start (s)";
            derivedDataLabel += mathStringEnd;
            ui->dataListY->addItem(derivedDataLabel);
            ui->dataListX->addItem(derivedDataLabel);
            qDebug() << "Derived data  name:" << derivedDataLabel << "data length:" << timeSecsSinceStart.length();
            derivedDataVector.append(timeSecsSinceStart);
            derivedDataVectorLabels.append(derivedDataLabel);
        } else {
            showMessage("Time Since Start (s) derivation error!\n"
                        "Check log file and make sure \"Device Time\ has a format like" + torqueDeviceTimeFormat);
        }
    }
    stopBusy();

}

void SimpleCsvLogAnalyzer::plotGraph(QString xName, QString yName)
{
    if(xName.isEmpty() && yName.isEmpty()){
        qDebug() << "Select label(s) before plotting...";
        return;
    }
    startBusy();
    clearPlotNDisableTracer();

    if(xName.isEmpty()){
        // Plot Y labels vs time, if no time info than plot versus data point number
        if(yName.startsWith(mathStringStart)){
            qDebug() << "We got derived data here, name:" << yName;
            qDebug() << "Available derived data labels:" << derivedDataVectorLabels;
            qDebug() << yName << "index in derivedDataVectorLabels" << derivedDataVectorLabels.indexOf(yName);
            // Get derived data from buffer
            if(derivedDataVectorLabels.indexOf(yName)>=0){
                qDebug() << "We have label for " << yName;
                if(derivedDataVector.length()>derivedDataVectorLabels.indexOf(yName)){
                    qDebug() << "We have data for " << yName;
                    yVals = derivedDataVector[derivedDataVectorLabels.indexOf(yName)];
                }
            }
        } else {
            yVals = csvFile.getDataByName(yName);
        }
        if(yVals.isEmpty()){
            ui->statusbar->showMessage("No Y axis data to plot!");
            showMessage("No Y axis data to plot!");
            return;
        }
        plotType = PLOT_Y_VS_POINT_NUM;
        // Get X Label values
        xName = QString("%1%2%3").arg(mathStringStart)
                .arg("Time Since Start (s)")
                .arg(mathStringEnd);
        if(derivedDataVectorLabels.contains(xName)){
            qDebug() << "We have real time info";
            qDebug() << xName << "index in derivedDataVectorLabels" << derivedDataVectorLabels.indexOf(xName);
            // Get derived data from buffer
            if(derivedDataVectorLabels.indexOf(xName)>=0){
                qDebug() << "We have label for " << xName;
                if(derivedDataVector.length()>derivedDataVectorLabels.indexOf(xName)){
                    qDebug() << "We have data for " << xName;
                    xVals = derivedDataVector[derivedDataVectorLabels.indexOf(xName)];
                    xName = "Time Since Start (s)";
                }
            }
        }

        if(xVals.isEmpty()){
            xName = "Sample Number";
            xVals.resize(yVals.length());
            for(int i=0;i<xVals.length();++i){
                xVals[i] = i;
            }
        }

        ui->plot1->xAxis->setLabel(xName);
        ui->plot1->yAxis->setLabel(yName);
        // configure plot style
        valuePlot->setLineStyle(QCPGraph::lsLine);
        valuePlot->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 1));
        valuePlot->setData(xVals,yVals);
        QPen pen = valuePlot->pen();
        pen.setColor(Qt::blue);
        valuePlot->setPen(pen);
    } else {
        // Plot Y labels vs Selected X label
        // Get Y Label values
        if(yName.startsWith(mathStringStart)){
            qDebug() << "We got derived data here, name:" << yName;
            qDebug() << "Available derived data labels:" << derivedDataVectorLabels;
            qDebug() << yName << "index in derivedDataVectorLabels" << derivedDataVectorLabels.indexOf(yName);
            // Get derived data from buffer
            if(derivedDataVectorLabels.indexOf(yName)>=0){
                qDebug() << "We have label for " << yName;
                if(derivedDataVector.length()>derivedDataVectorLabels.indexOf(yName)){
                    qDebug() << "We have data for " << yName;
                    yVals = derivedDataVector[derivedDataVectorLabels.indexOf(yName)];
                }
            }
        } else {
            yVals = csvFile.getDataByName(yName);
        }
        if(yVals.isEmpty()){
            ui->statusbar->showMessage("No Y axis data to plot!");
            showMessage("No Y axis data to plot!");
            return;
        }
        // Get X Label values
        if(xName.startsWith(mathStringStart)){
            qDebug() << "We got derived data here, name:" << xName;
            qDebug() << "Available derived data labels:" << derivedDataVectorLabels;
            qDebug() << xName << "index in derivedDataVectorLabels" << derivedDataVectorLabels.indexOf(xName);
            // Get derived data from buffer
            if(derivedDataVectorLabels.indexOf(xName)>=0){
                qDebug() << "We have label for " << xName;
                if(derivedDataVector.length()>derivedDataVectorLabels.indexOf(xName)){
                    qDebug() << "We have data for " << xName;
                    xVals = derivedDataVector[derivedDataVectorLabels.indexOf(xName)];
                }
            }
        } else {
            xVals = csvFile.getDataByName(xName);
        }
        if(xVals.isEmpty()){
            ui->statusbar->showMessage("No X axis data to plot!");
            showMessage("No X axis data to plot!");
            return;
        }
        plotType = PLOT_Y_VS_X;
        ui->plot1->xAxis->setLabel(xName);
        ui->plot1->yAxis->setLabel(yName);
        // configure plot style
        valuePlot->setLineStyle(QCPGraph::lsLine);
        valuePlot->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot, 3));
        valuePlot->setData(xVals,yVals);
        QPen pen = valuePlot->pen();
        pen.setColor(Qt::red);
        valuePlot->setPen(pen);
    }

    qDebug() << xVals.length() << yVals.length();
    valuePlot->setData(xVals,yVals);

    setupTracer();
    stats = calculateStatisticalData(xVals,yVals,false);
    populateStatisticsLabels();
    zoomReset();
    ui->rightTabs->setCurrentIndex(0);
    stopBusy();

}

void SimpleCsvLogAnalyzer::on_plotSelected_clicked()
{
    // Plots values of selected data name versus recorda/data point
    if(ui->dataListY->selectedItems().isEmpty()){
        ui->statusbar->showMessage("Select a proper data for y axis!");
        showMessage("Select a proper data for y axis!");
        return;
    }

    QString name = ui->dataListY->selectedItems().first()->text();

    plotGraph("",name);

}

void SimpleCsvLogAnalyzer::on_plotSelectedXY_clicked()
{
    // Plots values of selected data name versus selected another data field
    if(ui->dataListY->selectedItems().isEmpty() | ui->dataListX->selectedItems().isEmpty()){
        ui->statusbar->showMessage("Select a proper data for both x and y axis!");
        showMessage("Select a proper data for both x and y axis!");
        return;
    }

    QString nameY = ui->dataListY->selectedItems().first()->text();
    QString nameX = ui->dataListX->selectedItems().first()->text();

    plotGraph(nameX,nameY);
}

void SimpleCsvLogAnalyzer::tracerEvent(QMouseEvent *event)
{
    if(plotType == PLOT_NONE){
        return;
    }

    // Find corresponding graph value for both y and x
    mousePlotCoordX = ui->plot1->xAxis->pixelToCoord(event->pos().x());
    mousePlotCoordY = ui->plot1->yAxis->pixelToCoord(event->pos().y());
    //qDebug() << "Mouse plot coordinates. X:" << mousePlotCoordX << "Y:" << mousePlotCoordY;

    QVector<double> x(2), y(2);
    x[0] = mousePlotCoordX;
    y[0] = 0;
    x[1] = mousePlotCoordX;
    y[1] = 0;
    verticalLine->setData(x, y);
    QList<double> ret;
    tracer->setGraphKey(mousePlotCoordX);
    ui->plot1->replot();
    zoomCursorCenter = tracer->position->key();
    //qDebug() << "Slope of curve at:" << mousePlotCoordX << "is:" << calculateSlopeOfCurve(mousePlotCoordX);
    switch (plotType) {
    case PLOT_Y_VS_POINT_NUM:
        ret = calculateSlopeOfCurve(tracer->position->key());
        ui->statusbar->showMessage(QString("%1: %2, %3: %4, Left Slope: %5, Right Slope:%6")
                                   .arg(ui->plot1->xAxis->label())
                                   .arg(QString::number(tracer->position->key(),'f',2))
                                   .arg(ui->plot1->yAxis->label())
                                   .arg(QString::number(tracer->position->value(),'f',2))
                                   .arg(QString::number(ret[0],'f',2))
                .arg(QString::number(ret[1],'f',2)));
        break;
    case PLOT_Y_VS_X:
        ui->statusbar->showMessage(QString("%1: %2, %3: %4, Y/X: %5, Y/X of Mouse: %6").arg(ui->plot1->xAxis->label())
                                   .arg(QString::number(tracer->position->key(),'f',4))
                                   .arg(ui->plot1->yAxis->label())
                                   .arg(QString::number(tracer->position->value(),'f',4))
                                   .arg(QString::number(tracer->position->value()/tracer->position->key(),'f',4))
                                   .arg(QString::number(mousePlotCoordY/mousePlotCoordX,'f',4)));
        break;
    case PLOT_Y1_AND_Y2_VS_POINT_NUM:

        break;
    case PLOT_Y1_Y2_VS_X:

        break;
    default:
        break;
    }


}

void SimpleCsvLogAnalyzer::moveRigthPressed()
{
    qDebug() << "moveRigthPressed";
}

void SimpleCsvLogAnalyzer::on_actionZoom_Reset_triggered()
{
    zoomReset();
}

void SimpleCsvLogAnalyzer::on_actionZoom_In_triggered()
{
    QCPRange xRange = ui->plot1->xAxis->range();
    // use zoomCursorCenter for zooming centered at last traced point,
    // overwrite it with low + span/2 to zoom at plot center
    zoomCursorCenter = xRange.lower + (xRange.upper-xRange.lower)/2;
    double newSpan = (xRange.upper-xRange.lower)*0.9;
    xRange.lower = zoomCursorCenter - (newSpan/2);
    xRange.upper = zoomCursorCenter + (newSpan/2);
    ui->plot1->xAxis->setRange(xRange);
    ui->plot1->replot();
}

void SimpleCsvLogAnalyzer::on_actionZoom_Out_triggered()
{
    QCPRange xRange = ui->plot1->xAxis->range();
    // use zoomCursorCenter for zooming centered at last traced point,
    // overwrite it with low + span/2 to zoom at plot center
    zoomCursorCenter = xRange.lower + (xRange.upper-xRange.lower)/2;
    double newSpan = (xRange.upper-xRange.lower)*1.1111111;
    xRange.lower = zoomCursorCenter - (newSpan/2);
    xRange.upper = zoomCursorCenter + (newSpan/2);
    ui->plot1->xAxis->setRange(xRange);
    ui->plot1->replot();
}



void SimpleCsvLogAnalyzer::on_actionSave_Plot_Image_triggered()
{
    // Ask user to enter image name to save plot
    // It is covenient to generate a date-time and data field name based dafault file name for lazy users
    QString filePath;
#ifdef Q_OS_ANDROID
    QString defaultFileName = QString("plot_capture_%1_vs_%2_%3.jpg")
            .arg(ui->plot1->xAxis->label().remove(QRegExp("[^a-zA-Z\\d\\s]")))
            .arg(ui->plot1->yAxis->label().remove(QRegExp("[^a-zA-Z\\d\\s]")))
            .arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss"));
    CustomFileDialog *dlg = new CustomFileDialog(this,true,defaultFileName);
    dlg->showMaximized();
    int ret = dlg->exec();
    if(ret){
        filePath = dlg->filePath;
    } else {
        filePath.clear();
    }
    dlg->deleteLater();
    if(!filePath.endsWith(".jpg")){
        filePath.append(".jpg");
    }
#else
    filePath = QFileDialog::getSaveFileName(this,"Select a file...",
                                            QString("plot_capture_%1_vs_%2_%3.jpg")
                                            .arg(ui->plot1->xAxis->label().remove(QRegExp("[^a-zA-Z\\d\\s]")))
                                            .arg(ui->plot1->yAxis->label().remove(QRegExp("[^a-zA-Z\\d\\s]")))
                                            .arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss")),
                                            "*.jpg");
#endif

    startBusy();
    qDebug() << "filePath:" << filePath;
    if(filePath.isEmpty()){
        qDebug() << "Dosya seçilmedi";
        stopBusy();
        return;
    }
    // Hide tracer, before saving plot as image
    tracer->setVisible(false);
    ui->plot1->replot();
    ui->plot1->saveJpg(filePath,0,0,1,98);
    // Bring back tracer line
    tracer->setVisible(true);
    ui->plot1->replot();

    stopBusy();
}


void SimpleCsvLogAnalyzer::on_dataListY_currentRowChanged(int currentRow)
{
    if(currentRow<0){
        return;
    }
    QString s;
    if(currentRow>=m_sampleValues.length()){
        s = QString("No sample value for %1").arg(ui->dataListY->item(currentRow)->text());
    } else {
        s = QString("Sample value for %1 is %2").arg(ui->dataListY->item(currentRow)->text())
                .arg(m_sampleValues.at(currentRow));
    }
    ui->statusbar->showMessage(s);
}


void SimpleCsvLogAnalyzer::on_rightTabs_currentChanged(int index)
{
    // Close loading indicator
    stopBusy();
}

void SimpleCsvLogAnalyzer::on_rightTabs_tabBarClicked(int index)
{
    startBusy();
}

//void SimpleCsvLogAnalyzer::on_dataTableWidget_customContextMenuRequested(const QPoint &pos)
//{
//    Q_UNUSED(pos)
//    tableViewContextMenu->exec(QCursor::pos());
//}

//void SimpleCsvLogAnalyzer::hideTableColumns_forTable()
//{
//    QItemSelectionModel *select = ui->dataTableWidget->selectionModel();

//    if(!select->hasSelection()){ //check if has selection
//        qDebug() << "no selection";
//        return;
//    }
//    startBusy();
//    QModelIndexList indexList = select->selectedColumns(); // return selected column(s)

//    qDebug() << "Selected columns length:" << indexList.length();
//    for(int i=0; i<indexList.length(); ++i){
//        qDebug() << "Hide column:" << indexList[i].column();
//        ui->dataTableWidget->hideColumn(indexList[i].column());
//    }
//    ui->dataTableWidget->clearSelection();
//    stopBusy();
//}

//void SimpleCsvLogAnalyzer::showTableColumns_forTable()
//{
//    QItemSelectionModel *select = ui->dataTableWidget->selectionModel();

//    if(!select->hasSelection()){ //check if has selection
//        qDebug() << "no selection";
//        return;
//    }
//    startBusy();
//    QModelIndexList indexList = select->selectedColumns(); // return selected column(s)

//    // Hide all
//    for (int i=0; i<ui->dataTableWidget->columnCount(); ++i) {
//        ui->dataTableWidget->hideColumn(i);
//    }
//    ui->dataTableWidget->clearSelection();
//    // Show selected columns
//    qDebug() << "Selected columns length:" << indexList.length();
//    for(int i=0; i<indexList.length(); ++i){
//        qDebug() << "Hide column:" << indexList[i].column();
//        ui->dataTableWidget->showColumn(indexList[i].column());
//    }
//    stopBusy();
//}

//void SimpleCsvLogAnalyzer::restoreTableColumns_forTable()
//{
//    startBusy();
//    for (int i=0; i<ui->dataTableWidget->columnCount(); ++i) {
//        ui->dataTableWidget->showColumn(i);
//    }
//    ui->dataTableWidget->clearSelection();
//    stopBusy();
//}

//void SimpleCsvLogAnalyzer::plotThis_forTable()
//{
//    QItemSelectionModel *select = ui->dataTableWidget->selectionModel();

//    if(!select->hasSelection()){ //check if has selection
//        qDebug() << "no selection";
//        return;
//    }
//    startBusy();
//    QModelIndexList indexList = select->selectedColumns(); // return selected column(s)
//    qDebug() << "Plot: Selected column:" << indexList.first().column()
//             << "name:" << ui->dataTableWidget->horizontalHeaderItem(indexList.first().column())->text();
//    plotGraph("",ui->dataTableWidget->horizontalHeaderItem(indexList.first().column())->text());
//    ui->dataTableWidget->clearSelection();
//    stopBusy();
//}

//void SimpleCsvLogAnalyzer::statisticsForThis_forTable()
//{
//    QItemSelectionModel *select = ui->dataTableWidget->selectionModel();

//    if(!select->hasSelection()){ //check if has selection
//        qDebug() << "no selection";
//        return;
//    }
//    startBusy();
//    QModelIndexList indexList = select->selectedColumns(); // return selected column(s)
//    qDebug() << "Statistics: Selected column:" << indexList.first().column()
//             << "name:" << ui->dataTableWidget->horizontalHeaderItem(indexList.first().column())->text();
//    calculateStatisticalData(QVector<double>(),csvFile.getDataByName(ui->dataTableWidget->horizontalHeaderItem(indexList.first().column())->text()),true);
//    stopBusy();
//    ui->dataTableWidget->clearSelection();
//}

void SimpleCsvLogAnalyzer::plotThis_forList()
{
    QItemSelectionModel *select = ui->dataListY->selectionModel();

    if(!select->hasSelection()){ //check if has selection
        qDebug() << "no selection";
        return;
    }
    startBusy();
    QModelIndexList indexList = select->selectedRows(); // return selected column(s)
    qDebug() << "Plot: Selected column:" << indexList.first().row()
             << "name:" << ui->dataListY->item(indexList.first().row())->text();
    plotGraph("",ui->dataListY->item(indexList.first().row())->text());
    //    ui->dataTableWidget->clearSelection();
    stopBusy();
}

void SimpleCsvLogAnalyzer::plotThisVsAnotherDataLabel_forList()
{
    QItemSelectionModel *select = ui->dataListY->selectionModel();

    if(!select->hasSelection()){ //check if has selection
        qDebug() << "no selection";
        return;
    }
    QStringList labelList;
    for(int i=0;i<ui->dataListY->count();++i){
        labelList << ui->dataListY->item(i)->text();
    }
    QString selectedXAxisLabel = QInputDialog::getItem(this,"Select data label for X axis","X axis data label:",labelList,0);
    startBusy();
    QModelIndexList indexList = select->selectedRows(); // return selected column(s)
    qDebug() << "Plot: Selected column:" << indexList.first().row()
             << "name:" << ui->dataListY->item(indexList.first().row())->text();
    plotGraph(selectedXAxisLabel,ui->dataListY->item(indexList.first().row())->text());
    //    ui->dataTableWidget->clearSelection();
    stopBusy();
}

void SimpleCsvLogAnalyzer::statisticsForThis_forList()
{
    QItemSelectionModel *select = ui->dataListY->selectionModel();

    if(!select->hasSelection()){ //check if has selection
        qDebug() << "no selection";
        return;
    }
    startBusy();
    QModelIndexList indexList = select->selectedRows(); // return selected column(s)
    qDebug() << "Statistics: Selected column:" << indexList.first().row()
             << "name:" << ui->dataListY->item(indexList.first().row())->text();
    calculateStatisticalData(QVector<double>(),csvFile.getDataByName(ui->dataListY->item(indexList.first().row())->text()),true);
    stopBusy();
    //    ui->dataTableWidget->clearSelection();
}


void SimpleCsvLogAnalyzer::on_dataListY_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos)
    labelListContextMenu->exec(QCursor::pos());
}

void SimpleCsvLogAnalyzer::on_DataDerivator_clicked()
{

    //    QMessageBox msgBox;
    //    msgBox.setText(QString("Screen Resolution: W:%1, H:%2")
    //                   .arg(qApp->desktop()->width())
    //                   .arg(qApp->desktop()->height()));
    //    msgBox.exec();
    QStringList labelList;
    for(int i=0;i<ui->dataListY->count();++i){
        if(!ui->dataListY->item(i)->text().startsWith(mathStringStart)){
            labelList << ui->dataListY->item(i)->text();
        }
    }
    DataMath *math = new DataMath(labelList,mathOperatorsList);
#ifdef Q_OS_ANDROID
    math->showMaximized();
#endif
    //    math->showMaximized();
    int ret = math->exec();

    //connect(math,SIGNAL())
    //qDebug() << "Return:" << ret;
    qDebug() << "Math ops: " << math->mathOps;

    if(ret){
        if(math->mathOps.isEmpty()){
            ui->statusbar->showMessage("Empty formula for derived data!");
            showMessage("Empty formula for derived data!");
        } else {
            createDerivedDataLabel(math->mathOps);
            //            QString derivedDataLabel;
            //            derivedDataLabel += mathStringStart;
            //            for (int i=0;i<math->mathOps.length();++i) {
            //                derivedDataLabel += math->mathOps[i];
            //            }
            //            derivedDataLabel += mathStringEnd;
            //            ui->dataListY->addItem(derivedDataLabel);
            //            ui->dataListX->addItem(derivedDataLabel);
            //            QVector<double> values = createDerivedDataLabel(math->mathOps);
            //            qDebug() << "Derived data  name:" << derivedDataLabel << "data length:" << values.length();
            //            derivedDataVector.append(values);
            //            derivedDataVectorLabels.append(derivedDataLabel);
        }
    }

    math->deleteLater();
}

void SimpleCsvLogAnalyzer::on_actionData_Derivator_triggered()
{
    on_DataDerivator_clicked();
}

void SimpleCsvLogAnalyzer::on_actionPlot_SelectedData_triggered()
{
    on_plotSelected_clicked();
}

void SimpleCsvLogAnalyzer::on_actionplot_SelectedDataVsSelectedData_triggered()
{
    on_plotSelectedXY_clicked();
}

void SimpleCsvLogAnalyzer::plotThisPredefinedQuickPlot(QString labelNameForY, QString labelNameForX)
{
    //    if(!labelNameForX.isEmpty()){
    //        // Check if the labels list is empty
    //        if(ui->dataListY->count() ==0){
    //            showMessage("Open a log file before creating a new plot");
    //            return;
    //        }
    //        // Check if the selected label is derived
    //        if(labelfo)
    //            QList<QListWidgetItem *> items = ui->dataListY->findItems(labelNameForY,Qt::MatchContains);
    //        if(!items.isEmpty()){
    //            plotGraph("",items.first()->text());
    //        } else {
    //            showMessage("Cannot find selected label!\nAdd selected label(s) to \"what to log\" list "
    //                        "in your Torque app to favor this type of plot\n"
    //                        "Or retry with another log file that contains selected label");
    //            return;
    //        }
    //    }

    //    if(ui->dataListY->count() ==0){
    //        showMessage("Open a log file before creating a new plot");
    //        return;
    //    }
    //    QList<QListWidgetItem *> items = ui->dataListY->findItems(labelNameForY,Qt::MatchContains);
    //    if(!items.isEmpty()){
    //        plotGraph("",items.first()->text());
    //    } else {
    //        showMessage("Cannot find selected label!\nAdd Speed (OBD) label to \"what to log\" list "
    //                    "in your Torque app to favor this type of plot\n"
    //                    "Or retry with another log file that contains selected label");
    //        return;
    //    }
}

QString SimpleCsvLogAnalyzer::getProperLabelName(QString name)
{
    QString s;
    if(ui->dataListY->count() ==0){
        showMessage("Open a log file before creating a new plot");
        return s;
    }
    QList<QListWidgetItem *> items = ui->dataListY->findItems(name,Qt::MatchContains);
    if(!items.isEmpty()){
        s = items.first()->text();
    }
    return s;
}

void SimpleCsvLogAnalyzer::on_predefinedPlot1_clicked()
{
    // Speed (OBD) vs Time
    QString properName = getProperLabelName("Speed (OBD)");

    if(properName.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot\n"
                    "Or retry with another log file that contains selected label");
    } else {
        // add time info for x axis
        plotGraph("",properName);
    }

}

void SimpleCsvLogAnalyzer::on_predefinedPlot2_clicked()
{
    // Speed (GPS) vs Time
    QString properName = getProperLabelName("Speed (GPS)");

    if(properName.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // add time info for x axis
        plotGraph("",properName);
    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot3_clicked()
{
    // Altitude vs Time
    QString properName = getProperLabelName("Altitude");

    if(properName.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // add time info for x axis
        plotGraph("",properName);
    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot4_clicked()
{
    // Avg. Consumption vs Time
    QString properName = getProperLabelName("Trip average");

    if(properName.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // add time info for x axis
        plotGraph("",properName);
    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot5_clicked()
{
    // LTFT vs Time
    QString properName = getProperLabelName("Fuel Trim Bank 1 Long Term");

    if(properName.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // add time info for x axis
        plotGraph("",properName);
    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot7_clicked()
{
    // STFT1 vs Time
    QString properName = getProperLabelName("Fuel Trim Bank 1 Short Term");

    if(properName.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // add time info for x axis
        plotGraph("",properName);
    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot6_clicked()
{
    // LTFT+STFT vs RPM
    QString ltft = getProperLabelName("Fuel Trim Bank 1 Long Term");
    QString stft = getProperLabelName("Fuel Trim Bank 1 Short Term");
    QString rpm = getProperLabelName("Engine RPM");

    if(ltft.isEmpty() | stft.isEmpty() | rpm.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // Check if there is already a neccessary derived data
        QStringList formula;
        QString ddLabel;
        formula.append(ltft);
        formula.append("+");
        formula.append(stft);
        ddLabel += mathStringStart;
        for (int i=0;i<formula.length();++i) {
            ddLabel += formula[i];
        }
        ddLabel += mathStringEnd;
        ddLabel = getProperLabelName(ddLabel);
        if(ddLabel.isEmpty()){
            // Create a derived data (stft+ltft)/rpm
            ddLabel = createDerivedDataLabel(formula);
        }
        if(!ddLabel.isEmpty()){
            plotGraph(rpm,ddLabel);
        } else {
            showMessage("Quick Plot Error");
        }

    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot8_clicked()
{
    // Speed (OBD) / RPM vs Time
    QString speed = getProperLabelName("Speed (OBD)");
    QString rpm = getProperLabelName("Engine RPM");

    if(speed.isEmpty() | rpm.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // Check if there is already a neccessary derived data
        QStringList formula;
        QString ddLabel;
        formula.append(speed);
        formula.append("/");
        formula.append(rpm);
        ddLabel += mathStringStart;
        for (int i=0;i<formula.length();++i) {
            ddLabel += formula[i];
        }
        ddLabel += mathStringEnd;
        ddLabel = getProperLabelName(ddLabel);
        if(ddLabel.isEmpty()){
            // Create a derived data
            ddLabel = createDerivedDataLabel(formula);
        }
        if(!ddLabel.isEmpty()){
            plotGraph("",ddLabel);
        } else {
            showMessage("Quick Plot Error");
        }

    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot9_clicked()
{
    // RPM
    QString properName = getProperLabelName("Engine RPM");

    if(properName.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // add time info for x axis
        plotGraph("",properName);
    }
}

void SimpleCsvLogAnalyzer::on_predefinedPlot10_clicked()
{
    // LTFT+STFT vs Time
    QString ltft = getProperLabelName("Fuel Trim Bank 1 Long Term");
    QString stft = getProperLabelName("Fuel Trim Bank 1 Short Term");

    if(ltft.isEmpty() | stft.isEmpty()){
        showMessage("Cannot find or derive selected label!\nAdd selected label(s) to \"what to log\" list "
                    "in your Torque app to favor this type of plot or retry with another log file that contains selected label");
    } else {
        // Check if there is already a neccessary derived data
        QStringList formula;
        QString ddLabel;
        formula.append(ltft);
        formula.append("+");
        formula.append(stft);
        ddLabel += mathStringStart;
        for (int i=0;i<formula.length();++i) {
            ddLabel += formula[i];
        }
        ddLabel += mathStringEnd;
        ddLabel = getProperLabelName(ddLabel);
        if(ddLabel.isEmpty()){
            // Create a derived data (stft+ltft)/rpm
            ddLabel = createDerivedDataLabel(formula);
        }
        if(!ddLabel.isEmpty()){
            // add real time
            plotGraph("",ddLabel);
        } else {
            showMessage("Quick Plot Error");
        }

    }
}

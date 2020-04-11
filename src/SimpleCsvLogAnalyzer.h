#ifndef SIMPLECSVLOGANALYZER_H
#define SIMPLECSVLOGANALYZER_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QDialog>
#include <QFileDialog>
#include <QShortcut>
#include <QMenu>
#include <QLocale>
#include "QCustomPlot/qcustomplot.h"
#include "CsvFileProcessor.h"
#include "DataMath.h"
#include "CustomFileDialog.h"
#include <limits>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#endif



enum{
    PLOT_NONE,
    PLOT_Y_VS_POINT_NUM,
    PLOT_Y_VS_X,
    PLOT_Y1_AND_Y2_VS_POINT_NUM,
    PLOT_Y1_Y2_VS_X
};

typedef struct{
    double min = 0;
    double max = 0;
    double span = 0;
    double average = 0;
    double median = 0;
    int length;
}_statistics;

typedef struct{
    _statistics x;
    _statistics y;
}statistics;

QT_BEGIN_NAMESPACE
namespace Ui { class SimpleCsvLogAnalyzer; }
QT_END_NAMESPACE

class SimpleCsvLogAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    // variables
    // methods
    SimpleCsvLogAnalyzer(QWidget *parent = nullptr);
    ~SimpleCsvLogAnalyzer();

    void plotGraph(QString xName, QString yName);

private slots:
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void on_plotSelected_clicked();
    void on_plotSelectedXY_clicked();
    void tracerEvent(QMouseEvent * event);
    void moveRigthPressed();
    void on_actionZoom_Reset_triggered();
    void on_actionSave_Plot_Image_triggered();
    void on_dataListY_currentRowChanged(int currentRow);
    void on_rightTabs_currentChanged(int index);
    void on_rightTabs_tabBarClicked(int index);
    //    void on_dataTableWidget_customContextMenuRequested(const QPoint &pos);
    void on_dataListY_customContextMenuRequested(const QPoint &pos);
    void on_DataDerivator_clicked();

    void on_actionData_Derivator_triggered();

    void on_actionPlot_SelectedData_triggered();

    void on_actionplot_SelectedDataVsSelectedData_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void plotThisPredefinedQuickPlot(QString labelNameForY, QString labelNameForX);
    QString getProperLabelName(QString name);

    void on_predefinedPlot1_clicked();

    void on_predefinedPlot2_clicked();

    void on_predefinedPlot3_clicked();

    void on_predefinedPlot4_clicked();

    void on_predefinedPlot5_clicked();

    void on_predefinedPlot7_clicked();

    void on_predefinedPlot6_clicked();

    void on_predefinedPlot8_clicked();

    void on_predefinedPlot9_clicked();

    void on_predefinedPlot10_clicked();

public slots:
    // Slots for data table view custom context menu options
    //    void hideTableColumns_forTable();
    //    void showTableColumns_forTable();
    //    void restoreTableColumns_forTable();
    //    void plotThis_forTable();
    //    void statisticsForThis_forTable();
    void plotThis_forList();
    void plotThisVsAnotherDataLabel_forList();
    void statisticsForThis_forList();

private:
    // variables
    Ui::SimpleCsvLogAnalyzer *ui;
    CsvFileProcessor csvFile;
    QCPItemTracer *tracer;
    QCPCurve *verticalLine;
    QShortcut *moveRight,*moveLeft;
    QSplashScreen *loadingSplash;
    QMenu *tableViewContextMenu;
    QMenu *labelListContextMenu;
    double mousePlotCoordX = 0;
    double mousePlotCoordY = 0;
    QVector<double> xVals;
    QVector<double> yVals;
    QVector<QVector<double>> derivedDataVector;
    QVector<QString> derivedDataVectorLabels;
    statistics stats;
    QStringList mathOperatorsList = QStringList() << "+" << "-" << "*" << "/";
    QString mathStringStart = QString("_drvd(");
    QString mathStringEnd = QString(")_");
    QString torqueDeviceTimeFormat = QString("d-MMM-yyyy HH:mm:ss.zzz");   // e.g. 12-Jul-2015 22:15:00.473
    QLocale defaultEngLocale = QLocale(QLocale::English, QLocale::UnitedStates);
    QStringList m_labels,m_sampleValues;
    int plotType = PLOT_NONE;
    double zoomCursorCenter = 0;

    // Plots
    QCPGraph *valuePlot;
    QCPGraph *cursorPlot;

#ifdef Q_OS_ANDROID
#endif

    // methods
    void cleanUpAndExit();
    void initPlot();
    //void initDataTable();
    void zoomReset();
    QList<double> calculateSlopeOfCurve(double keyValue);
    void clearPlotNDisableTracer();
    void setupTracer();
    statistics calculateStatisticalData(QVector<double> x, QVector<double> y, bool showReportMessage);
    void populateStatisticsLabels();
    void clearStatisticsLabels();
    void startBusy();
    void stopBusy();
    QString createDerivedDataLabel(QStringList formula);

    static void showMessage(QString test){
        QMessageBox msgBox;
        msgBox.setText(test);
        msgBox.exec();
    }

    enum {
        permissionDenied,
        alreadyGranted,
        granted
    };

    static int getAndroidPermission(QString permissionName){
#if defined (Q_OS_ANDROID)
        int ret = permissionDenied;
        //Request requiered permissions at runtime
        auto result = QtAndroid::checkPermission(permissionName);
        if(result == QtAndroid::PermissionResult::Denied){
            //showMessage("Permission has not given before!, Requesting now");
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permissionName}));
            if(resultHash[permissionName] == QtAndroid::PermissionResult::Denied){
                showMessage("Permission denied to "+permissionName);
                int ret = permissionDenied;
            } else {
                showMessage("Permission granted to "+permissionName);
                ret = granted;
            }
        } else {
            ret = alreadyGranted;
        }
        return ret;
#endif
       return -1;
    }

};
#endif // 

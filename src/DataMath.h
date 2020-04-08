#ifndef DATAMATH_H
#define DATAMATH_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class DataMath;
}

class DataMath : public QDialog
{
    Q_OBJECT

public:
    explicit DataMath(QStringList labelList,QStringList opList, QWidget *parent = nullptr);
    ~DataMath();
    QStringList mathOperationsList;
    QStringList mathOps;

private slots:
    void on_dataLabels_itemDoubleClicked(QListWidgetItem *item);

    void on_operatorList_itemDoubleClicked(QListWidgetItem *item);

    void on_clear_clicked();

    void on_dataLabels_itemClicked(QListWidgetItem *item);

    void on_operatorList_itemClicked(QListWidgetItem *item);

private:
    Ui::DataMath *ui;
};

#endif // DATAMATH_H

#include "DataMath.h"
#include "ui_DataMath.h"

DataMath::DataMath(QStringList labelList,QStringList opList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataMath)
{
    mathOperationsList = opList;
    ui->setupUi(this);
    for(int i=0;i<labelList.length();++i){
        ui->dataLabels->addItem(labelList[i]);
    }
    for(int i=0;i<opList.length();++i){
        ui->operatorList->addItem(opList[i]);
    }
    ui->operatorList->setEnabled(false);
    ui->dataLabels->setEnabled(true);
}

DataMath::~DataMath()
{
    delete ui;
}

void DataMath::on_dataLabels_itemDoubleClicked(QListWidgetItem *item)
{
    mathOps.append(item->text());
    ui->dataMath->clear();
    for (int i=0;i<mathOps.length();++i) {
        ui->dataMath->setText(ui->dataMath->text()+mathOps[i]);
    }
    if(mathOps.length()==1){
        ui->operatorList->setEnabled(true);
    }
}

void DataMath::on_dataLabels_itemClicked(QListWidgetItem *item)
{
    on_dataLabels_itemDoubleClicked(item);
}

void DataMath::on_operatorList_itemDoubleClicked(QListWidgetItem *item)
{
    mathOps.append(item->text());
    ui->dataMath->clear();
    for (int i=0;i<mathOps.length();++i) {
        ui->dataMath->setText(ui->dataMath->text()+mathOps[i]);
    }

}

void DataMath::on_operatorList_itemClicked(QListWidgetItem *item)
{
    on_operatorList_itemDoubleClicked(item);
}

void DataMath::on_clear_clicked()
{
    if(mathOps.length()>0){
        mathOps.removeLast();
        ui->dataMath->clear();
        for (int i=0;i<mathOps.length();++i) {
            ui->dataMath->setText(ui->dataMath->text()+mathOps[i]);
        }
    }
}





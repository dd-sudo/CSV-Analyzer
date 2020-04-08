#include "CustomFileDialog.h"
#include "ui_CustomFileDialog.h"

#include <QKeyEvent>

CustomFileDialog::CustomFileDialog(QWidget *parent, bool saveFile, QString defaultFile) :
    QDialog(parent),
    ui(new Ui::CustomFileDialog)
{
    mSaveFile = saveFile;
    mDefaultFileName = defaultFile;
    ui->setupUi(this);

    if(mSaveFile){
        ui->okBtn->setText("Save");
    }
    ui->fileNameEdit->setText(mDefaultFileName);
    // Creates our new model and populate
    QString mPath = "/storage/emulated/0/";

    // All entries
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries | QDir::NoDot);
    model->setNameFilters(QStringList()<< "*.csv" << "*.jpg");

    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->setRootPath(mPath));
    ui->filePathEdit->setText(model->rootPath());
    fi.setFile(model->rootPath());


    // qlineedits cannot effectively catch enter key event so it should be handled!
    //    One can disable this behavior by setting setDefault() and setAutoDefault() on the button. To disable this on all buttons in your dialog add this snippet after you instantiated and initialized the ui from Designer:

    //    @
    //    QList<QPushButton *> buttonList = findChildren<QPushButton *>();
    //    foreach(QPushButton *pb, buttonList) {
    //    pb->setDefault( false );
    //    pb->setAutoDefault( false );
    //    }
    //    @

    QList<QPushButton *> buttonList = findChildren<QPushButton *>();
    foreach(QPushButton *pb, buttonList) {
        pb->setDefault( false );
        pb->setAutoDefault( false );
    }

}

CustomFileDialog::~CustomFileDialog()
{
    delete ui;
}


void CustomFileDialog::on_listView_clicked(const QModelIndex &index)
{
    QString mPath = model->fileInfo(index).canonicalFilePath();
    fi.setFile(mPath);
    if(fi.isDir()){
        qDebug() << mPath << "is a directory";
        ui->listView->setRootIndex(model->setRootPath(mPath));
        if(!mSaveFile){
            ui->fileNameEdit->clear();
        }
    } else {
        qDebug() << mPath << "is a file";
        ui->fileNameEdit->setText(fi.fileName());
    }
    //    qDebug() << "Path:" << fi.canonicalFilePath();
    ui->filePathEdit->setText(fi.canonicalFilePath());

}

void CustomFileDialog::on_cancelBtn_clicked()
{
    filePath.clear();
    this->reject();

}

void CustomFileDialog::on_filePathEdit_returnPressed()
{
    qDebug() << "return pressed!";
}

void CustomFileDialog::on_okBtn_clicked()
{
    qDebug() << "Selected:" << ui->fileNameEdit->text();
    QFileInfo tfi;
    tfi.setFile(model->rootPath(),ui->fileNameEdit->text());
    if(tfi.isDir()){
        qDebug() << "Yes," << tfi.canonicalFilePath() << "is a directory";
        ui->listView->setRootIndex(model->setRootPath(tfi.canonicalFilePath()));
    } else {
        qDebug() << "It is a file:" << tfi.absoluteFilePath();
        filePath = tfi.absoluteFilePath();
        this->accept();
    }
    ui->fileNameEdit->clear();


}

void CustomFileDialog::on_fileNameEdit_returnPressed()
{
    //    qDebug() << "return pressed!";
    on_okBtn_clicked();

}

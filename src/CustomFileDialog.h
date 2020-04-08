#ifndef CUSTOMFILEDIALOG_H
#define CUSTOMFILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDebug>

namespace Ui {
class CustomFileDialog;
}

class CustomFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomFileDialog(QWidget *parent, bool saveFile = false, QString defaultFile = QString(""));
    ~CustomFileDialog();
    QString filePath;


private:
    Ui::CustomFileDialog *ui;
    bool mSaveFile = false;
    QString mDefaultFileName;

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_cancelBtn_clicked();

    void on_filePathEdit_returnPressed();

    void on_okBtn_clicked();

    void on_fileNameEdit_returnPressed();

private:
    QFileSystemModel *model;
    QFileInfo fi;
};

#endif // CUSTOMFILEDIALOG_H

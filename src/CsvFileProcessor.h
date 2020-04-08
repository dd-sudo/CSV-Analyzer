#ifndef CSVFILEPROCESSOR_H
#define CSVFILEPROCESSOR_H

#include <QFile>
#include <QObject>
#include <QDebug>
#include <math.h>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableWidget>


class CsvFileProcessor : public QObject
{
    Q_OBJECT
public:
    explicit CsvFileProcessor(QObject *parent = nullptr);
    void setFilePath(QString filePath);
    QStringList getCsvFileLabels();
    QStringList getSampleValuesForLabels();
    QVector<double> getDataByName(QString dataName);
    QStringList getRawDataByName(QString dataName);
    bool file2DataModel(QStandardItemModel *mdl);
    bool file2TableWidget(QTableWidget *tw);

    // variables
    QString valueSeperator = QString(",");

public slots:

signals:

private:
    QFile m_file;
    QString m_filePath;
    QStringList m_valueNames;
    QVector<double> values;
    QByteArray readLineFromCSV(QFile *file, uint16_t maxLen = 16384);
};

#endif // CSVFILEPROCESSOR_H

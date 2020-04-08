#include "CsvFileProcessor.h"

#include <QApplication>


CsvFileProcessor::CsvFileProcessor(QObject *parent) : QObject(parent)
{

}

void CsvFileProcessor::setFilePath(QString filePath)
{
    m_filePath = filePath;
    if(m_file.isOpen()){
        m_file.close();
    }
    m_file.setFileName(m_filePath);
    if(!m_file.open(QIODevice::ReadOnly)){
        qDebug() << "File could not opened!";
    }
}

QByteArray CsvFileProcessor::readLineFromCSV(QFile *file, uint16_t maxLen){
    // QIODEvice::readLine support only \n line endings,
    // This method accepts either \n or \r line ending
    QByteArray result;
    if(!file->isOpen()){
        qDebug() << "File is not opened!";
        return result;
    }

    result.resize(maxLen);
    int readBytes = 0;
    char c = 0;
    bool readMore = true;
    while(readMore) {
        file->getChar(&c);
        result[readBytes] = c;
        ++readBytes;
        if((readBytes > (maxLen-2)) || (c == '\n') || (c == '\r')){
            readMore = false;
        }
    }
    result[readBytes] = 0;
    // some csv files have \r\n line ending, e.g. my temp. Humidity logger.
    // check there is a following \n or \r in the read line
    // if true, skip it, if false rewind
    file->getChar(&c);
    if((c != '\n') || (c != '\r')){
        file->seek(-1);
    }
    //qDebug() << "readBytes:" << readBytes;
    return result;
}

QStringList CsvFileProcessor::getCsvFileLabels()
{
    if(!m_file.isOpen()){
        qDebug() << "No csv file specified";
        m_valueNames.clear();
        return m_valueNames;
    }
    m_file.seek(0); // seek to start of the file
    // Get value field names from first line
    //QString str = QString::fromUtf8(m_file.readLine());
    QString str = QString::fromUtf8(readLineFromCSV(&m_file));
    //qDebug() << "Titles:" << str;
    m_valueNames = str.split(valueSeperator);
    for(int i=0;i<m_valueNames.length();++i){
        m_valueNames.replace(i,m_valueNames.at(i).trimmed());
    }
    //qDebug() << "m_valueNames:" << m_valueNames;
    return m_valueNames;
}

QStringList CsvFileProcessor::getSampleValuesForLabels()
{
    QStringList values4Labels;
    if(!m_file.isOpen()){
        qDebug() << "No csv file specified";
        values4Labels.clear();
        return values4Labels;
    }
    m_file.seek(0); // seek to start of the file
    readLineFromCSV(&m_file); // skip labels
    // Get value field names from first line
    //QString str = QString::fromUtf8(m_file.readLine());
    QString str = QString::fromUtf8(readLineFromCSV(&m_file));
    values4Labels = str.split(valueSeperator);
    for(int i=0;i<values4Labels.length();++i){
        values4Labels.replace(i,values4Labels.at(i).trimmed());
    }
    qDebug() << "values4Labels:" << values4Labels;
    return values4Labels;
}

QVector<double> CsvFileProcessor::getDataByName(QString dataName)
{
    bool ok = false;
    double dVal;
    values.clear();
    int index = m_valueNames.indexOf(dataName);
    if(index==-1){
        qDebug() << "No matching data name";
        return values;
    }
    //qDebug() << "Data index:" << index;
    // Gather values
    QString str;
    QStringList strList;
    m_file.seek(0); // seek to start of the file
    readLineFromCSV(&m_file); // skip labels
    str = QString::fromUtf8(readLineFromCSV(&m_file));
    while(!str.isEmpty()){
        strList = str.split(valueSeperator);
        dVal = strList.value(index).toDouble(&ok);
        //qDebug() << /*"Str:" << strList.value(index)*/ "StrList:" << strList << "value:" << dVal;
        if(!ok){
            dVal = NAN;
            //qDebug() << "toDouble error. str:" << strList.value(index);
            //break;
        }
        values.append(dVal);
        str = QString::fromUtf8(readLineFromCSV(&m_file));
    }
    if(values.isEmpty()){
        qDebug() << "Values is empty";
    } else {
        qDebug() << "str:" << str << "first val:" << values.first() << "last val:" << values.last() << "value count" << values.length();
    }
    return values;
}

QStringList CsvFileProcessor::getRawDataByName(QString dataName)
{
    QStringList vals;
    int index = m_valueNames.indexOf(dataName);
    if(index==-1){
        qDebug() << "No matching data name";
        return vals;
    }
    //qDebug() << "Data index:" << index;
    // Gather values
    QString str;
    QStringList strList;
    m_file.seek(0); // seek to start of the file
    readLineFromCSV(&m_file); // skip labels
    str = QString::fromUtf8(readLineFromCSV(&m_file));
    while(!str.isEmpty()){
        strList = str.split(valueSeperator);
        vals.append(strList.value(index));
        str = QString::fromUtf8(readLineFromCSV(&m_file));
    }
    if(vals.isEmpty()){
        qDebug() << "Values is empty";
    } else {
        qDebug() << "str:" << str << "first val:" << vals.first() << "last val:" << vals.last() << "value count" << vals.length();
    }
    return vals;
}

bool CsvFileProcessor::file2TableWidget(QTableWidget *tw)
{
    if(!m_file.isOpen()){
        qDebug() << "No csv file specified";
        return false;
    }
    QString str;
    QStringList values;
    values = getCsvFileLabels();
    tw->clear();
    tw->setRowCount(0);
    tw->setColumnCount(0);
    tw->setColumnCount(values.length());
    tw->setHorizontalHeaderLabels(values);
    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    m_file.seek(0); // seek to start of the file
    readLineFromCSV(&m_file); // skip labels
    str = QString::fromUtf8(readLineFromCSV(&m_file));
    int rowNum = 0;
    while(!str.isEmpty()){
        tw->insertRow(rowNum);
        values = str.split(valueSeperator);
        for(int i=0;i<values.length();++i){
            QTableWidgetItem *newItem = new QTableWidgetItem(values.at(i).trimmed());
            tw->setItem(rowNum,i,newItem);
        }
        str = QString::fromUtf8(readLineFromCSV(&m_file));
        ++rowNum;
    }


    return true;
}

bool CsvFileProcessor::file2DataModel(QStandardItemModel *mdl)
{
    if(!m_file.isOpen()){
        qDebug() << "No csv file specified";
        return false;
    }
    if(mdl == nullptr){
        qDebug() << "Model error!";
        return false;
    }
    QString str;
    QStringList values;
    QModelIndex index;
    values = getCsvFileLabels();
    mdl->clear();
    mdl->setColumnCount(values.length());
    mdl->setHorizontalHeaderLabels(values);

    m_file.seek(0); // seek to start of the file
    readLineFromCSV(&m_file); // skip labels
    str = QString::fromUtf8(readLineFromCSV(&m_file));
    int rowNum = 0;
    while(!str.isEmpty()){
        mdl->insertRow(rowNum);
        values = str.split(valueSeperator);
        for(int i=0;i<values.length();++i){
            index =  mdl->index(rowNum,i,QModelIndex());
            mdl->setData(index,values.at(i).trimmed());
        }
        str = QString::fromUtf8(readLineFromCSV(&m_file));
        ++rowNum;
        //QApplication::processEvents();
    }

}

//bool CsvFileProcessor::file2TableWidget(QTableWidget *tw)
//{
//    if(!m_file.isOpen()){
//        qDebug() << "No csv file specified";
//        return false;
//    }
//    QString str;
//    QStringList values;
//    values = getCsvFileLabels();
//    tw->clear();
//    tw->setRowCount(0);
//    tw->setColumnCount(0);
//    tw->setColumnCount(values.length());
//    tw->setHorizontalHeaderLabels(values);
//    tw->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

//    m_file.seek(0); // seek to start of the file
//    readLineFromCSV(&m_file); // skip labels
//    str = QString::fromUtf8(readLineFromCSV(&m_file));
//    int rowNum = 0;
//    while(!str.isEmpty()){
//        tw->insertRow(rowNum);
//        values = str.split(valueSeperator);
//        for(int i=0;i<values.length();++i){
//            QTableWidgetItem *newItem = new QTableWidgetItem(values.at(i).trimmed());
//            tw->setItem(rowNum,i,newItem);
//        }
//        str = QString::fromUtf8(readLineFromCSV(&m_file));
//        ++rowNum;
//    }
//    return true;
//}


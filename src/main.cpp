#include "SimpleCsvLogAnalyzer.h"

#include <QApplication>

// Application Icon made by Freepik from www.flaticon.com

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleCsvLogAnalyzer w;
    w.show();
    return a.exec();
}

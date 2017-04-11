#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "medialibrary.h"
#include "songinfo.h"
#include "songsinlibrary.h"
#include "songsinlibrarysortfilter.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTableView * tableViewSorted;
    MediaLibrary mediaLibrary;
    void configSignals();
    void setupCustomWidgets();
};

#endif // MAINWINDOW_H

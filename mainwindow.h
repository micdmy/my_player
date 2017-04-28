#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "medialibrary.h"
#include "songinfo.h"
#include "songsinlibrary.h"
#include "songsinlibrarysortfilter.h"
#include "onetagtablemodel.h"
#include <QMdiArea>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMdiArea centralMdiArea;


private:
    Ui::MainWindow *ui;
    QTableView * tableViewSorted;
    QTableView * tableViewOneTag;
    SearchFrame songListSearchFrame;
    SearchFrame oneTagSearchFrame;
    MediaLibrary mediaLibrary;
    void configSignals();

};

#endif // MAINWINDOW_H

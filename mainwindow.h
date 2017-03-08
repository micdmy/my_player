#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "medialibrary.h"
#include "songinfo.h"
#include "songsinlibrary.h"
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
    MediaLibrary mediaLibrary;
    void configSignals();

};

#endif // MAINWINDOW_H

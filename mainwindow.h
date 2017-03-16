#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
private slots:
    void on_actionrepaint_triggered();


private:
    Ui::MainWindow *ui;
    MediaLibrary mediaLibrary;
    void configSignals();

};

#endif // MAINWINDOW_H

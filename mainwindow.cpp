#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configSignals();
    mediaLibrary.load();
    ui->tableView->setModel(mediaLibrary.getDataModelPtr());

    /*SongInfo s;
    s.setPath("/home/mic/ver.mp3");


    s.readFile();*/
    //SongsInLibrary sin;

    //sin.addSongs(paths);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configSignals()
{
    connect(ui->actionEdit_directories,SIGNAL(triggered()),&mediaLibrary,SLOT(editDirectories()));
    connect(ui->actionReload_all,SIGNAL(triggered()),&mediaLibrary,SLOT(reloadAllDirectories()));
    connect(ui->actionUsed_tags,SIGNAL(triggered()),&mediaLibrary,SLOT(editUsedTags()));
    connect(ui->actionUsed_file_formats,SIGNAL(triggered()),&mediaLibrary,SLOT(editUsedFileFormats()));
    connect(ui->actionSet_default_tags_file_formats,SIGNAL(triggered()),&mediaLibrary,SLOT(setDefaultTagsAndFileFormats()));
}




void MainWindow::on_actionrepaint_triggered()
{
   // ui->tableView->repaint();
}

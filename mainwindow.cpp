#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupCustomWidgets();
    configSignals();

    mediaLibrary.load();

    ui->tableView->setModel( mediaLibrary.getDataModelPtr() );
    mediaLibrary.initProxyModel();
    tableViewSorted->setModel( mediaLibrary.getProxyModel() );
    mediaLibrary.setupProxyModel(
                tableViewSorted->selectionModel(), //sets selection model
                ui->frameSearchSongs); //connects with lineEdit textChanged signal
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

void MainWindow::setupCustomWidgets()
{
    tableViewSorted =new QTableView();
    ui->frameSearchSongs->addWidget(tableViewSorted);
}




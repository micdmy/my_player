#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableViewSorted =new QTableView();
    songListSearchFrame.addWidget(tableViewSorted);
    mediaLibrary.load();

    mediaLibrary.initProxyModel();
    tableViewSorted->setModel( mediaLibrary.getProxyModel() );
    mediaLibrary.setupProxyModel(
                tableViewSorted->selectionModel(), //sets selection model
                &songListSearchFrame); //connects with lineEdit textChanged signal
    OneTagSortFilter * oneTagSortFilter =mediaLibrary.oneTagFiltersReload().first();
    tableViewOneTag = new QTableView();
    oneTagSearchFrame.addWidget(tableViewOneTag);
    tableViewOneTag->setModel(oneTagSortFilter);
    connect(&oneTagSearchFrame,SIGNAL(searchTextChanged(QString)),
            oneTagSortFilter,SLOT(setFilterRegExp(QString)));
    oneTagSortFilter->setSelectionModel(tableViewOneTag->selectionModel());

    setCentralWidget(&centralMdiArea);
    centralMdiArea.addSubWindow(&oneTagSearchFrame);
    centralMdiArea.addSubWindow(&songListSearchFrame);
    configSignals();
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



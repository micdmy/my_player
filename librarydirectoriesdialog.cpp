#include "librarydirectoriesdialog.h"
#include "ui_librarydirectoriesdialog.h"

LibraryDirectoriesDialog::LibraryDirectoriesDialog(DirectoriesListModel * dirModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibraryDirectoriesDialog),
    model(dirModel)
{
    ui->setupUi(this);
    setWindowTitle("Source directories for media library");
    ui->directoriesView->setModel(model);
    selectionModel = ui->directoriesView->selectionModel();
    ui->directoriesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->directoriesView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(pathDoubleClicked(QModelIndex)));
    oldDirectories = model->getList();
}

LibraryDirectoriesDialog::~LibraryDirectoriesDialog()
{
    removeRepeats();
    emit directoriesChanged(getAdded(), getRemoved());
    delete ui;
}

void LibraryDirectoriesDialog::removeRepeats()
{
    QStringList & paths = model->getList();
    for(int i=0;i<paths.length()-1;i++) {
        for(int j=i+1;j<paths.length();j++) {
            if(paths.at(i) == paths.at(j)) {
                paths.removeAt(j--);
            }
        }
    }
}

QStringList LibraryDirectoriesDialog::getAdded()
{
    QStringList & paths = model->getList();
    QStringList ret;
    bool isNew;
    for(QString now : paths) {
        isNew = true;
        for(QString old : oldDirectories) {
            if(now == old) {
                isNew = false;
            }
        }
        if(isNew) {
            ret.append(now);
        }
    }
    return ret;
}

QStringList LibraryDirectoriesDialog::getRemoved()
{
    QStringList & paths = model->getList();
    QStringList ret;
    bool isInNew;
    for(QString old : oldDirectories) {
        isInNew = false;
        for(QString now : paths) {
            if(now == old) {
                isInNew = true;
            }
        }
        if(!isInNew) {
            ret.append(old);
        }
    }
    return ret;
}

void LibraryDirectoriesDialog::editPath(int row)
{
    //removeInNewDirectories(model->getList().operator [](row));
    QString newPath = model->edit(row);
    //newDirectories.append(newPath);
}

int LibraryDirectoriesDialog::getCurrentRow()
{
    const QModelIndex index = ui->directoriesView->selectionModel()->currentIndex();
    if(index.isValid()){
        return index.row();
    } else {
        return -1;
    }
}
/*
void LibraryDirectoriesDialog::removeInNewDirectories(QString path)
{

    for(int i=0; i<newDirectories.length(); i++) {
        if(newDirectories[i] == path) {
            newDirectories.removeAt(i);
        }
    }
}*/

void LibraryDirectoriesDialog::pathDoubleClicked(QModelIndex index)
{
    editPath(index.row());
}

void LibraryDirectoriesDialog::on_addButton_clicked()
{
    QString newPath = model->add();
    //newDirectories.append(newPath);
}

void LibraryDirectoriesDialog::on_removeButton_clicked()
{
    int index = getCurrentRow();
    if(index >= 0){
        selectionModel->clearCurrentIndex();
        model->remove(index);
        //removeInNewDirectories(model->getList().operator [](index));
    }
}

void LibraryDirectoriesDialog::on_editButton_clicked()
{
    int row = getCurrentRow();
    if(row >= 0){
        editPath(row);
    }
}

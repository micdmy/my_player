#ifndef LIBRARYDIRECTORIESDIALOG_H
#define LIBRARYDIRECTORIESDIALOG_H

#include <QDialog>
#include "mediadirectories.h"
#include <QAbstractItemModel>
#include <QStringListModel>
#include<QAbstractItemView>
#include "directorieslistmodel.h"
namespace Ui {
class LibraryDirectoriesDialog;
}

class LibraryDirectoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LibraryDirectoriesDialog(DirectoriesListModel *dirModel, QWidget *parent = 0);
    ~LibraryDirectoriesDialog();

private:
    Ui::LibraryDirectoriesDialog *ui;
    MediaDirectories * mediaDirectories;
    DirectoriesListModel * model;
    QItemSelectionModel * selectionModel;
    QStringList newDirectories;
    void editPath(int row);
    int getCurrentRow();
    void removeInNewDirectories(QString path);
private slots:
  void pathDoubleClicked(QModelIndex index );
  void on_addButton_clicked();
  void on_removeButton_clicked();
  void on_editButton_clicked();
signals:
  void directoriesAdded(QStringList dirs);
};

#endif // LIBRARYDIRECTORIESDIALOG_H

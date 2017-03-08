#include "stringlistdialog.h"
#include "ui_stringlistdialog.h"

StringListDialog::StringListDialog(QStringListModel * stringListModel, const QString & title, const QString &info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StringlIstDialog),
    model(stringListModel)
{
    ui->setupUi(this);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                  QAbstractItemView::DoubleClicked);
    ui->infoLabel->setText(info);
    setWindowTitle(title);
}

StringListDialog::~StringListDialog()
{
    delete ui;
}

void StringListDialog::on_addButton_clicked()
{
    int row = model->rowCount();
    model->insertRows(row,1);
    editRow(row);
}

void StringListDialog::on_editButton_clicked()
{
    int row = ui->listView->currentIndex().row();
    editRow(row);
}

void StringListDialog::on_removeButton_clicked()
{
    model->removeRows(ui->listView->currentIndex().row(),1);
}

void StringListDialog::on_insertButton_clicked()
{
    int row = ui->listView->currentIndex().row();
    model->insertRows(row,1);
    editRow(row);
}

void StringListDialog::editRow(int row)
{
    QModelIndex index = model->index(row);
    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}

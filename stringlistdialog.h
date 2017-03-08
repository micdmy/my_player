#ifndef STRINGLISTDIALOG_H
#define STRINGLISTDIALOG_H

#include <QDialog>
#include <QStringListModel>
namespace Ui {
class StringlIstDialog;
}

class StringListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StringListDialog(QStringListModel * stringListModel, const QString &title, const QString &info, QWidget *parent = 0);
    ~StringListDialog();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_removeButton_clicked();

    void on_insertButton_clicked();

private:
    Ui::StringlIstDialog *ui;
    QStringListModel * model;
    void editRow(int row);
};

#endif // STRINGLISTDIALOG_H

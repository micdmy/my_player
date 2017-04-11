#ifndef SEARCHFRAME_H
#define SEARCHFRAME_H

#include <QFrame>
#include <QKeyEvent>

namespace Ui {
class SearchFrame;
}

class SearchFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SearchFrame(QWidget *parent = 0);
    ~SearchFrame();
    void addWidget(QWidget * orphantWidget);
private slots:
    void on_lineEdit_textEdited(const QString &newText);

private:
    Ui::SearchFrame *ui;
    void keyPressEvent(QKeyEvent *event);
protected:
    QWidget * orphant;
signals:
    void searchTextChanged(const QString &);
};

#endif // SEARCHFRAME_H

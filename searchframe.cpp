#include "searchframe.h"
#include "ui_searchframe.h"

SearchFrame::SearchFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SearchFrame)
{
    ui->setupUi(this);
    ui->lineEdit->setFocusPolicy(Qt::ClickFocus);
    ui->lineEdit->setVisible(false);
    setFocusPolicy(Qt::StrongFocus); //sets keyboard focus for keyPressEvent(QKeyEvent *event)

}

SearchFrame::~SearchFrame()
{
    delete ui;
}

void SearchFrame::addWidget(QWidget *orphantWidget)
{
    orphant = orphantWidget;
    orphant->setParent(this);
    orphant->setFocusPolicy(Qt::NoFocus);
    ui->verticalLayout->addWidget(orphant);
}

void SearchFrame::keyPressEvent(QKeyEvent *event)
{
    QString key;
    key = (char)(event->key());
    QRegExp re("^[\\.\\+'&?!=/,a-zA-Z0-9_-]*$"); //match Alphanumerical and .+'&?!=/,_-
    if(re.exactMatch(key)) {
        ui->lineEdit->setVisible(true); //does not matter if it is aleady visible, set it anyway
        ui->lineEdit->setText(ui->lineEdit->text() + key); //add pressed letter to search lineEdit
        ui->lineEdit->setFocus(); //next letter will be put to lineEdit directly via on_lineEdit_textEdited slot
        emit searchTextChanged(ui->lineEdit->text()); //signal to other objects
    }
}

void SearchFrame::on_lineEdit_textEdited(const QString &newText)
{
    if(newText.isEmpty()) {
        //hide search, text was 'backspaced'
        ui->lineEdit->setVisible(false);
        setFocus(); //return focus to 'this' widget
    } else {
        //change letters to uppercase if not empty
        ui->lineEdit->setText(newText.toUpper());
    }
    emit searchTextChanged(ui->lineEdit->text()); //signal to other objects
}

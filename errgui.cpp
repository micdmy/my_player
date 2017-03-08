#include "errgui.h"



void ErrGui::error(QString message)
{
    QMessageBox box;
    box.setText(message);
    box.exec();
}

void ErrGui::error(QFile & file)
{
    error(file.errorString());
}

bool ErrGui::ask(QString question)
{
    QMessageBox box;
    box.setText(question);
    return box.exec();
}

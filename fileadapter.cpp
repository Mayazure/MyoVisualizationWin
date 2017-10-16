#include "fileadapter.h"
#include <QFile>
#include <QTextStream>

FileAdapter::FileAdapter(Form *form)
{
    this->form = form;
}

void FileAdapter::load(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream *out = new QTextStream(&file);
    QStringList tempOption = out->readAll().split("\n");
    for(int i=1;i<tempOption.count();i++){
        QStringList temp = tempOption.at(i).split(",");
        this->form->realtimeDataSlot(8, 0,
                                     temp.at(2).toInt(),
                                     temp.at(3).toInt(),
                                     temp.at(4).toInt(),
                                     temp.at(5).toInt(),
                                     temp.at(6).toInt(),
                                     temp.at(7).toInt(),
                                     temp.at(8).toInt(),
                                     temp.at(9).toInt());
    }
}

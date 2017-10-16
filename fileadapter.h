#ifndef FILEADAPTER_H
#define FILEADAPTER_H

#include <QString>
#include "graphwindow.h"

class Form;

class FileAdapter
{
public:
    FileAdapter(Form *form);
    void load(QString path);

private:
    Form *form;

};

#endif // FILEADAPTER_H

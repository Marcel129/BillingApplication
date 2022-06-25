#ifndef FV_H
#define FV_H

#include <QObject>
#include <fvdata.h>
#include <fvtemplate.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

class FV : public QObject
{
    Q_OBJECT
    FVTemplate FV_temp;
    bool is_inited;

    void createLatexFV();
    void createPDFFV();

public:
    explicit FV(QObject *parent = nullptr);
    bool init();

public slots:
    void createFV();

signals:

};

#endif // FV_H

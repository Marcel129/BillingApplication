#ifndef FV_H
#define FV_H

#include <QObject>
#include "fvdata.h"
#include "fvtemplate.h"
#include "config.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

class FV : public QObject
{
    Q_OBJECT
    FVTemplate FV_temp;
    FVData FV_data;

    bool is_inited;
    bool addReciper;

    void createLatexFV();
    void createPDFFV();

public:
    explicit FV(QObject *parent = nullptr);
    bool init();
    void addRecord(const FVRecord & record);
    void setAddingReciper(bool value);
    void insertValuesIntoKeywords();

public slots:
    void createFV();

signals:

};


#endif // FV_H

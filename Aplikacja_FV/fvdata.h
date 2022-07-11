#ifndef FVDATA_H
#define FVDATA_H

#include <QObject>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "config.h"

#define MIN_RABAT_VALUE 0
#define MAX_RABAT_VALUE 100
#define MIN_PRICE_VALUE 0
#define MAX_PRICE_VALUE 100000

const std::string FVRecord_productName_DefValue = "26/06/6418";
const std::string FVRecord_PKWiU_DefValue = "26/06/6418";
const std::string FVRecord_unit_DefValue = "szt.";

const std::string FVTableElemSeparator_DefValue = " & ";
const std::string FVTable_EOL_DefValue = " \\\\ \\hline";

struct FVRecord
{
    std::string productName;
    std::string PKWiU;
    std::string unit;
    float rabat;
    unsigned int quantity;
    float price;
    float totalValue;

    FVRecord(std::string,unsigned int,float,float,std::string,std::string);
};

class FVData : public QObject
{
    Q_OBJECT
    std::vector<FVRecord> records;
public:
    explicit FVData(QObject *parent = nullptr);
    void addToRecords(const FVRecord &p);
        const std::vector<FVRecord>& getRecords() {return records;}

signals:

};

std::ostream& operator<<(std::ostream& os, const FVRecord& rec);

#endif // FVDATA_H

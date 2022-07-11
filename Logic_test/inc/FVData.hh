#ifndef FVData_HH
#define FVData_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "config.hh"

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


class FVData
{
    std::vector<FVRecord> records;

public:
    void addToRecords(const FVRecord &p);
    const std::vector<FVRecord>& getRecords() {return records;}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const FVRecord& rec){
    os << rec.productName << FVTableElemSeparator_DefValue <<
          rec.rabat << "\\% " << FVTableElemSeparator_DefValue <<
          rec.PKWiU << FVTableElemSeparator_DefValue <<
          rec.quantity << FVTableElemSeparator_DefValue <<
          rec.unit << FVTableElemSeparator_DefValue <<
          rec.price << FVTableElemSeparator_DefValue <<
          rec.totalValue << FVTable_EOL_DefValue;

    return os;
}

FVRecord::FVRecord(std::string pn,
                   unsigned int q,
                   float p,
                   float r = 0,
                   std::string u = FVRecord_unit_DefValue,
                   std::string pk = FVRecord_PKWiU_DefValue)
{
    productName = pn;
    PKWiU = pk;
    unit = u;
    r >= MIN_RABAT_VALUE &&r <= MAX_RABAT_VALUE ? rabat = r : r < MIN_RABAT_VALUE ? rabat = MIN_RABAT_VALUE
                                                                                  : rabat = MAX_RABAT_VALUE;
    quantity = q;
    //price = p;
        p >= MIN_PRICE_VALUE &&p <= MAX_PRICE_VALUE ? price = p : p < MIN_PRICE_VALUE ? price = MIN_PRICE_VALUE
                                                                                  : price = MAX_PRICE_VALUE;
    totalValue = float(quantity)*price - float(quantity)*price*rabat/100.0;
}

void FVData::addToRecords(const FVRecord &p)
{
    records.push_back(p);
}

#endif
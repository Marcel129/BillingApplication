#include "fvdata.h"

FVData::FVData(QObject *parent)
    : QObject{parent}
{

}

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

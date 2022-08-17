#ifndef INVOICETEMPLATE_H
#define INVOICETEMPLATE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDate>

#include <config.h>
#include <database.h>
#include <invoicerecord.h>

const QString spacer("%-||-||-");
const QString EOFString("%-||-||--||-||--||-||-");
const QString FVLDefaultFileName("FakturaVAT");
const QString FVLTemplateDefaultFileName("Invoice_template.tex");
const QString FVLDefaultFileName_Latex(FVLDefaultFileName + ".tex");

const QVector<QString> filesToDelete =
{
    FVLDefaultFileName + ".log",
    FVLDefaultFileName + ".tex",
    FVLDefaultFileName + ".aux"
};

enum FVTemplatePart
{
    Prembula,
    Header,
    SellerBuyerDataBeginning,
    Reciper,
    SellerBuyerDataEnding,
    InvoiceNumberText,
    MainTableBegining,
    MainTableEnding,
    MainTableSummmary,
    PaymentData,
    Ending
};


class FVTemplate : public QObject
{
    Q_OBJECT
    QStringList parts;
    QStringList sourceParts;
    bool is_loaded;

public:
    explicit FVTemplate(QObject *parent = nullptr);
    QString getPart(FVTemplatePart a);
    QStringList & getAllParts();
    bool load();

    void insertValuesIntoKeywords(
            seller Seller,
            customer buyer,
            reciper recip,
            QString paymentMethod,
            QString billingPalce,
            QDate billingDate,
            QDate saleDate,
            QString paymentDeadline);

    void refresh();

public slots:

signals:

};

#endif // INVOICETEMPLATE_H

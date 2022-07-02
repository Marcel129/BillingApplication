#ifndef FVTEMPLATE_H
#define FVTEMPLATE_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

const std::string FVpath = "D:\\SzkolkaRoslinOpatow\\Aplikacja\\";
const std::string FVTemplateDefaultPath = "D:\\SzkolkaRoslinOpatow\\Aplikacja\\External_resources\\";
const std::string spacer = "%-||-||-";
const std::string EOFString = "%-||-||--||-||--||-||-";
const std::string FVLDefaultFileName = "FakturaVAT";
const std::string FVLTemplateDefaultFileName = "Faktura_template.tex";
const std::string FVLDefaultFileName_Latex = FVLDefaultFileName + ".tex";
const std::vector<std::string> filesToDelete = {FVLDefaultFileName + ".log",
                                      FVLDefaultFileName + ".tex",
                                      FVLDefaultFileName + ".aux"};

enum FVTemplatePart
{
    Prembula,
    BeginingMainTable,
    EndingMainTable,
    Ending
};

class FVTemplate : public QObject
{
    Q_OBJECT
    std::vector<std::string> parts;
    bool is_loaded;

public:
    explicit FVTemplate(QObject *parent = nullptr);
    std::string getPart(FVTemplatePart a);
    bool load(const std::string path = FVpath);

public slots:


signals:

};

#endif // FVTEMPLATE_H

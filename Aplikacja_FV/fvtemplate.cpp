#include "fvtemplate.h"

FVTemplate::FVTemplate(QObject *parent)
    : QObject{parent}
{

}

std::string FVTemplate::getPart(FVTemplatePart a)
{
    return parts.at(a);
};

bool FVTemplate::load(const std::string path)
    {
    std::fstream temp;
    std::string tmp_text = "";

    temp.open(FVTemplateDefaultPath + FVLTemplateDefaultFileName, std::ios::in);
    if (!temp)
    {
        qDebug() << "Unable to open template file";
        exit(1);
    }

    unsigned int index = 0;

    do
    {
        tmp_text = "";
        parts.push_back(tmp_text);
        do
        {
            getline(temp, tmp_text);

            if (tmp_text != spacer && tmp_text != EOFString)
            {
                parts[index] += (tmp_text + "\n");
            }
        } while (tmp_text != spacer && tmp_text != EOFString);

        index++;
    } while (tmp_text != EOFString);

    temp.close();

    is_loaded = (Ending == (index - 1));

    return is_loaded;
    };


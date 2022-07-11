#ifndef CONFIG_HH
#define CONFIG_HH

#include "iostream"
#include "vector"
#include "string"

const std::string resourcesPath = "D:\\SzkolkaRoslinOpatow\\Aplikacja\\External_resources\\";
const std::string FVpath = "D:\\SzkolkaRoslinOpatow\\Aplikacja\\";
const std::string CSVSplitChar = ";";
const char CommentChar = '#';
const std::string EOFDataString = "!EndOfData;;;;";


std::vector<std::string> splitString(std::string str, std::string sep)
{
    std::vector<std::string> result;
    std::string tmp_str = str;
    int pos1 = 0, pos2 = 0;

    do
    {
        if ((pos2 = str.find(sep)) != std::string::npos)
        {
            tmp_str = str.substr(0, pos2);
            str = str.substr(pos2 + 1);
            pos1 = pos2;
            result.push_back(tmp_str);
        }
        else
        {
            //last element, when separator is not found
            result.push_back(str);
        }

    } while (pos2 != std::string::npos);

    return result;
}

#endif
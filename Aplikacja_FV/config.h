#ifndef CONFIG_H
#define CONFIG_H

#include "iostream"
#include "vector"
#include "string"

const std::string resourcesPath = "D:\\SzkolkaRoslinOpatow\\Aplikacja\\External_resources\\";
const std::string FVpath = "D:\\SzkolkaRoslinOpatow\\Aplikacja\\";
const std::string CSVSplitChar = ";";
const char CommentChar = '#';
const std::string EOFDataString = "!EndOfData;;;;";


std::vector<std::string> splitString(std::string str, std::string sep);

#endif // CONFIG_H

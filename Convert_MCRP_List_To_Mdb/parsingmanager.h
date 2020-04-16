#ifndef PARSINGMANAGER_H
#define PARSINGMANAGER_H

#include <fstream>
#include <parameter.h>


class ParsingManager
{
public:
    ParsingManager();
    ParsingManager(QString txtFileName);
    ~ParsingManager();

    bool isCorrectFile;
    std::string errorName;

    int startParsing();

private:
    std::string currentSection;
    std::ifstream in;
    std::vector<Parameter> v_Par;

    std::string findSection(std::string currentLine);
};

#endif // PARSINGMANAGER_H

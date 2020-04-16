#include "parsingmanager.h"

const std::string analogSectionName = "АНАЛОГИ";
const std::string RKSectionName = "РАЗОВЫЕ КОМАНДЫ";
const std::string DDKSectionName = "ДВОИЧНО-ДЕСЯТИЧНЫЙ КОД";
const std::string CalcSectionName = "РАСЧЕТНЫЕ";

ParsingManager::ParsingManager()
{

}

ParsingManager::ParsingManager(QString std::string txtFileName)
    :errorName("no error")
    ,isCorrectFile(true)
    ,currentSection(noSection)
{

    // check opening file
    if(txtFileName == "")
    {
        errorName = "File isn't exist. Select correct file";
        isCorrectFile = false;
        return;
    }

    in.open(txtFileName.toStdString().c_str());

    //check condition file
    if( !in)
    {
        errorName = "Error opennig file";
        isCorrectFile = false;
        return;
    }
}

ParsingManager::~ParsingManager()
{
    in.close();
}

int ParsingManager::startParsing()
{    
    std::string curLine("");
    while(std::getline(in, curLine))
    {
        // find of of const string АНАЛОГИ, РАСЧЕТНЫЕ КОМАНДЫ
        currentSection = findSection(curLine);
        switch (currentSection) {
        case analogSectionName:
        {
            v_Par.push_back(AnalogCMR::AnalogCMR(in));
            break;
        }
        case RKSectionName:
        {
            v_Par.push_back(RK::RK(in));
            break;
        }
        default:
            break;
        }
    }
    return v_Par.size();
}

std::string ParsingManager::findSection(std::string currentLine)
{
    switch(currentLine)
    {
    case analogSectionName: return analogSectionName;
    case RKSectionName: return RKSectionName;
    case DDKSectionName: return DDKSectionName;
    case CalcSectionName: return CalcSectionName;
    default: return currentSection;
    }
}



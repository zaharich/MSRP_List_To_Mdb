
#include "parameter.h"



//Gт [т] - Суммарный запас топлива [003978]
//  Датчик: КУТЦ
//  Занимает разряды: 1 - 12
//  Адреса: 754
//  Тип расчета: цена младшего разряда
//  Цена младшего разряда: 0.064

//Hб_абс_ИСРП [м] - Высота барометрическая абсолютная QNE (ИСРП) [000026,000027] ЦМР=0.125м
//  Датчик: ИСРП
//  Занимает разряды: 3 - 12
//  Параметр со знаком
//  Адреса: 209 1233
//  Тип расчета: двойное слово

//Vmin_доп [км/ч] - Минимально-допустимая приборная скорость [000128]
//  Датчик: ПКРиус
//  Занимает разряды: 1 - 12
//  Адреса: 332
//  Тип расчета: градуировки
//  Физика: 290. 570.
//  Код прямой  : 0 2047
//  Код обратный: 0 2047
//  Масштабный коэффициент: 1.

AnalogCMR::AnalogCMR(std::ifstream& in)
{
    std::string line;
    // ищем первую не нулевую строку
    while( (std::getline(in, line)) && (line != ""))
    {
        // если строка содержит символ "[" - значит это первая строка блока описания параметра
        if(std::string::npos != line.find("["))
        {
            // rus_ident
            size_t nOpenBracket = line.find("[");
            rus_ident = line.substr(0, nOpenBracket-1);

            // unit_measure
            size_t nClosedBracket = line.find("]");
            unit_measure = line.substr(nOpenBracket+1, nClosedBracket);

            // name
            size_t nDash = line.find("-");
            size_t n2OpenBracket = line.find("[", nClosedBracket);
            name = line.substr(nDash+2, n2OpenBracket-1);

            // numbet_param and check double word
            size_t nComma = line.find(",", n2OpenBracket);
            if(nComma == std::string::npos)
            {
                // once word
                size_t n2ClosedBracket = line.find("]", n2OpenBracket);
                number_param = line.substr(n2OpenBracket+1, n2ClosedBracket-1);
            }
            else
            {
                //double word
                number_param = line.substr(n2OpenBracket+1, nComma-1);
                size_t n2ClosedBracket = line.find("]", n2OpenBracket);
                number_param2 = line.substr(nComma+1, n2ClosedBracket-1);
            }
        }
        else
        {
            //первая строчка не содержит "[" - это ошибка
        }

        // read sensor line
        std::getline(in, line);
        sensor = readSensorLine(line);

        // read digits line
        std::getline(in, line);
        first_digit = readFirstDigit(line);
        second_digit = readSecondDigit(line);


    } //while
}


std::string Parameter::readSensorLine(std::string& line)    // todo большие и маленькие буквы
{
    if(line.find("Датчик") != std::string::npos)
    {
        size_t n = line.find(":");
        if(n != std::string::npos)
            return line.substr(n+1);
    }
    return std::string("-");
}

std::string Parameter::readFirstDigit(std::string& line)
{
    if( (line.find("разряды")!=std::string::npos) || (line.find("Разряды")!=std::string::npos) )
    {
        size_t nColon = line.find(":");
        size_t nDash = line.find("-");

        if(nColon != std::string::npos)
            // two digits
            if(nDash != std::string::npos)
                return line.substr(nColon+1, nDash-1);
            // one digit
            else
                return line.substr(Colon+1);
    }
    return std::string("-1");
}

std::string Parameter::readSecondDigit()

/* Класс параметр содержит в себе все данные параметра МСРП
 * содержит функции работы с данными
 * содержит функции парсинга строк исходного файла списка
 */

#ifndef PARAMETER_H
#define PARAMETER_H


class Parameter
{
public:
   virtual void writeToDB() = 0;
   virtual int read(std::ifstream in) = 0;

   std::string rus_ident;
   std::string name;
   std::string number_param;
   std::string sensor;
   std::string first_digit;
   std::string adress;
};


class RK: public Parameter
{
public:
    RK() {};
    RK(std::ifstream in);
    void writeToDB();
    int read(std::ifstream in);
};


class AnalogCMR: public Parameter
{
public:
    AnalogCMR() {};
    AnalogCMR(std::ifstream in);
    void writeToDB();
    int read(std::ifstream in);

    std::string unit_measure;
    std::string second_digit;
    std::string sign;
    std::string price;
};


class AnalogTar: public Parameter
{
public:
    AnalogTar() {};

    std::string unit_measure;
    std::string second_digit;
    std::string sign;
    std::string fizika;
    int array[];
    float coef;
};


#endif // PARAMETER_H

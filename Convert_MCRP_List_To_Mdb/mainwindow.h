#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <fstream>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    std::ifstream in;

    struct par{
        // тип параметра: "0"-значение младшего разряда или тарировка, "1"-разовая команда
        bool type_par;

        // до первого символа [
        std::string rus_ident;
        // до первого символа ]
        std::string unit_measure;
        // после - , до первого символа [
        std::string name;
        // до символа , (тогда двойное слово); или до символа ]
        std::string number_param;
        // до символа ] (только при условии, что двойное слово)
        std::string number_param2;

        // после подстроки "Датчик: "
        std::string sensor;
        // после подстроки "Занимает разряды: "
        std::string begin_end_digit;
        // если существует строка "Параметр со знаком"
        std::string sign;
        // Первый адрес после подстроки "Адреса:"
        std::string adress;
        // Тип расчета
        std::string type;
    };
    std::ofstream out;

    std::vector<par> par_array;

};

#endif // MAINWINDOW_H

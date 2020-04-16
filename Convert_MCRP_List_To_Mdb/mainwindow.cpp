#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"

#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>

#include <parsingmanager.h>

#define testPrintOutFile 0

static const std::string str_analog = "АНАЛОГИ.";
static const std::string str_rk = "РАЗОВЫЕ КОМАНДЫ.";
static const std::string str_DDK = "ДВОИЧНО-ДЕСЯТИЧНЫЙ КОД.";
static const std::string str_calc = "РАСЧЕТНЫЕ.";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // open select dialog source file
    QString txtFileName = QFileDialog::getOpenFileName(0, "Select txt file", "", "");
    ParsingManager parser(txtFileName);
    if( !parser.isCorrectFile)
    {
        ui->lineEdit->setText(QString::fromStdString(parser.error_name));
        return;
    }

    // parsing strings
    std::string line;
    int nStruct = 0;
    while(std::getline(in, line))
    {
        par p;
        // если строка содержит символ "[" - значит это первая строка блока описания параметра
        if(std::string::npos != line.find("["))
        {
            size_t n = line.find("[");
            size_t nTire = line.find("-");

            // если параметр с ЦМР или Тар
            // Gт [т] - Суммарный запас топлива [003978]
            if(nTire > n)
            {
                // type_par
                p.type_par = 0;

                // rus_ident
                p.rus_ident = line.substr(0, n-2);

                // unit_measure
                size_t n2 = line.find("]");
                p.unit_measure = line.substr(n+1, n2-1);

                // name
                int n3 = line.find("[");
                p.name = line.substr(nTire+2, n3-2);

                // check double word
                size_t n4 = line.find(",");
                if(n4 == std::string::npos)
                {
                    // once word
                    size_t n41 = line.find("]");
                    p.number_param = line.substr(n3+1, n41);
                }
                else
                {
                    //double word
                    p.number_param = line.substr(n3+1, n4-1);
                    int n42 = line.find("]");
                    p.number_param2 = line.substr(n4+1, n42-1);
                }
            }
            // если параметр РК
            // О_БПК25 - Отказ канала БПК 25
            else
            {
                // type par
                p.type_par = 1;

                // rus_ident
                p.rus_ident = line.substr(0, nTire-2);

                //name
                p.name = line.substr(nTire+2, n-1);

                // number_param
                size_t m = line.find("]");
                p.number_param = line.substr(n+1, m-1);
            }

            // second string
            std::getline(in, line);
            if(std::string::npos != line.find("Датчик"))
            {
                n = line.find(":");
                p.unit_measure = line.substr(n+2);
            }

            par_array.push_back(p);
            nStruct++;
        }
    }
    ui->lineEdit_2->setText(QString::number(nStruct));
    in.close();


    // print vector of struct in file
#if testPrintOutFile

    QString txtOutFileName = QFileDialog::getOpenFileName(0, "Select Out txt file", "", "");
    if(txtOutFileName == "")
    {
        ui->lineEdit->setText("Select corrent outfile");
        return;
    }

    // check condition file
    out.open(txtOutFileName.toStdString().c_str());
    if( !out)
    {
        ui->lineEdit_2->setText("Error of opennig outfile");
        return;
    }

    for(std::vector<par>::iterator b = par_array.begin(), e = par_array.end(); b != e; ++b)
    {
        out << "Rus_ident: " << b->rus_ident << std::endl;
        out << std::endl;
    }
#endif

}



void MainWindow::on_pushButton_2_clicked()
{
    QString mdbFileName = QFileDialog::getOpenFileName(0, "Select database file(*.mdb)", "", "");

    // check selecting file
    if(mdbFileName == "")
    {
        ui->lineEdit_3->setText("File is not select");
        return;
    }

    // connect to DB
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)}; DSN=''; DBQ=" + mdbFileName);
    if(!db.open())
    {
        ui->lineEdit_3->setText(db.lastError().text());
        return;
    }
    else
        ui->lineEdit_3->setText(mdbFileName + " - Connect!");

    // SQL exec
    QSqlQuery* query = new QSqlQuery(db);
    query->prepare("INSERT INTO `00_ТАБЛИЦА ПАРАМЕТРОВ` (Идент_RUS, Замер) VALUES ('test', '12');");
    query->exec();

    // write vector to bd
}

/*s = "INSERT INTO `00_ТАБЛИЦА ПАРАМЕТРОВ` (";
for(std::map<String, String>::iterator b = mdb_doc_map.begin(), e = mdb_doc_map.end(); b != e; ++b)
    s += (*b).first + ",";
s = s.SubString(0, s.Length() - 1);

s += ") VALUES(";
for(std::map<String, String>::iterator b = mdb_doc_map.begin(), e = mdb_doc_map.end(); b != e; ++b)
    s += "'" + StringGrid1->Cells[ doc_column_map[mdb_doc_map[(*b).first] ] ][i] + "'" + ",";
s = s.SubString(0, s.Length() - 1);
s += ")";*/

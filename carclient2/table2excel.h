#ifndef TABLE2EXCEL_H
#define TABLE2EXCEL_H
#include <QString>
#include <QList>
#include <QFile>
#include <QTextEdit>
#include <QTableWidget>
#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>
#include <QVariant>
#include <QTextCodec>
#include <QMessageBox>

typedef unsigned int UINT;
class Table2Excel
{
public:
    Table2Excel();
    Table2Excel(QString xlsFile);
    ~Table2Excel();
    bool Open(UINT nSheet = 1, bool visible = false);//打开xls文件
        bool Open(QString xlsFile, UINT nSheet = 1, bool visible = false);
        void Save();                //保存xls报表
        void Close();               //关闭xls报表

        bool SaveDataFrTable(QTableWidget *tableWidget); //保存数据到xls
        bool ReadDataToTable(QTableWidget *tableWidget); //从xls读取数据到ui

        QVariant GetCellData(UINT row, UINT column);                //获取指定单元数据
        bool     SetCellData(UINT row, UINT column, QVariant data); //修改指定单元数据

        UINT GetRowCount()const;
        UINT GetColumnCount()const;

        bool IsOpen();
        bool IsValid();
protected:
    void Clear();
private:
    QAxObject *pExcel;      //指向整个excel应用程序
    QAxObject *pWorkbooks;  //指向工作簿集,excel有很多工作簿
    QAxObject *pWorkbook;   //指向sXlsFile对应的工作簿
    QAxObject *pWorksheet;  //指向工作簿中的某个sheet表单

    QString   sXlsFile;     //xls文件路径
    UINT      nCurrSheet;   //当前打开的第几个sheet
    bool      bIsVisible;   //excel是否可见
    int       nRowCount;    //行数
    int       nColumnCount; //列数
    int       nStartRow;    //开始有数据的行下标值
    int       nStartColumn; //开始有数据的列下标值

    bool      bIsOpen;      //是否已打开
    bool      bIsValid;     //是否有效
    bool      bIsANewFile;  //是否是一个新建xls文件，用来区分打开的excel是已存在文件还是有本类新建的
    bool      bIsSaveAlready;//防止重复保存

};

#endif // TABLE2EXCEL_H

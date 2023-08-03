#include "bank.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication  a(argc, argv);

    // BankAccount nesnesini oluştur
    Bank account1Ref("Irem Mardinoglu", 10000.0);
    Bank account2Ref("Jane Smith", 2000.0);
    account1Ref.show();
    account2Ref.show();
    return a.exec();
}



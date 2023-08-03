#ifndef BANK_H
#define BANK_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Bank; }
QT_END_NAMESPACE

class Bank : public QMainWindow
{
    Q_OBJECT

public:
    Bank(const QString name, double balance, QWidget* parent = nullptr);
    ~Bank();
    Bank operator+(const Bank& other) const;
    Bank operator-(double amount);
    Bank& operator=(const Bank& other);
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;


private:
    Ui::Bank* ui; // Use a pointer to the UI class instead
    QString m_name;
    double m_balance;
    QString m_password1 = "1234";
    QString m_password2 = "2345";
    Bank& account1Ref; // Reference to account1
    Bank& account2Ref; // Reference to account2

private slots:
    void on_PasswordButton_clicked();
    void on_depositButton_clicked();
    void on_withdrawButton_clicked();
    void on_TransferButton_clicked();

};
#endif // BANK_H


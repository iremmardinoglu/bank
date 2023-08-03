#include "bank.h"
#include "ui_bank.h"
#include <QInputDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <QDebug>


 Bank::Bank(const QString name, double balance, QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::Bank),
    m_name(name),
    m_balance(balance),
    account1Ref(account1Ref),
    account2Ref(account2Ref)
{
    ui->setupUi(this);
    // ... (other parts of the constructor remain unchanged)
}

Bank::~Bank()
{
    delete ui;
}

Bank Bank::operator+(const Bank& other) const
{
    double totalBalance = m_balance + other.m_balance;
    return Bank(m_name, totalBalance);
}

// Overload - operator to implement transfer from one account to another

Bank Bank::operator-(double amount)
{
    if (amount > 0 && m_balance >= amount)
    {
        m_balance -= amount;
        return Bank(m_name, amount); // Return a Bank object with the transferred amount
    }
    else
    {
        return Bank(m_name, 0.0); // Return a dummy account with 0 balance
    }
}


// Custom copy assignment operator
Bank& Bank::operator=(const Bank& other)
{
    if (this != &other) // Avoid self-assignment
    {
        m_name = other.m_name;
        m_balance = other.m_balance;
        // You may need to copy other data members if your class has additional ones.
    }
    return *this;
}


void Bank::deposit(double amount)
{
    if (amount > 0)
    {
        m_balance += amount;
    }
}

bool Bank::withdraw(double amount)
{
    if (amount > 0 && m_balance >= amount)
    {
        m_balance -= amount;
        return true;
    }
    return false;
}

double Bank::getBalance() const
{
    return m_balance;
}

void Bank::on_depositButton_clicked()
{
    bool ok;
    QString amountText = QInputDialog::getText(this, tr("Deposit"),tr("Enter deposit amount:"), QLineEdit::Normal,"", &ok);
    if (ok && !amountText.isEmpty()) {
        double amount = amountText.toDouble();
        deposit(amount);
        ui->balanceLabel->setText("Current balance: " + QString::number(m_balance));
    }
}

void Bank::on_withdrawButton_clicked()
{
    bool ok;
    QString amountText = QInputDialog::getText(this, tr("Withdraw"),tr("Enter withdrawal amount:"), QLineEdit::Normal,"", &ok);
    if (ok && !amountText.isEmpty()) {
        double amount = amountText.toDouble();
        bool success = withdraw(amount);
        if (!success) {
            QMessageBox::warning(this, tr("Withdrawal Failed"), tr("Insufficient balance in the account."));
        } else {
            ui->balanceLabel->setText("Current balance: " + QString::number(m_balance));
        }
    }
}

void Bank::on_PasswordButton_clicked()
{
    QString enteredPassword = ui->lineEdit->text();
    if (enteredPassword == m_password1)
    {
        // Password is correct, show the balance
        ui->balanceLabel->setText("Current balance: " + QString::number(m_balance));
        ui->balanceLabel->setVisible(true);
    }
    else
    {
        // Incorrect password, hide the balance
        ui->balanceLabel->setVisible(false);
    }
}


void Bank::on_TransferButton_clicked()
{
    bool ok;
    QString amountText = QInputDialog::getText(this, tr("Transfer"), tr("Enter transfer amount:"), QLineEdit::Normal, "", &ok);
    if (ok && !amountText.isEmpty()) {
        double amount = amountText.toDouble();

        // Get the destination account's name from the user
        QString destinationAccountName = QInputDialog::getText(this, tr("Transfer"), tr("Enter destination account name:"), QLineEdit::Normal, "", &ok);
        if (ok && !destinationAccountName.isEmpty()) {
            // Search for the destination account
            // You may need a data structure to store multiple accounts and search for the destination account here.
            // For the sake of simplicity, we will assume there are two predefined accounts (account1 and account2).

            Bank* destinationAccount = nullptr;
            if (destinationAccountName == "Irem Mardinoglu") {
                destinationAccount = &account1Ref;
            } else if (destinationAccountName == "Jane Smith") {
                destinationAccount = &account2Ref;
            } else {
                QMessageBox::warning(this, tr("Account Not Found"), tr("Destination account not found. Please enter a valid account name."));
                return;
            }

            // Perform the transfer

            qDebug() << amount;
            qDebug() << getBalance();

            if (amount <= getBalance())
            {
                Bank transferResult = *this - amount;
                QMessageBox::information(this, tr("Transfer Successful"), tr("Transfer successful!"));
                ui->balanceLabel->setText("Current balance: " + QString::number(m_balance));
                return;
            }
            else
            {
                QMessageBox::warning(this, tr("Transfer Failed"), tr("Transfer failed! Insufficient balance in the source account."));
            }

        }
    }
}

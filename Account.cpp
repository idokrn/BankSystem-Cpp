#include "Account.h"

Account::Account() {
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    m_persons = nullptr;
    m_totalPersons = 0;
    m_balance = 0;

    // Set Account number
    static int account_number = 0;
    m_accountNumber = account_number;
    account_number += 3;

}

Account::Account(const Person &person, double balance) {
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    m_persons = new Person*[1];
    m_persons[0] = new Person(person);
    m_totalPersons = 1;
    m_balance = balance;

    // Set Account number
    static int account_number = 1;
    m_accountNumber = account_number;
    account_number += 3;
}

Account::Account(Person **persons, int count, double balance) {
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    SetPersons(persons, count);
    SetBalance(balance);

    // Set Account number
    static int account_number = 2;
    m_accountNumber = account_number;
    account_number += 3;
}

Account::Account(const Account &other) {
    m_numberOfTransaction = other.m_numberOfTransaction;
    m_transactionList = new Transaction*[m_numberOfTransaction];
    for (int i = 0; i < m_numberOfTransaction; i++){
        m_transactionList[i] = new Transaction(*other.m_transactionList[i]);
    }

    m_totalPersons = other.GetTotalPersons();
    m_persons = new Person*[m_totalPersons];
    for(int i = 0; i < m_totalPersons; i++){
        m_persons[i] = new Person(*other.m_persons[i]);
    }

    m_accountNumber = other.GetAccountNumber();
    m_balance = other.GetBalance();
}

Account::~Account() {
    clearPersons();
    clearTransactions();
}


void Account::SetPersons(Person **persons, int count) {
    m_persons = persons;
    m_totalPersons = count;
}

void Account::SetAccountNumber(int number) {
    m_accountNumber = number;
}

void Account::SetBalance(double balance) {
    m_balance = balance;
}

void Account::SetTransactions(Transaction **newTransaction, int count) {
    m_transactionList = newTransaction;
    m_numberOfTransaction = count;
}

Transaction **Account::GetTransactions() {
    return m_transactionList;
}

int Account::GetNumOfTransactions() {
    return m_numberOfTransaction;
}

Person **Account::GetPersons() const {
    return m_persons;
}

int Account::GetTotalPersons() const {
    return  m_totalPersons;
}

int Account::GetAccountNumber() const {
    return m_accountNumber;
}

double Account::GetBalance() const {
    return m_balance;
}

void Account::AddTransaction(const Transaction &newTransaction) {
    auto src = newTransaction.GetSource();
    auto newSrcTranList = new Transaction*[src->GetNumOfTransactions()+1];
    for(int i = 0; i < src->GetNumOfTransactions(); i++){
        newSrcTranList[i] = src->GetTransactions()[i];
    }
    newSrcTranList[src->GetNumOfTransactions()] = new Transaction(newTransaction);
    src->SetTransactions(newSrcTranList,src->GetNumOfTransactions()+1);

    if(src->GetAccountNumber() != newTransaction.GetDes()->GetAccountNumber()){
        auto des = newTransaction.GetDes();
        auto newDesTranList = new Transaction*[des->GetNumOfTransactions()+1];
        for(int i = 0; i < des->GetNumOfTransactions(); i++){
            newDesTranList[i] = des->GetTransactions()[i];
        }
        newDesTranList[src->GetNumOfTransactions()] = new Transaction(newTransaction);
        des->SetTransactions(newDesTranList,des->GetNumOfTransactions()+1);
        des->SetBalance(des->GetBalance() + newTransaction.GetAmount());
        src->SetBalance(src->GetBalance() - newTransaction.GetAmount());
    }
}

void Account::Withdraw(double amount, const char *date) {
    Transaction newTran(this,this,amount,date);
    AddTransaction(newTran);
    m_balance -= amount;
}

void Account::Deposit(double amount, const char *date) {
    Transaction newTran(this,this,amount,date);
    AddTransaction(newTran);
    m_balance += amount;
}

void Account::AddPerson(const Person &newPerson, double amount) {
    for(int i = 0; i < m_totalPersons; i++){
        if(m_persons[i]->GetId() == newPerson.GetId()){
            return;
        }
    }

    auto newPersonList = new Person*[m_totalPersons+1];
    for(int i = 0; i < m_totalPersons; i++){
        newPersonList[i] = m_persons[i];
    }
    newPersonList[m_totalPersons] = new Person(newPerson);
    SetPersons(newPersonList,m_totalPersons + 1);
    m_balance += amount;
}

void Account::DeletePerson(const Person &oldPerson) {
    bool flag = false;
    for(int i = 0; i < m_totalPersons; i++){
        if(m_persons[i]->GetId() == oldPerson.GetId()){
            delete m_persons[i];
            m_persons[i] = nullptr;
            flag = true;
        }
        if(flag){
            m_persons[i] = m_persons[i+1];
        }
    }
    if(flag){
        m_totalPersons -= 1;
    }
    if(!m_totalPersons){
        clearPersons();
    }

}

void Account::clearTransactions() {
    for(int i = 0; i < m_numberOfTransaction; i++){
        delete m_transactionList[i];
    }
    delete[] m_transactionList;
    m_numberOfTransaction = 0;
    m_transactionList = nullptr;
}

void Account::clearPersons() {
    for(int i = 0; i<m_totalPersons; i++){
        delete m_persons[i];
    }
    delete[] m_persons;
    m_totalPersons = 0;
    m_persons = nullptr;

}
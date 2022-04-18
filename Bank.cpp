#include "Bank.h"

Bank::Bank() {
    m_name = nullptr;
    m_account = nullptr;
    m_bankCode = 0;
    m_numbeOfAccounts = 0;
    m_totalBalance = 0;
}

Bank::Bank(const char *name, int code) {
    m_name = strdup(name);
    m_account = nullptr;
    m_bankCode = code;
    m_numbeOfAccounts = 0;
    m_totalBalance = 0;
}

Bank::~Bank() {
    delete[] m_name;
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        delete m_account[i];
    }
    delete[] m_account;
}

void Bank::SetBankName(const char *name) {
    m_name = strdup(name);
}

void Bank::SetAccount(Account **account, int numbeOfAccounts) {
    m_account = account;
    m_numbeOfAccounts = numbeOfAccounts;
}

void Bank::SetTotal(double total) {
    m_totalBalance = total;
}

void Bank::SetCode(int code) {
    m_bankCode = code;
}

const char *Bank::GetBankName() const {
    return m_name;
}

Account **Bank::GetAccounts() const {
    return m_account;
}

int Bank::GetNumberOfAccounts() const {
    return m_numbeOfAccounts;
}

double Bank::GetTotal() const {
    return m_totalBalance;
}

int Bank::GetCode() const {
    return m_bankCode;
}

void Bank::AddAccount(const Account &account) {
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
            return;
        }
    }
    auto newAccountList = new Account *[m_numbeOfAccounts + 1];
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        newAccountList[i] = m_account[i];
    }
    newAccountList[m_numbeOfAccounts] = new Account(account);
    SetAccount(newAccountList, m_numbeOfAccounts + 1);
    m_totalBalance += account.GetBalance();
}

void Bank::AddAccount(const Person &per, double amount) {
    Account newAcc(per, amount);
    AddAccount(newAcc);
}

void Bank::AddPerson(const Person &newPerson, const Account &account, double amount) {
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
            for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
                if (m_account[i]->GetPersons()[j]->GetId() == newPerson.GetId()) {
                    return;
                }
            }
            m_account[i]->AddPerson(newPerson, amount);
            m_totalBalance += amount;
            return;
        }
    }
    AddAccount(account);

}

void Bank::DeleteAccount(const Account &account) {
    bool flag = false;
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
            delete m_account[i];
            flag = true;
        }
        if (flag) { m_account[i] = m_account[i + 1]; }
    }
    if (flag) {
        m_numbeOfAccounts -= 1;
        m_totalBalance -= account.GetBalance();
    }
    if (!m_numbeOfAccounts) {
        delete[] m_account;
        m_account = nullptr;
        m_totalBalance = 0;
    }
}

void Bank::DeletePerson(const Person &p) {
    for(int i = 0; i < m_numbeOfAccounts; i++){
        for(int j = 0; j< m_account[i]->GetTotalPersons();j++){
            if(m_account[i]->GetPersons()[j]->GetId() == p.GetId()){
                m_account[i]->DeletePerson(p);
                j--;
                if(!m_account[i]->GetTotalPersons()) {
                    DeleteAccount(*m_account[i]);
                    i--;
                }
            }
        }
    }
}


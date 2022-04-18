#include "Transaction.h"

Transaction::Transaction(Account *s, Account *d, double amount, const char *date) {
    m_source = s;
    m_destination = d;
    m_amount = amount;
    m_date = strdup(date);
}

Transaction::Transaction(const Transaction &other) {
    m_source = other.m_source;
    m_destination = other.m_destination;
    m_amount = other.m_amount;
    m_date = strdup(other.m_date);
}

void Transaction::SetSource(Account *src) {
    m_source = src;
}

void Transaction::SetDes(Account *dst) {
    m_destination = dst;
}

void Transaction::SetAmount(double amount) {
    m_amount = amount;
}

void Transaction::SetDate(const char *date) {
    delete[] m_date;
    m_date = strdup(date);
}

Account *Transaction::GetSource() const {
    return m_source;
}

Account *Transaction::GetDes() const {
    return m_destination;
}

double Transaction::GetAmount() const {
    return m_amount;
}

char *Transaction::GetDate() const {
    return m_date;
}
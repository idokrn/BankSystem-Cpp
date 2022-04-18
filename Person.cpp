#include "Person.h"

Person::Person() {
    m_name = nullptr;
    m_id = 0;
}

Person::Person(const char *name, int id) {
    m_name = strdup(name);
    m_id = id;
}

Person::Person(const Person &other) {
    m_name = strdup(other.GetName());
    m_id = other.GetId();
}

Person::~Person() {
    delete [] m_name;
}

int Person::GetId() const {
    return m_id;
}

void Person::SetId(int newId) {
    m_id = newId;
}

char *Person::GetName() const {
    return m_name;
}

void Person::SetName(const char *newName) {
    delete[] m_name;
    m_name = strdup(newName);
}


#include "cTag.h"

cTag::cTag(int id, std::string nome)
: m_id(id), m_nome(nome) {}

int cTag::identifier() const {
    return m_id;
}

const std::string& cTag::nome() const {
    return m_nome;
}

void cTag::setidentifier(int id) {
    if (id > 0) { m_id = id; }
}

void cTag::setnome(std::string nome) {
    m_nome = nome;
}

std::ostream& operator<<(std::ostream& os, const cTag& tag) {
    os << tag.m_id << "," << tag.m_nome;
    return os;
}

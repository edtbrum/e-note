#include "cAutor.h"

cAutor::cAutor(std::string nome, std::string email)
: m_nome(nome), m_email(email) {}

cAutor::cAutor(int id, std::string nome, std::string email)
: m_id(id), m_nome(nome), m_email(email) {}

cAutor::~cAutor() {}

int cAutor::identifier() const {
    return m_id;
}

const std::string& cAutor::nome() const {
    return m_nome;
}

const std::string& cAutor::email() const {
    return m_email;
}

void cAutor::setid(int id) {
    m_id = id;
}

void cAutor::setnome(std::string nome) {
    m_nome = nome;
}

void cAutor::setemail(std::string email) {
    m_email = email;
}

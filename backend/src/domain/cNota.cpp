#include "domain/cNota.h"

cNota::cNota(std::string titulo, std::string conteudo, int autor_id)
: m_titulo(titulo), m_conteudo(conteudo), m_autor_id(autor_id) {}

int cNota::identifier() const {
    return m_id;
}

const std::string& cNota::titulo() const {
    return m_titulo;
}

const std::string& cNota::conteudo() const {
    return m_conteudo;
}

using time_point = std::chrono::system_clock::time_point;

time_point cNota::criado_em() const {
    return m_criado_em;
}

time_point cNota::atualizado_em() const {
    return m_atualizado_em;
}

int cNota::autor_id() const {
    return m_autor_id;
}

void cNota::setidentifier(int id) {
    if (id > 0) { m_id = id; }
}

void cNota::settitulo(const std::string& titulo) {
    m_titulo = titulo;
}

void cNota::setconteudo(const std::string& conteudo) {
    m_conteudo = conteudo;
}

void cNota::setcriado_em(time_point criado_em) {
    m_criado_em = criado_em;
}

void cNota::setatualizado_em(time_point atualizado_em) {
    m_atualizado_em = atualizado_em;
}

void cNota::setautor_id(int id) {
    if (id > 0) { m_id = id; }
}

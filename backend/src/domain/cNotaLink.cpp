#include "cNotaLink.h"

cNotaLink::cNotaLink(int id, std::string tipo, std::string url, int orig, int dest)
: m_id(id), m_tipo(tipo), m_url(url), m_nota_origem_id(orig), m_nota_destino_id(dest) {}

int cNotaLink::identifier() const {
    return m_id;
}

const std::string& cNotaLink::tipo() const {
    return m_tipo;
}

const std::string& cNotaLink::url() const {
    return m_url;
}

int cNotaLink::nota_origem_id() const {
    return m_nota_origem_id;
}

int cNotaLink::nota_destino_id() const {
    return m_nota_destino_id;
}

void cNotaLink::setidentifier(int id) {
    if (id > 0) { m_id = id; }
}

void cNotaLink::settipo(std::string tipo) {
    m_tipo = tipo;
}

void cNotaLink::seturl(std::string url) {
    m_url = url;
}

void cNotaLink::setnota_origem_id(int id) {
    if (id > 0) { m_nota_origem_id = id; }
}

void cNotaLink::setnota_destino_id(int id) {
    if (id > 0) { m_nota_destino_id = id; }
}

std::ostream& operator<<(std::ostream& os, const cNotaLink& nlink) {
    os  << nlink.m_id << "," << nlink.m_tipo << "," << nlink.m_url << "," 
        << nlink.m_nota_origem_id << "," << nlink.m_nota_destino_id;
    return os;
}

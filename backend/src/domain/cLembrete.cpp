#include "cLembrete.h"

cLembrete::cLembrete(int id, std::string dh, bool ativo, int nota_id)
: m_id(id), m_data_hora(dh), m_ativo(ativo), m_nota_id(nota_id) {}

int cLembrete::identifier() const {
    return m_id;
}

const std::string& cLembrete::data_hora() const {
    return m_data_hora;
}

bool cLembrete::ativo() const {
    return m_ativo;
}

int cLembrete::nota_id() const {
    return m_nota_id;
}

void cLembrete::setidentifier(int id) {
    if (id > 0) { m_id = id; }
}

void cLembrete::setdata_hora(std::string data_hora) {
    m_data_hora = data_hora;
}

void cLembrete::setativo(bool ativo) {
    m_ativo = ativo;
}

void cLembrete::setnota_id(int id) {
    if (id > 0) { m_nota_id = id; }
}

std::ostream& operator<<(std::ostream& os, const cLembrete& lembrete) {
    os  << lembrete.m_id << "," << lembrete.data_hora() << "," 
        << lembrete.m_ativo << "," << lembrete.m_nota_id;
    return os;
}

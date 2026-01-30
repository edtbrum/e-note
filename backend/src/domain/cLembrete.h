#pragma once

#include <ostream>
#include <string>

class cLembrete {
public:
    cLembrete() = default;
    ~cLembrete() = default;
    cLembrete(int id, std::string dh, bool ativo, int nota_id);

    int identifier() const;
    const std::string& data_hora() const;
    bool ativo() const;
    int nota_id() const;
    void setidentifier(int id);
    void setdata_hora(std::string data_hora);
    void setativo(bool ativo);
    void setnota_id(int id);

    friend std::ostream& operator<<(std::ostream& os, const cLembrete& lembrete);

private:
    int m_id {};
    std::string m_data_hora;
    bool m_ativo {};
    int m_nota_id {};
};
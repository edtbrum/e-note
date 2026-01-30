#pragma once

#include <ostream>
#include <string>

class cNotaLink {
public:
    cNotaLink() = default;
    ~cNotaLink() = default;
    cNotaLink(int id, std::string tipo, std::string url, int orig, int dest);

    int identifier() const;
    const std::string& tipo() const;
    const std::string& url() const;
    int nota_origem_id() const;
    int nota_destino_id() const;

    void setidentifier(int id);
    void settipo(std::string tipo);
    void seturl(std::string url);
    void setnota_origem_id(int id);
    void setnota_destino_id(int id);

    friend std::ostream& operator<<(std::ostream& os, const cNotaLink& nlink);

private:
    int m_id {};
    std::string m_tipo;
    std::string m_url;
    int m_nota_origem_id {};
    int m_nota_destino_id {};
};

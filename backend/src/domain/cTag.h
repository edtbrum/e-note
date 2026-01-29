#pragma once

#include <ostream>
#include <string>

class cTag {
public:
    cTag() = default;
    ~cTag() = default;
    cTag(int id, std::string nome);

    int identifier() const;
    const std::string& nome() const;
    void setidentifier(int id);
    void setnome(std::string nome);

    friend std::ostream& operator<<(std::ostream& os, const cTag& tag);

private:
    int m_id {};
    std::string m_nome;
};
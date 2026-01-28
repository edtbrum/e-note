#pragma once

#include <string>

class cAutor {
public:
    cAutor() = default;
    cAutor(std::string nome, std::string email);
    cAutor(int id, std::string nome, std::string email);
    ~cAutor();

    int identifier() const;
    const std::string& nome() const;
    const std::string& email() const;

    void setid(int id);
    void setnome(std::string nome);
    void setemail(std::string email);

private:
    int m_id {};
    std::string m_nome;
    std::string m_email;
};
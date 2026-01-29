#pragma once

#include <string>
#include <chrono>

class cNota {
public:
    using time_point = std::chrono::system_clock::time_point;

    cNota() = default;
    ~cNota() = default;
    explicit cNota(std::string titulo, std::string conteudo, int autor_id);

    int identifier() const;
    const std::string& titulo() const;
    const std::string& conteudo() const;
    time_point criado_em() const;
    time_point atualizado_em() const;
    int autor_id() const;

    void setidentifier(int id);
    void settitulo(const std::string& titulo);
    void setconteudo(const std::string& conteudo);
    void setcriado_em(time_point criado_em);
    void setatualizado_em(time_point atualizado_em);
    void setautor_id(int id);

private:
    int m_id {};
    std::string m_titulo;
    std::string m_conteudo;
    time_point m_criado_em;
    time_point m_atualizado_em;
    int m_autor_id {};
};

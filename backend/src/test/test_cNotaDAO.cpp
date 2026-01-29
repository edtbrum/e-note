#include "dao/cConnectionMySQL.h"
#include "dao/cNotaDAO.h"
#include "domain/cNota.h"
#include <iostream>

int main() {
    std::cout << ">> == Teste de acesso a tabela nota ==" << std::endl;

    cConnectionMySQL conn;
    cNotaDAO notadao(conn);
    auto *new_conn = notadao.get().connection();

    try {
        new_conn->setAutoCommit(false);

        cNota nota = notadao.findbyid(1);
        std::cout << ">> [OK] Find by ID realizado com sucesso" << std::endl;
        //std::cout << ">> [OK] [cNota] " << nota << std::endl;

        notadao.insert(nota);
        std::cout << ">> [OK] Insert realizado com sucesso" << std::endl;

        nota.settitulo("Titulo Teste Teste");
        notadao.update(nota);
        std::cout << ">> [OK] Update realizado com sucesso" << std::endl;

        new_conn->rollback();
        std::cout << ">> [OK] Testes realizados com sucesso" << std::endl;
    }
    catch(const std::runtime_error& e) {
        new_conn->rollback();
        std::cout << ">> [EXCEPTION] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

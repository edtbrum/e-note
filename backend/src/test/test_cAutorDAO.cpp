#include "dao/cAutorDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cAutor.h"
#include <iostream>
#include <stdexcept>

int main() {
    std::cout << ">> == Teste de acesso a tabela autor ==" << std::endl;

    cAutor autor(1,"Eduardo Trevisan","edtrevisan@gmail.com");
    cConnectionMySQL conn;
    cAutorDAO autordao(conn);
    auto *nconn = autordao.get().connection();

    try {
        nconn->setAutoCommit(false);

        cAutor nautor = autordao.findbyid(autor.identifier());
        std::cout << ">> [OK] Find realizado com sucesso" << std::endl;

        autordao.insert(autor);
        std::cout << ">> [OK] Insert realizado com sucesso" << std::endl;

        nautor.setemail("novoemail@gmail.com");
        autordao.update(nautor);
        std::cout << ">> [OK] Update realizado com sucesso" << std::endl;

        nconn->rollback();

        std::cout << ">> [OK] Teste realizado com sucesso" << std::endl;
    }
    catch(const std::runtime_error& e) {
        nconn->rollback();
        std::cout << ">> [EXCEPTION] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
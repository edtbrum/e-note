#include "dao/cAutorDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cAutor.h"
#include "service/cAutorService.h"
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::cout << ">> == Teste de servico para Autor ==" << std::endl;

    cConnectionMySQL conn;
    cAutorDAO autordao(conn);
    cAutorService service;

    try {
        cAutor autor("Teste Teste", "teste@teste.com");
        cAutor newautor = service.createAutor(autordao, autor);
        std::cout << ">> [OK] Autor criado com sucesso" << std::endl;

        newautor.setnome("Teste Teste Teste");
        service.updateAutor(autordao, newautor);
        std::cout << ">> [OK] Autor alterado com sucesso" << std::endl;

        std::vector<cAutor> lista = service.listAutores(autordao);
        if (!lista.empty()) {
            std::cout << ">> [OK] Lista de autores gerada com sucesso" << std::endl;
        }
        else {
            std::cout << ">> [ERRO] Lista de autores vazia" << std::endl;
        }

        service.deleteAutor(autordao, newautor.identifier());
        std::cout << ">> [OK] Autor apagado com sucesso" << std::endl;

        std::cout << ">> [OK] Testes finalizados com sucesso" << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << ">> [EXCEPTION] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
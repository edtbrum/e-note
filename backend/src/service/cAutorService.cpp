#include "cAutorService.h"
#include "domain/cAutor.h"
#include "cTransactionMySQL.h"

cAutor cAutorService::createAutor(IAutorDAO& autor_dao, const cAutor& autor) {
    auto *conn = autor_dao.get().connection();
    cTransactionMySQL tx(conn);

    int id = autor_dao.insert(autor);
    cAutor novo_autor = autor_dao.findbyid(id);
    tx.commit();

    return novo_autor;
}

void cAutorService::updateAutor(IAutorDAO& autor_dao, cAutor& autor) {
    autor_dao.update(autor);
}

std::vector<cAutor> cAutorService::listAutores(IAutorDAO& autor_dao) {
    return autor_dao.list();
}

void cAutorService::deleteAutor(IAutorDAO& autor_dao, int id) {
    if (autor_dao.verifyautor(id) == 0) {
        autor_dao.deletebyid(id);
    }
    else {
        throw std::runtime_error("Error: Autor nao pode ser apagado");
    }
}

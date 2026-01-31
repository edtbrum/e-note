#pragma once

#include "dao/IAutorDAO.h"
#include "domain/cAutor.h"
#include <cppconn/connection.h>
#include <vector>

class cAutorService {
public:
    cAutor createAutor(IAutorDAO& autor_dao, const cAutor& autor);
    void changeAutor(IAutorDAO& autor_dao, cAutor& autor);
    std::vector<cAutor> listAutores(IAutorDAO& autor_dao);
};

#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cAutor.h"

enum class eSearchAuthor { AuthorID, AuthorName, AuthorEmail};

class IAutorDAO {
public:
    virtual ~IAutorDAO() = default;

    virtual cConnectionMySQL& get() = 0;
    virtual void insert(cAutor& autor) = 0;
    virtual void update(cAutor& autor) = 0;
    virtual cAutor find(cAutor& autor, eSearchAuthor type) = 0;
};

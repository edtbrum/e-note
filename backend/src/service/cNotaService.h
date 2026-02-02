#pragma once

#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"
#include "domain/cNotaTag.h"
#include "dto/create_nota_dto.h"
#include "repository/INotaRepository.h"
#include <optional>
#include <vector>

class cNotaService {
public:
    cNotaService(cConnectionMySQL& conn, INotaRepository& repo);
    void createNota(const cNota& nota, 
                    const std::optional<cLembrete>& lembrete,
                    const std::vector<cNotaTag>& tags,
                    const std::vector<cNotaLink>& links
    );

    void createNotaDTO(const CreateNotaDTO& dto);

private:
    cConnectionMySQL& m_conn;
    INotaRepository& m_repo;
};

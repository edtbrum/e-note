#pragma once

#include "dao/INotaDAO.h"
#include "dao/cConnectionMySQL.h"
#include "domain/cLembrete.h"
#include "domain/cNota.h"
#include "domain/cNotaLink.h"
#include "domain/cNotaTag.h"
#include "dto/create_nota_dto.h"
#include "dto/nota_response_dto.h"
#include "dto/update_nota_dto.h"
#include "repository/INotaRepository.h"
#include <optional>
#include <vector>

class cNotaService {
public:
    cNotaService(cConnectionMySQL& conn, INotaRepository& repo);
    int createNota( const cNota& nota, 
                    const std::optional<cLembrete>& lembrete,
                    const std::vector<cNotaTag>& tags,
                    const std::vector<cNotaLink>& links
    );

    int createNotaDTO(const CreateNotaDTO& dto);
    NotaResponseDTO findNotaById(int nota_id);
    std::vector<NotaResponseDTO> findNotas();
    void deleteNota(INotaDAO& notadao, int id);
    void updateNotaDTO(const UpdateNotaDTO& dto);

private:
    cConnectionMySQL& m_conn;
    INotaRepository& m_repo;
};

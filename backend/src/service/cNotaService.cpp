#include "cNotaService.h"
#include "service/cTransactionMySQL.h"

cNotaService::cNotaService(cConnectionMySQL& conn, INotaRepository& repo)
: m_conn(conn), m_repo(repo) {}

void cNotaService::createNota(  
    const cNota& nota, 
    const std::optional<cLembrete>& lembrete,
    const std::vector<cNotaTag>& tags,
    const std::vector<cNotaLink>& links
) {
    auto *conn = m_conn.connection();
    cTransactionMySQL tx(conn);

    int notaid = m_repo.insertNota(m_conn, nota);
    
    if (lembrete.has_value()) {
        m_repo.insertLembrete(m_conn, *lembrete, notaid);
    }
    
    if (!tags.empty()) {
        m_repo.insertTags(m_conn, tags, notaid);
    }
    
    if (!links.empty()) {
        m_repo.insertLinks(m_conn, links, notaid);
    }

    tx.commit();
}

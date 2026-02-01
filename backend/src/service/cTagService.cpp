#include "cTagService.h"
#include "domain/cTag.h"
#include "cTransactionMySQL.h"

cTag cTagService::createTag(ITagDAO& tagdao, const std::string nome) {
    auto *conn = tagdao.get().connection();
    cTransactionMySQL tx(conn);

    int id = tagdao.insert(nome);
    cTag tag = tagdao.findbyid(id);

    tx.commit();
    return tag;
}

std::vector<cTag> cTagService::listTags(ITagDAO& tagdao) {
    return tagdao.list();
}

void cTagService::deleteTag(ITagDAO& tagdao, int id) {
    tagdao.deletebyid(id);
}

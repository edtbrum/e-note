#pragma once

#include "dao/ITagDAO.h"
#include "domain/cTag.h"
#include <string>
#include <vector>

class cTagService {
public:
    cTag createTag(ITagDAO& tagdao, const std::string nome);
    std::vector<cTag> listTags(ITagDAO& tagdao);
    void deleteTag(ITagDAO& tagdao, int id);
};

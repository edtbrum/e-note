#include "service/makeLinkKey.h"

std::string makeLinkKey(const LinkDTO& l) {
    if (l.tipo == "interno") {
        return "I:" + std::to_string(l.notaDestinoId.value());
    }
    else {
        return "E:" + l.url.value();
    }
}
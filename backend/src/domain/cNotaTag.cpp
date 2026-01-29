#include "cNotaTag.h"

cNotaTag::cNotaTag(int notaid, int tagid)
: m_nota_id(notaid), m_tag_id(tagid) {}

int cNotaTag::nota_id() const {
    return m_nota_id;
}

int cNotaTag::tag_id() const {
    return m_tag_id;
}

void cNotaTag::setnota_id(int id) {
    if (id > 0) { m_nota_id = id; }
}

void cNotaTag::settag_id(int id) {
    if (id > 0) { m_tag_id = id; }
}

std::ostream& operator<<(std::ostream& os, const cNotaTag& notatag) {
    os << notatag.m_nota_id << "," << notatag.m_tag_id;
    return os;
}

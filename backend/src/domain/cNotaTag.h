#pragma once

#include <ostream>

class cNotaTag {
public:
    cNotaTag() = default;
    ~cNotaTag() = default;
    cNotaTag(int notaid, int tagid);

    int nota_id() const;
    int tag_id() const;
    void setnota_id(int id);
    void settag_id(int id);

    friend std::ostream& operator<<(std::ostream& os, const cNotaTag& notatag);

private:
    int m_nota_id {};
    int m_tag_id {};
};
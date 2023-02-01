#ifndef ERE_COMPONENT_TAG_HPP
#define ERE_COMPONENT_TAG_HPP

#include <string>

namespace ere {

struct tag {

    tag() : m_tag("entity") {}
    tag(const std::string& t_tag) : m_tag(t_tag) {}

    std::string getTag() { return m_tag; }
    void rename(const std::string& t_tag) { m_tag = t_tag; }

private:

    std::string m_tag;
};

}

#endif

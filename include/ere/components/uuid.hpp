#ifndef ERE_COMPONENTS_UUID_COMPONENT_HPP
#define ERE_COMPONENTS_UUID_COMPONENT_HPP

#include <util/algo.hpp>

namespace ere {

struct uuid {

    uuid() { m_uuid = util::generate_uuid_v4(); }
    std::string regenerate() { m_uuid = util::generate_uuid_v4(); return m_uuid; }
    std::string getUUID() { return m_uuid; }

private:

    std::string m_uuid;
};

}

#endif

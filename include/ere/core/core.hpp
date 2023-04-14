#ifndef __ERE_CORE_HPP__
#define __ERE_CORE_HPP__

#include <memory>

namespace ere {

template<typename T>
using scope = std::unique_ptr<T>;
template<typename T, typename... args>
constexpr scope<T> createScope(args&&... t_args) {
    return std::make_unique<T>(std::forward<args>(t_args)...);
}

template<typename T>
using ref = std::shared_ptr<T>;
template<typename T, typename... args>
constexpr ref<T> createRef(args&&... t_args) {
    return std::make_shared<T>(std::forward<args>(t_args)...);
}

template<typename T>
using weak_ref = std::weak_ptr<T>;

}

#endif

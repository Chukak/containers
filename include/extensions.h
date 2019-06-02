#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <utility>
#include <memory>

/*
 * Pseudonym for code: `std::make_shared<T>(T(...))`.
 */
template<typename T,
         typename ... Args>
inline auto make_shared_ptr(Args&& ... args)
-> decltype(std::make_shared<T>(std::forward<Args>(args)...))
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}


#endif // EXTENSIONS_H

#ifndef __HELPERS_H_
#define __HELPERS_H_

#include <vector>

namespace Helpers {
    int choice(const std::string&);

    template <class T>
    void sort_lexicographically(std::vector<T>& data);
}

#include "Helpers_impl.h"

#endif


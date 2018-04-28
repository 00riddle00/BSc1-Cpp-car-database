#ifndef __HELPERS_IMPL_H_
#define __HELPERS_IMPL_H_

#include <vector>

namespace Helpers {

    template <class T>
    void sort_lexicographically(std::vector<T>& data) {

        int first = 0;
        int last = data.size() - 1;

        int i, j;
        T temp;

        for (i = first; i < last; ++i) {

            for (j = i + 1; j < last + 1; ++j) {

                if (*data[i] > *data[j]) {
                    temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }

}

#endif

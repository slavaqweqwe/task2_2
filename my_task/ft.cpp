
#include "ft.h"
std::vector<std::complex< double >> fur(std::vector<std::complex< double >> vect) {
    std::vector<std::complex< double >> outVect(vect.size());
    std::complex< double > comp_one(0, 1.0);
    for (size_t j = 0; j < vect.size(); j++) {
        for (size_t i = 0; i < vect.size(); i++) {
            outVect[j] += vect[i] * exp(comp_one * ((-2 * PI * i * j) / vect.size()));

        }
    }
    return outVect;
}
//
// Created by Oleksandr Deundiak on 10/21/17.
//

#ifndef LAB2_LFSR_H
#define LAB2_LFSR_H


#include <vector>

/**
 * Class for LFSR
 */
class LFSR {
public:
    /**
     * Constructor
     * @param equation coefficient values (lower bit will be multiplied with state's lower bit)
     * @param initialState initial state (lower bit will be returned fisrt)
     * @param cutoff maximum n-bit value, where n = size of LFSR
     */
    explicit LFSR(uint64_t equation, uint64_t initialState, uint64_t cutoff);

    /**
     * Returns next number of the sequence
     * @return next number of the sequence
     */
    uint64_t next();

private:
    uint64_t equation;
    uint64_t state;
    uint64_t cutoff;
};


#endif //LAB2_LFSR_H

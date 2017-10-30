//
// Created by Oleksandr Deundiak on 10/21/17.
//

#include "LFSR.h"

LFSR::LFSR(uint64_t equation, uint64_t initialState, uint64_t cutoff)
        : equation(equation),
          state(initialState),
          cutoff(cutoff) { }

uint64_t LFSR::next() {
    uint64_t res = this->state & 0x1;

    // Iterate
    uint64_t temp = this->state & this->equation;
    uint64_t cutoffTemp = this->cutoff;
    uint64_t newBit = 0;
    while (cutoffTemp != 0) {
        if ((temp & 0x000000000000001) != 0)
            newBit = ~newBit;
        newBit <<= 1;

        cutoffTemp >>= 1;
        temp >>= 1;
    }
    newBit &= this->cutoff + 1;
    newBit >>= 1;


    this->state = (this->state >> 1)  | newBit;

    return res;
}
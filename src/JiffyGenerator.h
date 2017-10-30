//
// Created by Oleksandr Deundiak on 10/21/17.
//

#ifndef LAB2_JIFFYGENERATOR_H
#define LAB2_JIFFYGENERATOR_H


#include "LFSR.h"

/**
 * CLass for Jiffy pseudo random generator
 */
class JiffyGenerator {
public:
    /**
     * Constructor
     * @param l1 L1 LFSR
     * @param l2 L2 LFSR
     * @param l3 L3 LFSR
     */
    JiffyGenerator(LFSR l1, LFSR l2, LFSR l3);

    /**
     * Return next pseudo random bit
     * @return next pseudo random bit
     */
    uint64_t next();

private:
    LFSR l1, l2, l3;
};


#endif //LAB2_JIFFYGENERATOR_H

//
// Created by Oleksandr Deundiak on 10/21/17.
//

#include "JiffyGenerator.h"

JiffyGenerator::JiffyGenerator(LFSR l1, LFSR l2, LFSR l3)
    : l1(l1), l2(l2), l3(l3) { }

uint64_t JiffyGenerator::next() {
    auto x = this->l1.next(), y = this->l2.next(), s = this->l3.next();

    return (s & x) ^ (~s & y);
}
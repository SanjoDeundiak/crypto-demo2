//
// Created by Oleksandr Deundiak on 10/21/17.
//

#ifndef LAB2_JIFFYCRYPTOANALYSIS_H
#define LAB2_JIFFYCRYPTOANALYSIS_H

#include <string>
#include "LFSR.h"
#include "JiffyGenerator.h"

/**
 * Class for Jiffy generator crypto analysis
 */
class JiffyCryptoAnalysis {
public:
    JiffyCryptoAnalysis(std::string sequence,
                        uint64_t equation1, uint64_t cutoff1,
                        uint64_t equation2, uint64_t cutoff2,
                        uint64_t equation3, uint64_t cutoff3);

    JiffyGenerator generator() const;

private:
    uint64_t findInitialValue(uint64_t cutoff, uint64_t equation, double C) const;
    uint64_t findL3(const LFSR &l1, const LFSR &l2, uint64_t cutoff, uint64_t equation) const;

    std::string sequence;
    uint64_t cutoff1, cutoff2, cutoff3;
    uint64_t equation1, equation2, equation3;
};


#endif //LAB2_JIFFYCRYPTOANALYSIS_H

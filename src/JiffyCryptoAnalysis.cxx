//
// Created by Oleksandr Deundiak on 10/21/17.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include "JiffyCryptoAnalysis.h"
#include "LFSR.h"
#include "JiffyGenerator.h"
#include "PhiInverse.h"

JiffyCryptoAnalysis::JiffyCryptoAnalysis(
        std::string sequence,
        uint64_t equation1, uint64_t cutoff1,
        uint64_t equation2, uint64_t cutoff2,
        uint64_t equation3, uint64_t cutoff3)
    : sequence(std::move(sequence)),
      equation1(equation1), cutoff1(cutoff1),
      equation2(equation2), cutoff2(cutoff2),
      equation3(equation3), cutoff3(cutoff3) { }

JiffyGenerator JiffyCryptoAnalysis::generator() const {
    double p1 = 0.25;
    double N = this->sequence.length();
    double a = 0.01;
    double C = N*p1 + PhiInverse::NormalCDFInverse(1-a)*std::sqrt(N*p1*(1-p1));
    std::cout << "C=" << C << ' ' << PhiInverse::NormalCDFInverse(1-a) << std::endl;

    auto state1 = this->findInitialValue(this->cutoff1, this->equation1, C);
    auto state2 = this->findInitialValue(this->cutoff2, this->equation2, C);

    auto l1 = LFSR(this->equation1, state1, this->cutoff1);
    auto l2 = LFSR(this->equation2, state2, this->cutoff2);
    auto state3 = this->findL3(l1, l2,
                 this->cutoff3, this->equation3);

    auto l3 = LFSR(this->equation3, state3, this->cutoff3);

    std::cout << "States: " << std::bitset<8>(state1) << ' ' << std::bitset<8>(state2) << ' ' << std::bitset<8>(state3) << std::endl;

    return JiffyGenerator(l1, l2, l3);
}

uint64_t JiffyCryptoAnalysis::findL3(const LFSR &l1, const LFSR &l2, uint64_t cutoff, uint64_t equation) const {
    for (uint64_t initialState = 0; initialState <= cutoff; initialState++) {
        LFSR l3(equation, initialState, cutoff);

        JiffyGenerator generator(l1, l2, l3);

        int i;
        for (i = 0; i < this->sequence.size(); i++) {
            auto rand = generator.next();

            if ((rand != 0 && this->sequence[i] == '0')
                || (rand == 0 && this->sequence[i] == '1'))
                break;
        }

        if (i == this->sequence.size()) {
            return initialState;
        }
    }

    assert(false);
}

uint64_t JiffyCryptoAnalysis::findInitialValue(uint64_t cutoff, uint64_t equation, double C) const {
    std::vector<int> rValues;
    int Rmin = std::numeric_limits<int>::max();
    uint64_t state = 0;
    for (uint64_t initialState = 0; initialState <= cutoff; initialState++) {
        LFSR l1(equation, initialState, cutoff);

        int R = 0;
        for (int i = 0; i < this->sequence.size(); i++) {
            auto rand = l1.next();

            if ((rand != 0 && this->sequence[i] == '0')
                || (rand == 0 && this->sequence[i] == '1'))
                R++;
        }

        if (R < Rmin) {
            Rmin = R;
            state = initialState;
        }
        rValues.push_back(R);
    }

    std::vector<int> rMatch;
    auto predicate = [=] (const int &value) {
        return value < C;
    };
    std::copy_if(rValues.begin(), rValues.end(), std::back_inserter(rMatch), predicate);
    assert(rMatch.size() == 1);

    return state;
}
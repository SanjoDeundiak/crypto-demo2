//
// Created by Oleksandr Deundiak on 10/21/17.
//

#include <iostream>
#include <cmath>
#include <cassert>
#include "JiffyCryptoAnalysis.h"
#include "LFSR.h"
#include "JiffyGenerator.h"
#include "Phi.h"

JiffyCryptoAnalysis::JiffyCryptoAnalysis(
        std::string sequence,
        uint64_t equation1, uint64_t cutoff1,
        uint64_t equation2, uint64_t cutoff2,
        uint64_t equation3, uint64_t cutoff3)
    : sequence(std::move(sequence)),
      equation1(equation1), cutoff1(cutoff1),
      equation2(equation2), cutoff2(cutoff2),
      equation3(equation3), cutoff3(cutoff3) { }

JiffyGenerator JiffyCryptoAnalysis::generator(int N1, int N2) const {
    double p1 = 0.25;
    double a = 0.01;
    double C1 = N1*p1 + Phi::NormalCDFInverse(1-a)*std::sqrt(N1*p1*(1-p1));
    double C2 = N2*p1 + Phi::NormalCDFInverse(1-a)*std::sqrt(N2*p1*(1-p1));

    auto states1 = this->findInitialValue(this->cutoff1, this->equation1, C1, N1);
    auto states2 = this->findInitialValue(this->cutoff2, this->equation2, C2, N2);

    auto states = this->findL3(states1, states2, this->cutoff3, this->equation3, std::max(N1, N2));

    auto l1 = LFSR(this->equation1, states[0], this->cutoff1);
    auto l2 = LFSR(this->equation2, states[1], this->cutoff2);
    auto l3 = LFSR(this->equation3, states[2], this->cutoff3);

    std::cout << "States: " << std::bitset<11>(states[0])
              << ' ' << std::bitset<9>(states[1])
              << ' ' << std::bitset<10>(states[2]) << std::endl;

    return JiffyGenerator(l1, l2, l3);
}

std::vector<uint64_t> JiffyCryptoAnalysis::findL3(const std::vector<uint64_t> &states1,
                                     const std::vector<uint64_t> &states2,
                                     uint64_t cutoff, uint64_t equation, int N) const {
    for (size_t i = 0; i < states1.size(); i++) {
        for (size_t j = 0; j < states2.size(); j++) {
            {
                auto l1 = LFSR(this->equation1, states1[i], this->cutoff1);
                auto l2 = LFSR(this->equation2, states2[j], this->cutoff2);

                int k;
                for (k = 0; k < N; k++) {
                    auto rand1 = l1.next();
                    auto rand2 = l2.next();

                    if (rand1 == rand2) {
                        if ((rand1 != 0 && this->sequence[k] == '0')
                            || (rand1 == 0 && this->sequence[k] == '1'))
                            break;
                    }
                }

                if (k != N) {
                    continue;
                }
            }

            auto l1 = LFSR(this->equation1, states1[i], this->cutoff1);
            auto l2 = LFSR(this->equation2, states2[j], this->cutoff2);

            for (uint64_t initialState = 0; initialState <= cutoff; initialState++) {
                LFSR l3(equation, initialState, cutoff);

                JiffyGenerator generator(l1, l2, l3);

                int k;
                for (k = 0; k < N; k++) {
                    auto rand = generator.next();

                    if ((rand != 0 && this->sequence[k] == '0')
                        || (rand == 0 && this->sequence[k] == '1'))
                        break;
                }

                if (k == N) {
                    return { states1[i], states2[j], initialState };
                }
            }
        }
    }

    assert(false);
}

std::vector<uint64_t> JiffyCryptoAnalysis::findInitialValue(uint64_t cutoff, uint64_t equation, double C, int N) const {
    std::vector<uint64_t > states;
    for (uint64_t initialState = 0; initialState <= cutoff; initialState++) {
        LFSR l1(equation, initialState, cutoff);

        int R = 0;
        for (int i = 0; i < N; i++) {
            auto rand = l1.next();

            if ((rand != 0 && this->sequence[i] == '0')
                || (rand == 0 && this->sequence[i] == '1'))
                R++;
        }

        if (R < C) {
            states.push_back(initialState);
        }
    }

    return states;
}
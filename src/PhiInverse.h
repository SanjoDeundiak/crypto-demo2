//
// Created by Oleksandr Deundiak on 10/30/17.
//

#ifndef LAB2_PHIINVERSE_H
#define LAB2_PHIINVERSE_H


class PhiInverse {
public:
    static double NormalCDFInverse(double p);

private:
    static double RationalApproximation(double t);
};


#endif //LAB2_PHIINVERSE_H

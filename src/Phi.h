//
// Created by Oleksandr Deundiak on 10/30/17.
//

#ifndef LAB2_PHI_H
#define LAB2_PHI_H


class Phi {
public:
    static double NormalCDFInverse(double p);
    static double NormalCDF(double x);

private:
    static double RationalApproximation(double t);
};


#endif //LAB2_PHIINVERSE_H

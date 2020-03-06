double R(const VectorXd& Fv, const VectorXd& Gv, double beta, double lame1, double lame2) {
    double x0[9];
    x0[0] = Fv[0];
    x0[1] = Fv[1];
    x0[2] = Fv[2];
    x0[3] = Fv[3];
    x0[4] = Fv[4];
    x0[5] = Fv[5];
    x0[6] = Fv[6];
    x0[7] = Fv[7];
    x0[8] = Fv[8];
    const double x1 = x0[0];
    double x2[9];
    x2[0] = Gv[0];
    x2[1] = Gv[1];
    x2[2] = Gv[2];
    x2[3] = Gv[3];
    x2[4] = Gv[4];
    x2[5] = Gv[5];
    x2[6] = Gv[6];
    x2[7] = Gv[7];
    x2[8] = Gv[8];
    const double x3 = x2[0];
    const double x4 = x0[3];
    const double x5 = x2[3];
    const double x6 = x0[6];
    const double x7 = x2[6];
    const double x8 = x1*x3 + x4*x5 + x6*x7;
    const double x9 = x0[1];
    const double x10 = x2[1];
    const double x11 = x0[4];
    const double x12 = x2[4];
    const double x13 = x0[7];
    const double x14 = x2[7];
    const double x15 = x10*x9 + x11*x12 + x13*x14;
    const double x16 = x0[2];
    const double x17 = x2[2];
    const double x18 = x0[5];
    const double x19 = x2[5];
    const double x20 = x0[8];
    const double x21 = x2[8];
    const double x22 = x16*x17 + x18*x19 + x20*x21;

    double out;
    out = (1.0/2.0)*beta*(lame1*pow(x15 + x22 + x8, 2) + lame2*(2*pow(x15, 2) + 2*pow(x22, 2) + 2*pow(x8, 2) + pow(x1*x10 + x11*x5 + x12*x4 + x13*x7 + x14*x6 + x3*x9, 2) + pow(x1*x17 + x16*x3 + x18*x5 + x19*x4 + x20*x7 + x21*x6, 2) + pow(x10*x16 + x11*x19 + x12*x18 + x13*x21 + x14*x20 + x17*x9, 2)));
    return out;

}

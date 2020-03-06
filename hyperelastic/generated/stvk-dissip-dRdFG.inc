void dRdFG(double f00, double f01, double f02, double f10, double f11, double f12, double f20, double f21, double f22, double g00, double g01, double g02, double g10, double g11, double g12, double g20, double g21, double g22, double lambda, double mu, VectorXd& out) {
    const double x0 = f00*g00 + f10*g10 + f20*g20;
    const double x1 = f01*g01 + f11*g11 + f21*g21;
    const double x2 = f02*g02 + f12*g12 + f22*g22;
    const double x3 = lambda*(x0 + x1 + x2);
    const double x4 = 2*x0;
    const double x5 = f00*g01 + f01*g00 + f10*g11 + f11*g10 + f20*g21 + f21*g20;
    const double x6 = f00*g02 + f02*g00 + f10*g12 + f12*g10 + f20*g22 + f22*g20;
    const double x7 = 2*x1;
    const double x8 = f01*g02 + f02*g01 + f11*g12 + f12*g11 + f21*g22 + f22*g21;
    const double x9 = 2*x2;

    out.resize(18);
    out[0] = g00*x3 + mu*(g00*x4 + g01*x5 + g02*x6);
    out[1] = g01*x3 + mu*(g00*x5 + g01*x7 + g02*x8);
    out[2] = g02*x3 + mu*(g00*x6 + g01*x8 + g02*x9);
    out[3] = g10*x3 + mu*(g10*x4 + g11*x5 + g12*x6);
    out[4] = g11*x3 + mu*(g10*x5 + g11*x7 + g12*x8);
    out[5] = g12*x3 + mu*(g10*x6 + g11*x8 + g12*x9);
    out[6] = g20*x3 + mu*(g20*x4 + g21*x5 + g22*x6);
    out[7] = g21*x3 + mu*(g20*x5 + g21*x7 + g22*x8);
    out[8] = g22*x3 + mu*(g20*x6 + g21*x8 + g22*x9);
    out[9] = f00*x3 + mu*(f00*x4 + f01*x5 + f02*x6);
    out[10] = f01*x3 + mu*(f00*x5 + f01*x7 + f02*x8);
    out[11] = f02*x3 + mu*(f00*x6 + f01*x8 + f02*x9);
    out[12] = f10*x3 + mu*(f10*x4 + f11*x5 + f12*x6);
    out[13] = f11*x3 + mu*(f10*x5 + f11*x7 + f12*x8);
    out[14] = f12*x3 + mu*(f10*x6 + f11*x8 + f12*x9);
    out[15] = f20*x3 + mu*(f20*x4 + f21*x5 + f22*x6);
    out[16] = f21*x3 + mu*(f20*x5 + f21*x7 + f22*x8);
    out[17] = f22*x3 + mu*(f20*x6 + f21*x8 + f22*x9);

}

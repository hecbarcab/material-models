double R(double f00, double f01, double f02, double f10, double f11, double f12, double f20, double f21, double f22, double g00, double g01, double g02, double g10, double g11, double g12, double g20, double g21, double g22, double lambda, double mu) {
    const double x0 = f00*g00 + f10*g10 + f20*g20;
    const double x1 = f01*g01 + f11*g11 + f21*g21;
    const double x2 = f02*g02 + f12*g12 + f22*g22;

    double out;
    out = (1.0/2.0)*lambda*pow(x0 + x1 + x2, 2) + (1.0/2.0)*mu*(2*pow(x0, 2) + 2*pow(x1, 2) + 2*pow(x2, 2) + pow(f00*g01 + f01*g00 + f10*g11 + f11*g10 + f20*g21 + f21*g20, 2) + pow(f00*g02 + f02*g00 + f10*g12 + f12*g10 + f20*g22 + f22*g20, 2) + pow(f01*g02 + f02*g01 + f11*g12 + f12*g11 + f21*g22 + f22*g21, 2));
    return out;

}

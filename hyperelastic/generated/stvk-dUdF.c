void dUdF(double f00, double f01, double f02, double f10, double f11, double f12, double f20, double f21, double f22, double lambda, double mu, VectorXd& out) {
    const double x0 = pow(f00, 2) + pow(f10, 2) + pow(f20, 2);
    const double x1 = pow(f01, 2) + pow(f11, 2) + pow(f21, 2);
    const double x2 = pow(f02, 2) + pow(f12, 2) + pow(f22, 2);
    const double x3 = (1.0/2.0)*lambda*(x0 + x1 + x2 - 3);
    const double x4 = f00*f01 + f10*f11 + f20*f21;
    const double x5 = f00*f02 + f10*f12 + f20*f22;
    const double x6 = x0 - 1;
    const double x7 = f01*f02 + f11*f12 + f21*f22;
    const double x8 = x1 - 1;
    const double x9 = x2 - 1;

    out.resize(9);
    out[0] = f00*x3 + mu*(f00*x6 + f01*x4 + f02*x5);
    out[1] = f01*x3 + mu*(f00*x4 + f01*x8 + f02*x7);
    out[2] = f02*x3 + mu*(f00*x5 + f01*x7 + f02*x9);
    out[3] = f10*x3 + mu*(f10*x6 + f11*x4 + f12*x5);
    out[4] = f11*x3 + mu*(f10*x4 + f11*x8 + f12*x7);
    out[5] = f12*x3 + mu*(f10*x5 + f11*x7 + f12*x9);
    out[6] = f20*x3 + mu*(f20*x6 + f21*x4 + f22*x5);
    out[7] = f21*x3 + mu*(f20*x4 + f21*x8 + f22*x7);
    out[8] = f22*x3 + mu*(f20*x5 + f21*x7 + f22*x9);

}

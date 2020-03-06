double U(const VectorXd& Fv, double lame1, double lame2) {
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
    const double x2 = x0[3];
    const double x3 = x0[6];
    const double x4 = pow(x1, 2) + pow(x2, 2) + pow(x3, 2);
    const double x5 = x0[1];
    const double x6 = x0[4];
    const double x7 = x0[7];
    const double x8 = pow(x5, 2) + pow(x6, 2) + pow(x7, 2);
    const double x9 = x0[2];
    const double x10 = x0[5];
    const double x11 = x0[8];
    const double x12 = pow(x10, 2) + pow(x11, 2) + pow(x9, 2);

    double out;
    out = (1.0/8.0)*lame1*pow(x12 + x4 + x8 - 3, 2) + (1.0/4.0)*lame2*(pow(x12 - 1, 2) + pow(x4 - 1, 2) + pow(x8 - 1, 2) + 2*pow(x1*x5 + x2*x6 + x3*x7, 2) + 2*pow(x1*x9 + x10*x2 + x11*x3, 2) + 2*pow(x10*x6 + x11*x7 + x5*x9, 2));
    return out;

}

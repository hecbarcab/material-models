void dUdF(const VectorXd& Fv, double lame1, double lame2, VectorXd& out) {
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
    const double x13 = (1.0/2.0)*lame1*(x12 + x4 + x8 - 3);
    const double x14 = x4 - 1;
    const double x15 = x1*x5 + x2*x6 + x3*x7;
    const double x16 = x1*x9 + x10*x2 + x11*x3;
    const double x17 = x8 - 1;
    const double x18 = x10*x6 + x11*x7 + x5*x9;
    const double x19 = x12 - 1;

    out.resize(9);
    out[0] = lame2*(x1*x14 + x15*x5 + x16*x9) + x1*x13;
    out[1] = lame2*(x1*x15 + x17*x5 + x18*x9) + x13*x5;
    out[2] = lame2*(x1*x16 + x18*x5 + x19*x9) + x13*x9;
    out[3] = lame2*(x10*x16 + x14*x2 + x15*x6) + x13*x2;
    out[4] = lame2*(x10*x18 + x15*x2 + x17*x6) + x13*x6;
    out[5] = lame2*(x10*x19 + x16*x2 + x18*x6) + x10*x13;
    out[6] = lame2*(x11*x16 + x14*x3 + x15*x7) + x13*x3;
    out[7] = lame2*(x11*x18 + x15*x3 + x17*x7) + x13*x7;
    out[8] = lame2*(x11*x19 + x16*x3 + x18*x7) + x11*x13;

}

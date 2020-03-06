double U(double f00, double f01, double f02, double f10, double f11, double f12, double f20, double f21, double f22, double lambda, double mu) {
    const double x0 = pow(f00, 2) + pow(f10, 2) + pow(f20, 2);
    const double x1 = pow(f01, 2) + pow(f11, 2) + pow(f21, 2);
    const double x2 = pow(f02, 2) + pow(f12, 2) + pow(f22, 2);

    double out;
    out = (1.0/8.0)*lambda*pow(x0 + x1 + x2 - 3, 2) + (1.0/4.0)*mu*(pow(x0 - 1, 2) + pow(x1 - 1, 2) + pow(x2 - 1, 2) + 2*pow(f00*f01 + f10*f11 + f20*f21, 2) + 2*pow(f00*f02 + f10*f12 + f20*f22, 2) + 2*pow(f01*f02 + f11*f12 + f21*f22, 2));
    return out;

}

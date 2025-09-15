#include <iostream>
#include <cmath>

// Numerical approximation to cumulative standard normal distribution
// Handbook of Mathemathical functions (Abramowitz and Stegun)

double N(double x) 
{
    static double b1 =  0.31938153;
    static double b2 = -0.356563782;
    static double b3 =  1.781477937;
    static double b4 = -1.821255978;
    static double b5 =  1.330274429;
    static double p  =  0.2316419;
    static double c2 =  0.3989423;

// Approaching zero probability (P(x)= 0.000000001)

    if (x >  6.0) { return 1.0; };
    if (x < -6.0) { return 0.0; };

    double a = fabs(x);
    double t = 1.0/(1.0+a*p);
    double b = c2*exp((-x)*(x/2.0));
    double n = ((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t;

    n = 1.0 - b*n;
    if ( x < 0.0 ) n = 1.0 - n;

    return n;
}

// Black-Scholes call option price

double BS_call(double S, double K, double r, double T, double sigma) 
{
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);

    return S * N(d1) - K * exp(-r * T) * N(d2);
}

// Black-Scholes put option price

double BS_put(double S, double K, double r, double T, double sigma)
{
    return BS_call(S, K, r, T, sigma) + K * exp(-r * T) - S;
}

// Black-Scholes formula input parameters

int main() 
{
    double S, K, r, T, sigma;
    
    std::cout << "PARAMETERS" <<std::endl;
    std::cout << "Stock price: "; std::cin >> S;
    std::cout << "Strike price: "; std::cin >> K;
    std::cout << "Risk-free interest rate: "; std::cin >> r;
    std::cout << "Time to expiration: "; std::cin >> T;
    std::cout << "Volatility: "; std::cin >> sigma;

    double call_price = BS_call(S, K, r, T, sigma);
    double put_price = BS_put(S, K, r, T, sigma);
    
    std::cout << "\nBLACK-SCHOLES" << std::endl;
    std::cout << "Call Price: " << call_price << std::endl;
    std::cout << "Put Price: " << put_price << std::endl;

    return 0;
}

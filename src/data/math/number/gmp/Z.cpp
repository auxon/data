// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <data/math/number/gmp/Z.hpp>
#include <gmp/gmpxx.h>

namespace data {
    
    namespace math {
    
        namespace number {
            
            namespace gmp {
                bool Z::operator==(const Z& z) const {
                    return __gmp_binary_equal::eval(&MPZ, &z.MPZ);
                }
                    
                bool Z::operator<(const Z& z) const {
                    return __gmp_binary_less::eval(&MPZ, &z.MPZ);
                }
                    
                bool Z::operator>(const Z& z) const {
                    return __gmp_binary_greater::eval(&MPZ, &z.MPZ);
                }
                    
                bool Z::operator<=(const Z& z) const {
                    return !__gmp_binary_greater::eval(&MPZ, &z.MPZ);
                }
                    
                bool Z::operator>=(const Z& z) const {
                    return !__gmp_binary_less::eval(&MPZ, &z.MPZ);
                }
                    
                Z Z::operator+(const Z& z) const {
                    Z sum{};
                    __gmp_binary_plus::eval(&sum.MPZ, &MPZ, &z.MPZ);
                    return sum;
                }
                    
                Z& Z::operator+=(const Z& z) {
                    __gmp_binary_plus::eval(&MPZ, &MPZ, &z.MPZ);
                    return *this;
                }
                    
                Z Z::operator*(const Z& z) const {
                    Z prod{};
                    __gmp_binary_multiplies::eval(&prod.MPZ, &MPZ, &z.MPZ);
                    return prod;
                }
                    
                Z& Z::operator*=(const Z& z) {
                    __gmp_binary_multiplies::eval(&MPZ, &MPZ, &z.MPZ);
                    return *this;
                }
                    
                Z Z::operator^(uint n) const {
                    Z pow{};
                    mpz_pow_ui(&pow.MPZ, &MPZ, n);
                    return pow;
                }
                    
                Z& Z::operator^=(uint n) {
                    mpz_pow_ui(&MPZ, &MPZ, n);
                    return *this;
                }

                math::number::division<Z> Z::divide(const Z& z) const {
                    math::number::division<Z> qr{};
                    mpz_cdiv_qr(&qr.Quotient.MPZ, &qr.Remainder.MPZ, &MPZ, &z.MPZ);
                    return qr;
                }
                
            }
            
        }

        number::gmp::N square(number::gmp::Z &z) {
            return z * z;
        }
    }
    
}

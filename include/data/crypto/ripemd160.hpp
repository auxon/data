// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_CRYPTO_RIPEMD160
#define DATA_CRYPTO_RIPEMD160

#include <data/crypto/digest.hpp>

namespace data::ripemd160 {
    
    const uint32 size = 20;
    
    using digest = crypto::digest<size>;
    
    const digest Zero = digest{};
    
    digest hash(bytes&);
    
    template <uint32 n>
    digest hash(const std::array<byte, n>&);
    
    template <uint32 n>
    digest hash(const math::number::bounded::uint<n>&);

}

#endif


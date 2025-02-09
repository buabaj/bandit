#pragma once

#include <stdexcept>

namespace bandit {

class compression_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

} // namespace bandit
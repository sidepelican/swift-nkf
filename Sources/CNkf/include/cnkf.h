#pragma once

#include <stdio.h>
#include <vector>
#include <string>

#include <swift/bridging>

std::vector<uint8_t> nkf_convert(const std::vector<uint8_t>& input,
                                 const std::string& options) SWIFT_NAME(nkf_convert(input:options:));

using UInt8Vector = std::vector<uint8_t>;

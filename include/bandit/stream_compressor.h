#ifndef BANDIT_STREAM_COMPRESSOR_H
#define BANDIT_STREAM_COMPRESSOR_H

#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "error.h"

namespace bandit {

class StreamCompressor {
public:
    explicit StreamCompressor(int blockSize);

    void compressStream(std::istream& input, std::ostream& output);

    int getBlockSize() const noexcept { return blockSize; }

    StreamCompressor(const StreamCompressor&) = delete;
    StreamCompressor& operator=(const StreamCompressor&) = delete;

    StreamCompressor(StreamCompressor&&) noexcept = default;
    StreamCompressor& operator=(StreamCompressor&&) noexcept = default;

    ~StreamCompressor() = default;

private:
    std::vector<char> compressBlock(const char* data, int dataSize);
    int blockSize;
};

} // namespace bandit

#endif // BANDIT_STREAM_COMPRESSOR_H
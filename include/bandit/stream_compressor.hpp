#ifndef BANDIT_STREAM_COMPRESSOR_HPP
#define BANDIT_STREAM_COMPRESSOR_HPP

#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace bandit {

class compression_error : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

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

#endif // BANDIT_STREAM_COMPRESSOR_HPP
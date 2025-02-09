#ifndef BANDIT_STREAM_DECOMPRESSOR_H
#define BANDIT_STREAM_DECOMPRESSOR_H

#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace bandit {

class StreamDecompressor {
public:
    StreamDecompressor() = default;

    void decompressStream(std::istream& input, std::ostream& output, int maxBlockSize);

    StreamDecompressor(const StreamDecompressor&) = delete;
    StreamDecompressor& operator=(const StreamDecompressor&) = delete;

    StreamDecompressor(StreamDecompressor&&) noexcept = default;
    StreamDecompressor& operator=(StreamDecompressor&&) noexcept = default;

    ~StreamDecompressor() = default;

private:
    int decompressBlock(const char* compressedData, int compressedSize,
                       char* decompressedData, int decompressedSize);
};

} // namespace bandit

#endif // BANDIT_STREAM_DECOMPRESSOR_H
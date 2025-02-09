#include "bandit/stream_compressor.hpp"
#include "lz4.h"

namespace bandit {

StreamCompressor::StreamCompressor(int blockSize) {
    if (blockSize <= 0) {
        throw std::invalid_argument("Block size must be positive");
    }
    this->blockSize = blockSize;
}

std::vector<char> StreamCompressor::compressBlock(const char* data, int dataSize) {
    if (dataSize <= 0) {
        throw std::invalid_argument("Data size must be positive");
    }

    int maxDstSize = LZ4_compressBound(dataSize);
    if (maxDstSize <= 0) {
        throw compression_error("Failed to calculate compression bound");
    }

    std::vector<char> compressed(maxDstSize);
    int compressedSize = LZ4_compress_default(data, compressed.data(), dataSize, maxDstSize);
    if (compressedSize <= 0) {
        throw compression_error("Compression failed");
    }

    compressed.resize(compressedSize);
    return compressed;
}

void StreamCompressor::compressStream(std::istream& input, std::ostream& output) {
    if (!input || !output) {
        throw std::ios_base::failure("Invalid stream");
    }

    std::vector<char> buffer(blockSize);
    while (input) {
        input.read(buffer.data(), blockSize);
        std::streamsize bytesRead = input.gcount();

        if (bytesRead > 0) {
            try {
                auto compBlock = compressBlock(buffer.data(), static_cast<int>(bytesRead));
                int compBlockSize = static_cast<int>(compBlock.size());
                int origBlockSize = static_cast<int>(bytesRead);

                output.write(reinterpret_cast<const char*>(&compBlockSize), sizeof(compBlockSize));
                output.write(reinterpret_cast<const char*>(&origBlockSize), sizeof(origBlockSize));
                output.write(compBlock.data(), compBlockSize);

                if (!output) {
                    throw std::ios_base::failure("Failed to write compressed data");
                }
            } catch (const compression_error& e) {
                throw; // Re-throw compression errors
            } catch (const std::exception& e) {
                throw compression_error(std::string("Compression failed: ") + e.what());
            }
        }
    }

    if (input.bad()) {
        throw std::ios_base::failure("Error reading input stream");
    }
}

} // namespace bandit
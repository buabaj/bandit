#include "bandit/stream_decompressor.hpp"
#include "bandit/error.hpp"
#include <lz4.h>

namespace bandit
{

    int StreamDecompressor::decompressBlock(const char *compressedData, int compressedSize,
                                            char *decompressedData, int decompressedSize)
    {
        if (compressedSize <= 0 || decompressedSize <= 0)
        {
            throw std::invalid_argument("Invalid block sizes");
        }

        int actualSize = LZ4_decompress_safe(compressedData, decompressedData,
                                             compressedSize, decompressedSize);
        if (actualSize < 0)
        {
            throw compression_error("Decompression failed");
        }

        return actualSize;
    }

    void StreamDecompressor::decompressStream(std::istream &input, std::ostream &output, int maxBlockSize)
    {
        if (!input || !output)
        {
            throw std::ios_base::failure("Invalid stream");
        }
        if (maxBlockSize <= 0)
        {
            throw std::invalid_argument("Max block size must be positive");
        }

        while (input)
        {
            int compBlockSize = 0;
            int origBlockSize = 0;

            if (!input.read(reinterpret_cast<char *>(&compBlockSize), sizeof(compBlockSize)))
            {
                if (input.eof())
                    break;
                throw std::ios_base::failure("Failed to read compressed block size");
            }

            if (!input.read(reinterpret_cast<char *>(&origBlockSize), sizeof(origBlockSize)))
            {
                throw std::ios_base::failure("Failed to read original block size");
            }

            if (origBlockSize > maxBlockSize)
            {
                throw compression_error("Block size exceeds maximum allowed size");
            }

            std::vector<char> compBlock(compBlockSize);
            if (!input.read(compBlock.data(), compBlockSize))
            {
                throw std::ios_base::failure("Failed to read compressed data");
            }

            try
            {
                std::vector<char> decompressed(origBlockSize);
                int decompressedSize = decompressBlock(compBlock.data(), compBlockSize,
                                                       decompressed.data(), origBlockSize);
                output.write(decompressed.data(), decompressedSize);
                if (!output)
                {
                    throw std::ios_base::failure("Failed to write decompressed data");
                }
            }
            catch (const compression_error &e)
            {
                throw; // Re-throw compression errors
            }
            catch (const std::exception &e)
            {
                throw compression_error(std::string("Decompression failed: ") + e.what());
            }
        }
    }

} // namespace bandit
#include <bandit/stream_compressor.h>
#include <bandit/stream_decompressor.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    try {
        // Create sample data
        std::string input_data = "Hello, this is a test of the Bandit compression library. "
                                "This text will be compressed and then decompressed to demonstrate "
                                "the functionality of our LZ4-based streaming compression system.";
        std::istringstream input(input_data);
        std::ostringstream compressed;

        // Create compressor with 1024 byte block size
        bandit::StreamCompressor compressor(1024);

        // Compress the data
        std::cout << "Compressing data...\n";
        compressor.compressStream(input, compressed);

        // Get the compressed data
        std::string compressed_data = compressed.str();
        std::cout << "Original size: " << input_data.size() << " bytes\n";
        std::cout << "Compressed size: " << compressed_data.size() << " bytes\n";

        // Now decompress the data
        std::istringstream compressed_input(compressed_data);
        std::ostringstream decompressed;

        std::cout << "Decompressing data...\n";
        bandit::StreamDecompressor decompressor;
        decompressor.decompressStream(compressed_input, decompressed, 1024);

        // Verify the result
        std::string result = decompressed.str();
        std::cout << "Decompressed size: " << result.size() << " bytes\n";
        std::cout << "Decompression successful: " << (result == input_data ? "yes" : "no") << "\n";
        
        if (result == input_data) {
            std::cout << "\nDecompressed content matches original!\n";
            return 0;
        } else {
            std::cerr << "\nError: Decompressed content does not match original!\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
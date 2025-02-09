# Bandit

Bandit is a military-grade data compression library designed for high-stakes environments where efficiency, reliability, and speed are mission-critical. Built with modern C++17 and the LZ4 compression algorithm to deliver exceptional performance in bandwidth-constrained scenarios.

Just like [messhy](https://github.com/buabaj/messhy), This would have been combined and developed further into a more comprehensive project as my submission to the European Defense Hackathon.

## Key Capabilities

- **Ultra-Low Latency**: Optimized for real-time data streaming in tactical environments
- **Block-Based Processing**: Enables immediate data access without full decompression
- **Resource Efficient**: Minimal memory footprint for deployment in resource-constrained systems
- **Streaming Support**: Handles continuous data flows for surveillance and monitoring
- **Error Resilient**: Robust error handling for maintaining data integrity

## Military Applications

- **Tactical Communications**: Compress mission-critical data for secure, efficient transmission
- **Drone Operations**: Optimize bandwidth for real-time video and sensor data streams
- **Field Intelligence**: Process and transmit reconnaissance data with minimal delay
- **Secure Communications**: Compatible with military-grade encryption systems

## Technical Features

- Modern C++17 implementation
- LZ4 compression algorithm integration
- Exception-safe operation
- Move semantics support
- Configurable block sizes
- Thread-safe design

## Requirements

- C++17 compatible compiler
- LZ4 library
- CMake 3.14 or higher

## Installation

```bash
brew install lz4
brew install cmake
```

## Building

```bash
mkdir build && cd build
cmake ..
make
```

## Usage Example

check out `examples/compression_demo.cpp` for a simple usage example.


## Performance

Based on recent benchmarks:

- **Compression Ratio**: Average 5.48x (varies by data type)
- **Throughput**:
  - Compression: 55.68 MB/s
  - Decompression: 9.74 MB/s
- **Latency**: 6-7ms for 374KB blocks

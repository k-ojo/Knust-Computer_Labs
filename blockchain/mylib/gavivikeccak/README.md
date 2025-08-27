# GaviviKeccak

A lightweight C implementation of the Keccak cryptographic hash function, supporting multiple output sizes (SHA-3 family).

## Overview

This project implements the core Keccak algorithm used in the SHA-3 cryptographic hash function family. Keccak is a sponge construction that can produce hash outputs of various lengths (224, 256, 384, 512 bits).

## Features

- Support for multiple hash output sizes
- Configurable state width and capacity
- Memory-efficient buffer management
- Standard Keccak padding implementation
- Block-based message processing

## Supported Hash Variants

The implementation supports the following SHA-3 variants:
- **SHA3-224**: 224-bit output, 1152-bit rate
- **SHA3-256**: 256-bit output, 1088-bit rate  
- **SHA3-384**: 384-bit output, 832-bit rate
- **SHA3-512**: 512-bit output, 576-bit rate

## File Structure

```
├── gavivikeccak.h     # Header file with declarations
├── gavivikeccak.c     # Main implementation (your provided code)
└── README.md          # This file
```

## Core Functions

### `keccak_init(uint8_t *b, o*size size)`
Initializes the Keccak state with specified parameters:
- Sets up state dimensions based on security level
- Configures rate and capacity values
- Calculates number of rounds

### `buf_init()`
Allocates and initializes buffer structures:
- Creates rate and capacity buffers
- Returns pointer to allocated buffer structure
- Zeros out buffer memory

### `c_blocks(uint32_t **blocks, uint32_t *padded_msg, size_t m_len)`
Divides padded message into processing blocks:
- Splits message according to rate size
- Organizes data for sponge construction

### `pad(uint8_t *msg, uint32_t *padded_msg, size_t *l)`
Implements Keccak padding scheme:
- Adds required padding bits
- Ensures message length is multiple of block size
- Applies domain separation padding

## Usage Example

```c
#include "gavivikeccak.h"

int main() {
    uint8_t message[] = "Hello, World!";
    uint8_t hash_type = 1; // SHA3-256
    
    // Initialize Keccak
    keccak_init(&hash_type, SHA3_256);
    
    // Initialize buffers
    buf_t *buffer = buf_init();
    
    // Process message (padding and hashing)
    // ... additional implementation needed
    
    return 0;
}
```

## Dependencies

- Standard C library (`stdlib.h`, `string.h`)
- Custom header file `gavivikeccak.h`

## Building

```bash
gcc -o keccak gavivikeccak.c -std=c99
```

## Technical Details

### State Configuration
- Uses variable state width (25 * 2^l words)
- Configurable security levels (l = 0,1,2,3...)
- Round count: 12 + 2*l

### Memory Layout
- 32-bit word operations
- Little-endian byte ordering
- Dynamic buffer allocation

### Rate Values
- SHA3-224: 1152 bits
- SHA3-256: 1088 bits  
- SHA3-384: 832 bits
- SHA3-512: 576 bits

## Security Notes

This is a partial implementation focusing on core Keccak operations. For production use, ensure:
- Complete permutation function implementation
- Proper secure memory handling
- Thorough testing against test vectors
- Side-channel attack protections

## Contributing

1. Fork the repository
2. Create a feature branch
3. Add tests for new functionality
4. Submit a pull request

## License

[Specify your license here]

## References

- [NIST FIPS 202: SHA-3 Standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.202.pdf)
- [Keccak Team Website](https://keccak.team/)
- [The Keccak SHA-3 submission](https://keccak.team/files/Keccak-submission-3.pdf)

## Status

⚠️ **Note**: This appears to be a partial implementation. Additional functions may be needed for complete hash computation including the Keccak-f permutation function and final output extraction.
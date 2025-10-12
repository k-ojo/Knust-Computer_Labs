# Gavivi Cryptographic Library

A modular C implementation of essential cryptographic primitives including Elliptic Curve Cryptography (ECC), SHA-256, and Keccak/SHA-3 hash functions.

## Overview

The Gavivi Cryptographic Library provides clean, educational implementations of modern cryptographic algorithms. Each module is self-contained with its own build system, tests, and documentation, making it easy to use individual components or the entire library.

## 🔐 Modules

### 📈 ECC (Elliptic Curve Cryptography)
**Location:** `ECC/`
- **Implementation:** secp256k1 curve support
- **Features:** Point operations, key generation, ECDSA signatures
- **Files:** `gavivisecp256kl.c`, `gavivisecp256kl.h`

### 🔗 gavivisha256 (SHA-256 Hash Function)
**Location:** `gavivisha256/`
- **Implementation:** Complete SHA-256 hash algorithm
- **Features:** Bit operations, utilities, comprehensive testing
- **Components:**
  - Core hash implementation (`gavivisha256.c`)
  - Bit manipulation utilities (`bit_operations.c`)
  - General utilities (`utils.c`)
  - Hash wrapper (`gavivihash.c`)

### 🌊 gavivikeccak (Keccac/SHA-3 Hash Family)
**Location:** `gavivikeccak/`
- **Implementation:** Keccac sponge construction
- **Features:** Multiple output sizes (SHA3-224, 256, 384, 512)
- **Components:**
  - Core Keccac implementation (`gavivikeccak.c`)
  - Initialization and padding functions

## 📁 Repository Structure

```
gavivi-crypto/
├── README.md                    # This file
├── ECC/                        # Elliptic Curve Cryptography
│   ├── gavivisecp256kl.c       # secp256k1 implementation
│   ├── gavivisecp256kl.h       # ECC header file
│   └── Makefile                # ECC build configuration
├── gavivisha256/               # SHA-256 Hash Function
│   ├── Makefile                # SHA-256 build configuration
│   ├── README.md               # SHA-256 documentation
│   ├── src/                    # Source files
│   │   ├── gavivisha256.c      # Core SHA-256 implementation
│   │   ├── gavivisha256.h      # SHA-256 header
│   │   ├── gavivihash.c        # Hash wrapper functions
│   │   ├── bit_operations.c    # Bit manipulation utilities
│   │   └── utils.c             # General utilities
│   └── test/                   # Test suite
│       ├── 1-test.c            # Basic functionality tests
│       ├── 2-test.c            # Edge case tests
│       ├── 3-test.c            # Performance tests
│       └── 4-test.c            # Vector validation tests
└── gavivikeccac/               # Keccac/SHA-3 Hash Family
    ├── Makefile                # Keccac build configuration
    ├── README.md               # Keccac documentation
    ├── src/                    # Source files
    │   ├── gavivikeccac.c      # Core Keccac implementation
    │   ├── gavivikeccac.h      # Keccac header
    │   └── 1-test.c            # Development test file
    └── test/                   # Test suite
        └── 1-test.c            # Keccac functionality tests
```

## 🚀 Quick Start

### Building Individual Modules

Each module can be built independently:

```bash
# Build ECC module
cd ECC
make

# Build SHA-256 module
cd gavivisha256
make

# Build Keccac module
cd gavivikeccac
make
```

### Running Tests

```bash
# Test SHA-256 implementation
cd gavivisha256
make test
./test/1-test  # Basic tests
./test/2-test  # Edge cases
./test/3-test  # Performance
./test/4-test  # Test vectors

# Test Keccac implementation
cd gavivikeccac
make test
./test/1-test
```

### Usage Examples

#### SHA-256 Hashing
```c
#include "gavivisha256/src/gavivisha256.h"

int main() {
    uint8_t message[] = "Hello, World!";
    uint8_t hash[32];
    
    // Compute SHA-256 hash
    sha256_hash(message, strlen((char*)message), hash);
    
    // Print result
    for(int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    
    return 0;
}
```

#### Keccac/SHA-3 Hashing
```c
#include "gavivikeccac/src/gavivikeccac.h"

int main() {
    uint8_t message[] = "Hello, World!";
    uint8_t hash[32];
    
    // Initialize Keccac for SHA3-256
    keccac_init(1, SHA3_256);  // 256-bit output
    
    // Process message and get hash
    // ... (additional implementation needed)
    
    return 0;
}
```

#### ECC Operations
```c
#include "ECC/gavivisecp256kl.h"

int main() {
    // ECC key generation and operations
    // Implementation depends on your ECC module structure
    
    return 0;
}
```

## 🔧 Build Requirements

- **GCC** 4.8+ or compatible C compiler
- **Make** build system
- **Standard C Library**

### Compiler Flags
Each module uses appropriate compiler flags for optimization and debugging:
- `-Wall -Wextra` for comprehensive warnings
- `-O2` for optimization (release builds)
- `-g` for debugging information (debug builds)

## 📋 Module Details

### ECC Module Features
- **secp256k1 curve** implementation
- Elliptic curve point arithmetic
- Key pair generation
- Digital signature support (ECDSA)

### SHA-256 Module Features
- Complete **NIST FIPS 180-4** compliant implementation
- Optimized bit operations
- Comprehensive test coverage
- Utility functions for common operations
- Performance benchmarking

### Keccac Module Features
- **NIST FIPS 202** compliant SHA-3 implementation
- Support for multiple output sizes:
  - SHA3-224 (224-bit output)
  - SHA3-256 (256-bit output)  
  - SHA3-384 (384-bit output)
  - SHA3-512 (512-bit output)
- Sponge construction with configurable rates
- Memory-efficient buffer management

## 🧪 Testing Strategy

Each module includes comprehensive testing:

- **Unit Tests**: Individual function validation
- **Integration Tests**: Module-level functionality
- **Vector Tests**: Known Answer Tests (KAT) against standard test vectors
- **Edge Case Tests**: Boundary conditions and error handling
- **Performance Tests**: Benchmarking and optimization validation

## 📖 Documentation

Each module contains its own README.md with:
- Detailed API documentation
- Usage examples
- Implementation notes
- Performance characteristics
- Security considerations

## 🛡️ Security Considerations

- **Educational Purpose**: These implementations prioritize clarity and learning
- **Production Use**: Additional hardening may be required for production environments
- **Side-Channel Resistance**: Limited side-channel protections implemented
- **Input Validation**: Comprehensive bounds checking and validation

## 🎯 Use Cases

- **Educational**: Learning cryptographic algorithm implementation
- **Prototyping**: Quick cryptographic functionality for proof-of-concepts
- **Embedded Systems**: Lightweight crypto for resource-constrained devices
- **Research**: Baseline implementations for cryptographic research

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch for the specific module
3. Add tests for new functionality
4. Ensure all existing tests pass
5. Submit a pull request

## 📄 License

[Specify your license here - MIT, GPL, Apache, etc.]

## 🔗 References

- **ECC**: [SEC 2: Recommended Elliptic Curve Domain Parameters](https://www.secg.org/sec2-v2.pdf)
- **SHA-256**: [NIST FIPS 180-4: Secure Hash Standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)
- **Keccac/SHA-3**: [NIST FIPS 202: SHA-3 Standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.202.pdf)

## 📊 Status

| Module | Status | Tests | Documentation |
|--------|--------|-------|---------------|
| ECC | ✅ Implemented | ⏳ Pending | ⏳ Pending |
| SHA-256 | ✅ Complete | ✅ Comprehensive | ✅ Complete |
| Keccac | 🔄 In Progress | ✅ Basic | ✅ Complete |

---

*Gavivi Cryptographic Library - Educational implementations of essential cryptographic primitives*
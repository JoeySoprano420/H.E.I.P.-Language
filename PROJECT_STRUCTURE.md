# H.E.I.P. Project Structure

```
HEIP Lang/
│
├── src/
│   ├── main.cpp            # Main CLI entry point
│   ├── core/
│   │   ├── heip_types.h      # Core type definitions
│   │ ├── dodeca_compiler.h      # Dodecagramic compiler header
│   │   └── dodeca_compiler.cpp # Compiler implementation
│   └── runtime/
│├── frame_runtime.h        # FIR header
│       └── frame_runtime.cpp      # Runtime implementation
│
├── examples/
│   ├── demo.heip  # Comprehensive demo program
│   └── test.heip      # Simple test program
│
├── docs/
│   ├── LANGUAGE_GUIDE.md# Complete language documentation
│   └── TECHNICAL_ARCHITECTURE.md  # Deep technical dive
│
├── bin/      # Build output (created on build)
│   ├── Debug/
│   └── Release/
│
├── obj/         # Intermediate files (created on build)
│
├── HEIP_Lang_New.vcxproj       # Visual Studio project file
├── CMakeLists.txt        # CMake build configuration
├── build.ps1     # PowerShell build script
├── README.md   # Project overview and quick start
└── pack.cpp         # (Original placeholder file)
```

## Quick Start Guide

### 1. Build the Project

**Option A: Visual Studio**
```
Open HEIP_Lang_New.vcxproj in Visual Studio
Press F5 to build and run
```

**Option B: PowerShell Script**
```powershell
.\build.ps1
```

**Option C: CMake**
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### 2. Run the Compiler

```bash
# Show information
.\bin\Release\heip.exe info

# Compile a program
.\bin\Release\heip.exe compile examples\demo.heip demo.bin --stats

# Run compiled bytecode
.\bin\Release\heip.exe run demo.bin --stats
```

### 3. Write Your First Program

Create `hello.heip`:
```heip
Protocol main
    State message = "Hello, H.E.I.P.!"
    Instruct say message
End

Guide call main
```

Compile and run:
```bash
heip compile hello.heip hello.bin
heip run hello.bin
```

## Key Files Explained

### src/core/heip_types.h
- Defines all core language types
- Instruction, Protocol, Franchise, Overlay, etc.
- Opcode enumeration
- HELP context structures

### src/core/dodeca_compiler.cpp
- Implements dodecagramic-overlay compilation
- Exponential folding algorithms
- Symbol allocation and management
- HELP integration
- Self-healing compilation

### src/runtime/frame_runtime.cpp
- Frame Interpreter Runtime (FIR)
- Bytecode execution engine
- Self-healing runtime
- Checkpoint/restore system
- Forensic logging

### src/main.cpp
- CLI interface
- Command parsing
- User interaction
- Statistics display

## Build Targets

### Debug Build
- Full debug symbols
- No optimizations
- Extensive logging
- Good for development

### Release Build
- Optimized for speed
- Minimal logging
- Production-ready
- Recommended for benchmarking

## Testing

### Manual Testing
```bash
# Test basic compilation
heip compile examples\test.heip test.bin

# Test with statistics
heip compile examples\demo.heip demo.bin --stats

# Test runtime
heip run test.bin --stats
```

### Expected Output
```
Compilation successful!
Original size: XXX bytes
Compressed size: XX bytes
Compression ratio: 10.X x

Execution completed successfully
Instructions executed: XXX
Execution time: XXX µs
Uptime: 100.0%
```

## Common Issues

### Issue: "MSBuild not found"
**Solution:** Install Visual Studio 2019 or later with C++ desktop development

### Issue: "Cannot open source file"
**Solution:** Ensure you're in the project root directory

### Issue: "Compilation failed"
**Solution:** Check that all source files are present in src/

## Architecture Overview

```
┌─────────────────────────────────────────┐
│ H.E.I.P. Source Code (.heip)      │
└──────────────┬──────────────────────────┘
        │
   ▼
┌─────────────────────────────────────────┐
│ Dodecagramic Compiler      │
│ • Parse instructions  │
│ • Build protocols │
│ • Apply overlay compression             │
│ • Exponential folding         │
│ • HELP optimization    │
└──────────────┬──────────────────────────┘
               │
  ▼
┌─────────────────────────────────────────┐
│ Compressed Bytecode (.bin)              │
└──────────────┬──────────────────────────┘
         │
               ▼
┌─────────────────────────────────────────┐
│ Frame Interpreter Runtime (FIR)      │
│ • Load bytecode│
│ • Execute instructions       │
│ • Self-healing         │
│ • Forensic logging            │
└──────────────┬──────────────────────────┘
               │
          ▼
┌─────────────────────────────────────────┐
│ Program Output / Result          │
└─────────────────────────────────────────┘
```

## Key Features

### Dodecagramic-Overlay Compilation
- **10:1 compression ratio**
- Overlay symbols (0-9, a-b, c-z)
- Exponential folding
- Direct opcode mapping

### Self-Healing Runtime
- **>99.999% uptime**
- Automatic error recovery
- Checkpoint/restore
- Forensic ledger

### HELP System
- **Adaptive learning**
- Pattern recognition
- Optimization recommendations
- Heuristic scoring

### Frame Interpreter Runtime
- **Native-level performance**
- Stack-based VM
- Temporal state management
- Memory safety guarantees

## Next Steps

1. **Explore examples/** - Study the demo programs
2. **Read docs/** - Deep dive into language and architecture
3. **Write programs** - Create your own .heip files
4. **Experiment** - Try different features and optimizations
5. **Contribute** - Help improve the language

## Resources

- **Language Guide:** docs/LANGUAGE_GUIDE.md
- **Technical Docs:** docs/TECHNICAL_ARCHITECTURE.md
- **Examples:** examples/
- **README:** README.md

## Contact

For questions, suggestions, or issues:
- Email: violetaurac@icloud.com
- Project: HEIP Lang v4.0

---

**H.E.I.P. v4.0**  
*"Write like a human. Execute like a machine. Learn like an organism."*

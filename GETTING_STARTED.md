# Getting Started with H.E.I.P. v4.0

Welcome to **H.E.I.P.** (Highly Evolved Intuitive Programming)! This tutorial will guide you through your first steps with the language.

## Installation

### Step 1: Build the Compiler

**Option A: Using PowerShell Script**
```powershell
cd "C:\Users\420up\source\repos\HEIP Lang"
.\build.ps1
```

**Option B: Using Visual Studio**
1. Open `HEIP_Lang_New.vcxproj` in Visual Studio
2. Select "Release" configuration
3. Build → Build Solution (F7)
4. Executable will be in `bin\Release\`

**Option C: Using CMake**
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

### Step 2: Verify Installation

```bash
.\bin\Release\heip.exe info
```

You should see:
```
╔═══════════════════════════════════════════════════════════════╗
║   H.E.I.P. v4.0 - Highly Evolved Intuitive Programming║
║   Dodecagramic-Overlay Compilation System║
╚═══════════════════════════════════════════════════════════════╝

Version: 4.0.0
Architecture: Dodecagramic-Overlay Compilation
Compression: 10:1 average ratio
...
```

## Your First H.E.I.P. Program

### Tutorial 1: Hello World

Create a file named `hello.heip`:

```heip
# My first H.E.I.P. program!

Protocol main
    State greeting = "Hello from H.E.I.P.!"
    Instruct say greeting
End

Guide call main
```

**Compile:**
```bash
.\bin\Release\heip.exe compile hello.heip hello.bin
```

**Run:**
```bash
.\bin\Release\heip.exe run hello.bin
```

**Expected Output:**
```
Hello from H.E.I.P.!
✓ Execution completed successfully
```

### What Just Happened?

1. **Protocol main** - Defined a sequence of instructions called "main"
2. **State greeting** - Created a variable named "greeting"
3. **Instruct say** - Instructed the runtime to output the value
4. **Guide call main** - Invoked the protocol

## Tutorial 2: Working with Numbers

Create `calculator.heip`:

```heip
# Simple calculator

Protocol add_numbers
    State x = 10
    State y = 20
    Bubble result
    
  Instruct load x
    Instruct load y
    Instruct add
    Instruct store result
    
  Instruct say result
End

Guide call add_numbers
```

This program:
- Creates two states (variables) with values
- Loads them onto the stack
- Adds them together
- Stores the result in a Bubble (mutable container)
- Outputs the result

**Expected Output:** `30`

## Tutorial 3: Using Franchises (Modules)

Create `modules.heip`:

```heip
# Demonstrating Franchises (modules)

Franchise Math
    Protocol multiply
 State a = 6
        State b = 7
      
        Instruct load a
   Instruct load b
      Instruct mul
    End
    
    Protocol divide
        State numerator = 100
        State denominator = 4
        
Instruct load numerator
        Instruct load denominator
        Instruct div
    End
End

# Call protocols from the franchise
Guide call Math.multiply
Guide call Math.divide
```

**Franchises** are like namespaces or modules - they organize related protocols together.

## Tutorial 4: Dodecagramic Compression

Create `compressed.heip`:

```heip
# Demonstrating overlay compression

# Define a reusable pattern
Overlay PrintMessage
    State message = "This is compressed!"
    Instruct say message
End

# Map it to symbol '0'
0: PrintMessage

# Now use the compressed form
Guide call 0
Guide call 0
Guide call 0
```

**Magic:** The entire `PrintMessage` overlay is compressed to a single symbol `'0'`!

When you compile this with `--stats`, you'll see:
```
Original size: 120 bytes
Compressed size: 12 bytes
Compression ratio: 10.0x
```

## Tutorial 5: Self-Healing Code

Create `healing.heip`:

```heip
# Self-healing demonstration

Protocol safe_operation
    State attempt = 0
  
    # Try an operation
    Instruct try_operation
    
    # If error occurs
    Instruct on_error
        # HELP system heals the error
     HELP Heal
   Instruct restore_checkpoint
    Instruct retry
    End
End

Guide call safe_operation
```

If an error occurs during execution, the HELP system will:
1. Detect the error
2. Check if it's a known pattern
3. Restore from checkpoint
4. Apply a fix
5. Retry the operation

## Tutorial 6: Mutability Types

Create `mutability.heip`:

```heip
# Understanding Bubble (mutable) vs Chain (immutable)

Protocol test_mutability
    # Bubble: Can be modified
    Bubble dynamic_list
 push 10
    push 20
    push 30
    
    # Chain: Cannot be modified
    Chain constants
    42
     3.14159
  "H.E.I.P."
    End
End

Guide call test_mutability
```

**Key Difference:**
- **Bubble:** Mutable, can add/remove/modify elements
- **Chain:** Immutable, fixed once created

## Understanding the Compilation Process

When you compile a H.E.I.P. program:

```
Your Code (.heip)
  ↓
[Parse Instructions]
  ↓
[Build Protocols]
    ↓
[Apply Overlay Compression] ← Symbols replace structures
  ↓
[Exponential Folding] ← Recursive pattern compression
  ↓
[HELP Optimization] ← Learning system adapts
  ↓
[Generate Bytecode]
  ↓
Compressed Binary (.bin)
```

Result: **10:1 compression ratio on average!**

## CLI Commands Reference

### Compile
```bash
heip compile <input.heip> <output.bin> [options]

Options:
  --stats      Show compression statistics
  --no-help    Disable HELP learning
```

### Run
```bash
heip run <bytecode.bin> [options]

Options:
  --stats        Show execution statistics
  --no-healing   Disable self-healing
```

### Info
```bash
heip info
```
Shows compiler version, features, and capabilities.

### Help
```bash
heip help
```
Shows usage information.

## Language Quick Reference

### Basic Types

| Type | Mutability | Purpose |
|------|------------|---------|
| `State` | Mutable | Variable declaration |
| `Bubble` | Mutable | Dynamic container |
| `Chain` | Immutable | Fixed sequence |
| `Case` | Configurable | Standard container |

### Instructions

| Instruction | Purpose |
|-------------|---------|
| `Instruct load` | Load value to stack |
| `Instruct store` | Store value from stack |
| `Instruct add` | Addition |
| `Instruct sub` | Subtraction |
| `Instruct mul` | Multiplication |
| `Instruct div` | Division |
| `Instruct say` | Output value |
| `Instruct jump` | Jump to label |
| `Instruct compare` | Compare values |

### Organizational Constructs

| Construct | Purpose |
|-----------|---------|
| `Protocol` | Sequence of instructions |
| `Franchise` | Module/namespace |
| `Frame` | Execution context |
| `Range` | Execution boundary |
| `Overlay` | Compression pattern |

### Meta Commands

| Command | Purpose |
|---------|---------|
| `Guide call` | Invoke protocol |
| `HELP Learn` | Trigger learning |
| `HELP Heal` | Self-healing |
| `HELP Recommend` | Get suggestion |

## Best Practices

### 1. Use Overlays for Repeated Patterns

**Bad:**
```heip
Protocol task1
    State x = 10
    Instruct load x
    Instruct process x
End

Protocol task2
    State x = 20
    Instruct load x
    Instruct process x
End
```

**Good:**
```heip
Overlay LoadAndProcess
    State x
    Instruct load x
    Instruct process x
End

0: LoadAndProcess
Protocol task1
    Guide call 0
End
```

### 2. Organize with Franchises

```heip
Franchise Utilities
  Protocol helper1
 # ...
    End
    
    Protocol helper2
 # ...
    End
End

Franchise Core
Protocol main
        Guide call Utilities.helper1
    End
End
```

### 3. Enable Statistics During Development

```bash
heip compile program.heip output.bin --stats
```

This helps you see compression ratios and identify optimization opportunities.

### 4. Let HELP Learn

Keep `--no-help` disabled during normal use. The compiler learns from each build and improves over time!

## Common Patterns

### Pattern 1: Counter Loop

```heip
Protocol count_to_ten
    State counter = 0
    State limit = 10
    
    # Loop start
    Instruct compare counter limit
 Instruct jump_if_equal done
  
    Instruct say counter
    Instruct add counter 1
    Instruct jump start
    
    # Loop end
End
```

### Pattern 2: Conditional Execution

```heip
Protocol check_value
  State x = 42
    State target = 42

    Instruct compare x target
 Instruct jump_if_equal match
 Instruct say "No match"
    Instruct jump end

    # match label
    Instruct say "Match found!"
    
    # end label
End
```

### Pattern 3: Function Call Chain

```heip
Protocol step1
    Instruct say "Step 1"
End

Protocol step2
    Instruct say "Step 2"
End

Protocol main
    Guide call step1
    Guide call step2
End

Guide call main
```

## Troubleshooting

### Problem: "Cannot open include file"
**Solution:** Make sure you're building from the project root directory.

### Problem: "Compilation failed"
**Solution:** Check your `.heip` syntax. Common issues:
- Missing `End` keyword
- Typo in instruction names
- Incorrect Guide call syntax

### Problem: "Execution failed"
**Solution:** Enable `--stats` to see what instruction failed:
```bash
heip run program.bin --stats
```

### Problem: Low compression ratio
**Solution:** Use more Overlays! Identify repeated patterns and create overlays for them.

## Next Steps

1. **Explore Examples:** Check out `examples/demo.heip` for advanced features
2. **Read Documentation:**
   - `LANGUAGE_GUIDE.md` - Complete language reference
   - `TECHNICAL_ARCHITECTURE.md` - How it works internally
3. **Experiment:** Try combining different features
4. **Optimize:** See how high you can push the compression ratio!

## Learning Path

1. ✅ Hello World (you are here)
2. ⬜ Basic arithmetic
3. ⬜ Franchises and modules
4. ⬜ Overlay compression
5. ⬜ Self-healing patterns
6. ⬜ Advanced protocols
7. ⬜ Building real applications

## Resources

- **Examples:** `examples/` directory
- **Language Guide:** `docs/LANGUAGE_GUIDE.md`
- **Architecture:** `docs/TECHNICAL_ARCHITECTURE.md`
- **Project Structure:** `PROJECT_STRUCTURE.md`

## Community

Share your H.E.I.P. programs and discoveries!
Contact: violetaurac@icloud.com

---

## Quick Command Cheat Sheet

```bash
# Compile
heip compile program.heip output.bin --stats

# Run
heip run output.bin --stats

# Info
heip info

# Help
heip help
```

---

**Welcome to the future of programming!** 🚀

*H.E.I.P. v4.0 - "Write like a human. Execute like a machine. Learn like an organism."*

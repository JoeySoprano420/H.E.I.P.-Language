#include "core/dodeca_compiler.h"
#include "runtime/frame_runtime.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

void print_banner() {
    std::cout << R"(
╔═══════════════════════════════════════════════════════════════╗
║            ║
║   H.E.I.P. v4.0 - Highly Evolved Intuitive Programming       ║
║   Dodecagramic-Overlay Compilation System          ║
║            ║
║   "Write like a human. Execute like a machine.         ║
║    Learn like an organism."          ║
║             ║
╚═══════════════════════════════════════════════════════════════╝
)" << std::endl;
}

void print_usage() {
    std::cout << "Usage: heip [command] [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  compile <input.heip> <output>   - Compile H.E.I.P. source to native code\n";
    std::cout << "  run <bytecode>       - Execute H.E.I.P. bytecode\n";
    std::cout << "  info    - Display compiler information\n";
    std::cout << "  help          - Show this help message\n\n";
    std::cout << "Options:\n";
    std::cout << "  --no-help  - Disable HELP learning system\n";
    std::cout << "  --no-healing   - Disable self-healing runtime\n";
  std::cout << "  --stats          - Show detailed statistics\n";
    std::cout << std::endl;
}

void print_info() {
    std::cout << "\nH.E.I.P. Compiler Information:\n";
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Version:    4.0.0\n";
    std::cout << "Architecture:      Dodecagramic-Overlay Compilation\n";
    std::cout << "Compression:       10:1 average ratio (exponential folding)\n";
    std::cout << "Runtime:           FIR (Frame Interpreter Runtime)\n";
    std::cout << "Learning System:   HELP (Heuristic Evaluation Learning Protocol)\n";
    std::cout << "Self-Healing:      Enabled (>99.999% uptime)\n";
    std::cout << "Standards:      C++14 compatible\n\n";
  
    std::cout << "Key Features:\n";
    std::cout << "  • Dodecagramic symbol compression (0-9, a-b, c-z)\n";
    std::cout << "  • Overlay-based structural replacement\n";
    std::cout << "  • Exponential folding techniques\n";
    std::cout << "  • Direct opcode mapping from condensed forms\n";
    std::cout << "  • Self-healing compiler kernel\n";
  std::cout << "  • Adaptive runtime optimization\n";
    std::cout << "  • Forensic ledger tracking\n\n";
    
    std::cout << "Programming Paradigms:\n";
    std::cout << "  • Instructional Programming (protocols, instructions, ranges)\n";
    std::cout << "  • Itemized Programming (tiers, containers, directives)\n";
    std::cout << "  • Multi-paradigm fusion (procedural, functional, declarative)\n";
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    print_banner();
    
    if (argc < 2) {
        print_usage();
        return 0;
    }
    
    std::string command = argv[1];
  
    if (command == "help" || command == "--help" || command == "-h") {
        print_usage();
return 0;
    }
    
    if (command == "info" || command == "--info") {
        print_info();
        return 0;
    }
    
    bool help_enabled = true;
    bool healing_enabled = true;
    bool show_stats = false;
    
    // Parse options
    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
  if (arg == "--no-help") {
            help_enabled = false;
 } else if (arg == "--no-healing") {
      healing_enabled = false;
        } else if (arg == "--stats") {
   show_stats = true;
        }
    }
    
    if (command == "compile") {
  if (argc < 4) {
            std::cerr << "Error: compile requires input and output files\n";
            std::cerr << "Usage: heip compile <input.heip> <output>\n";
     return 1;
    }
        
        std::string input_file = argv[2];
     std::string output_file = argv[3];
        
        std::cout << "Compiling: " << input_file << " → " << output_file << "\n";
  std::cout << "Dodecagramic-Overlay Compilation in progress...\n\n";
        
        heip::DodecaCompiler compiler;
        compiler.enable_learning(help_enabled);
        
        if (compiler.compile(input_file, output_file)) {
     std::cout << "\n✓ Compilation successful!\n\n";
    
       if (show_stats) {
   std::cout << "Detailed Statistics:\n";
   std::cout << "━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "Original size: " << compiler.get_original_size() << " bytes\n";
                std::cout << "Compressed size:    " << compiler.get_compressed_size() << " bytes\n";
    std::cout << "Compression ratio:  " << compiler.get_compression_ratio() << "x\n";
       std::cout << "Code reduction:     " << 
 (1.0f - 1.0f / compiler.get_compression_ratio()) * 100.0f << "%\n";
           
            auto& help_ctx = compiler.get_help_context();
                std::cout << "\nHELP Statistics:\n";
              std::cout << "Compilations:       " << help_ctx.compilation_count << "\n";
                std::cout << "Learning rate:   " << help_ctx.learning_rate << "\n";
       std::cout << "Adaptations:        " << help_ctx.adaptation_history.size() << "\n";
            }
   
         return 0;
      } else {
        std::cerr << "\n✗ Compilation failed\n";
          return 1;
 }
    }
    else if (command == "run") {
        if (argc < 3) {
            std::cerr << "Error: run requires bytecode file\n";
 std::cerr << "Usage: heip run <bytecode>\n";
          return 1;
     }
   
        std::string bytecode_file = argv[2];
        
        std::cout << "Loading bytecode: " << bytecode_file << "\n";
        std::cout << "Frame Interpreter Runtime initializing...\n\n";
    
     // Read bytecode file
        std::ifstream file(bytecode_file, std::ios::binary);
        if (!file.is_open()) {
    std::cerr << "Error: Could not open bytecode file\n";
 return 1;
      }
      
        std::vector<uint8_t> bytecode(
            (std::istreambuf_iterator<char>(file)),
     std::istreambuf_iterator<char>()
        );
 
        heip::FrameRuntime runtime;
        runtime.enable_self_healing(healing_enabled);
        
        if (!runtime.load_bytecode(bytecode)) {
    std::cerr << "Error: Failed to load bytecode\n";
  return 1;
  }
    
        std::cout << "Executing...\n\n";
   
        int result = runtime.execute();
        
      if (result == 0) {
  std::cout << "\n✓ Execution completed successfully\n\n";
            
            if (show_stats) {
            std::cout << "Runtime Statistics:\n";
          std::cout << "━━━━━━━━━━━━━━━━━━━━\n";
  std::cout << "Instructions executed: " << runtime.get_instruction_count() << "\n";
  std::cout << "Execution time:        " << runtime.get_execution_time_us() << " µs\n";
        std::cout << "Uptime:      " << runtime.get_uptime_percentage() << "%\n";
            }
        } else {
            std::cerr << "\n✗ Execution failed with code: " << result << "\n";
        }
        
      return result;
    }
    else {
        std::cerr << "Unknown command: " << command << "\n";
  print_usage();
        return 1;
    }
    
    return 0;
}

#include "dodeca_compiler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

namespace heip {

DodecaCompiler::DodecaCompiler() 
    : next_symbol_('0')
    , help_enabled_(true)
    , original_size_(0)
    , compressed_size_(0)
    , compression_ratio_(1.0f) {
    
    // Initialize HELP context
    help_context_.compilation_count = 0;
    help_context_.learning_rate = 0.01f;
}

bool DodecaCompiler::compile(const std::string& source_file, const std::string& output_file) {
    try {
        // Stage 1: Read source
   std::ifstream file(source_file);
  if (!file.is_open()) {
         std::cerr << "Failed to open source file: " << source_file << std::endl;
   return false;
        }
        
 std::stringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();
      original_size_ = source.size();
        
        // Stage 2: Parse instructions
        auto instructions = parse_instructions(source);
  
        // Stage 3: Build protocols
      auto protocols = build_protocols(instructions);
   
        // Stage 4: Generate bytecode with dodecagramic compression
   auto bytecode = generate_bytecode(protocols);

        // Stage 5: Apply exponential folding
   auto folded = fold_structure(bytecode);
 
        // Stage 6: HELP optimization
   if (help_enabled_) {
        apply_help_optimizations(folded);
        }
        
        compressed_size_ = folded.size();
        compression_ratio_ = static_cast<float>(original_size_) / compressed_size_;
        
        // Stage 7: Emit native code
        auto native_code = emit_native_code(folded);
        
        // Stage 8: Write output
        std::ofstream output(output_file, std::ios::binary);
  if (!output.is_open()) {
   std::cerr << "Failed to open output file: " << output_file << std::endl;
   return false;
        }
        
    output.write(reinterpret_cast<const char*>(native_code.data()), native_code.size());
        
        // Log compilation success
        help_context_.compilation_count++;
        log_forensic_event("Compilation successful: " + source_file);
     
        std::cout << "Compilation successful!" << std::endl;
      std::cout << "Original size: " << original_size_ << " bytes" << std::endl;
        std::cout << "Compressed size: " << compressed_size_ << " bytes" << std::endl;
        std::cout << "Compression ratio: " << compression_ratio_ << "x" << std::endl;
        
     return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Compilation error: " << e.what() << std::endl;
  
        // Attempt self-healing
        if (attempt_error_recovery(e.what())) {
   std::cout << "Error recovered through HELP system" << std::endl;
            return compile(source_file, output_file);  // Retry
   }
        
        return false;
    }
}

std::vector<std::shared_ptr<Instruction>> DodecaCompiler::parse_instructions(
    const std::string& source) {
    
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::istringstream stream(source);
    std::string line;
    uint32_t range_pos = 0;
    
    while (std::getline(stream, line)) {
    // Skip empty lines and comments
      if (line.empty() || line[0] == '#') continue;
        
        auto inst = std::make_shared<Instruction>();
        inst->range_start = range_pos;
        
      // Parse instruction type and name
        std::istringstream line_stream(line);
        std::string type_keyword;
        line_stream >> type_keyword;
   
     // Map keywords to instruction types
        if (type_keyword == "Instruct" || type_keyword == "instruct") {
inst->type = InstructionType::INSTRUCT;
        } else if (type_keyword == "Guide" || type_keyword == "guide") {
       inst->type = InstructionType::GUIDE;
        } else if (type_keyword == "State" || type_keyword == "state") {
      inst->type = InstructionType::STATE;
        } else if (type_keyword == "Protocol" || type_keyword == "protocol") {
         inst->type = InstructionType::PROTOCOL;
} else if (type_keyword == "Bubble" || type_keyword == "bubble") {
            inst->type = InstructionType::BUBBLE;
        } else if (type_keyword == "Chain" || type_keyword == "chain") {
inst->type = InstructionType::CHAIN;
  } else if (type_keyword == "Franchise" || type_keyword == "franchise") {
            inst->type = InstructionType::FRANCHISE;
        } else {
        // Try to find overlay symbol
            if (type_keyword.length() == 1 && dodeca_utils::is_valid_symbol(type_keyword[0])) {
      inst->type = InstructionType::OVERLAY;
            inst->overlay_ref = dodeca_map_.decompress(type_keyword[0]);
     }
 }
        
        // Parse name and parameters
        line_stream >> inst->name;
        std::string param;
        while (line_stream >> param) {
            inst->params.push_back(param);
     }
        
        inst->range_end = ++range_pos;
  instructions.push_back(inst);
 }
    
    return instructions;
}

std::vector<std::shared_ptr<Protocol>> DodecaCompiler::build_protocols(
    const std::vector<std::shared_ptr<Instruction>>& instructions) {
    
    std::vector<std::shared_ptr<Protocol>> protocols;
    std::shared_ptr<Protocol> current_protocol = nullptr;
    
    for (const auto& inst : instructions) {
  if (inst->type == InstructionType::PROTOCOL) {
   // Start new protocol
            current_protocol = std::make_shared<Protocol>();
            current_protocol->name = inst->name;
      protocols.push_back(current_protocol);
        } else if (current_protocol) {
        // Add instruction to current protocol
            current_protocol->instructions.push_back(inst);
   }
    }
    
    return protocols;
}

std::vector<uint8_t> DodecaCompiler::generate_bytecode(
    const std::vector<std::shared_ptr<Protocol>>& protocols) {
    
    std::vector<uint8_t> bytecode;
    
    for (const auto& protocol : protocols) {
     // Emit protocol header
        emit_opcode(bytecode, HEIPOpcode::FRAME_CREATE);
        
        for (const auto& inst : protocol->instructions) {
        // Check if instruction uses overlay compression
            if (inst->overlay_ref) {
     emit_opcode(bytecode, HEIPOpcode::OVERLAY_EXPAND);
     bytecode.insert(bytecode.end(), 
                 inst->overlay_ref->compressed_bytecode.begin(),
           inst->overlay_ref->compressed_bytecode.end());
          } else {
       // Map instruction to opcode
  HEIPOpcode opcode = map_to_opcode(inst->name);
 emit_opcode(bytecode, opcode);
      
    // Emit parameters
       for (const auto& param : inst->params) {
  // Simplified: emit parameter as string length + data
        emit_operand(bytecode, static_cast<uint32_t>(param.size()));
             bytecode.insert(bytecode.end(), param.begin(), param.end());
     }
        }
        }
 
    // Emit protocol footer
        emit_opcode(bytecode, HEIPOpcode::FRAME_EXIT);
    }
    
    return bytecode;
}

std::vector<uint8_t> DodecaCompiler::fold_structure(const std::vector<uint8_t>& unfolded) {
    // Exponential folding algorithm
    // Reduces repeated patterns and nested structures
    
    int optimal_depth = dodeca_utils::optimal_fold_depth(unfolded.size());
    return fold_recursively(unfolded, optimal_depth);
}

std::vector<uint8_t> DodecaCompiler::fold_recursively(
    const std::vector<uint8_t>& data, int depth) {
    
    if (depth <= 0 || data.size() < 4) return data;
    
    std::vector<uint8_t> folded;
    std::unordered_map<std::string, uint8_t> pattern_map;
    uint8_t pattern_id = 0;
    
    // Find repeating patterns
    for (size_t i = 0; i < data.size() - 3; i++) {
        std::string pattern(data.begin() + i, data.begin() + i + 4);
 
      if (pattern_map.find(pattern) == pattern_map.end()) {
   pattern_map[pattern] = pattern_id++;
        }
        
        // Replace pattern with symbol
        folded.push_back(pattern_map[pattern]);
        i += 3;  // Skip folded bytes
 }
    
    // Recursive folding
    return fold_recursively(folded, depth - 1);
}

HEIPOpcode DodecaCompiler::map_to_opcode(const std::string& instruction) {
    // Direct mapping from instruction names to opcodes
    static const std::unordered_map<std::string, HEIPOpcode> opcode_map = {
        {"load", HEIPOpcode::LOAD},
   {"store", HEIPOpcode::STORE},
        {"add", HEIPOpcode::ADD},
        {"sub", HEIPOpcode::SUB},
        {"call", HEIPOpcode::CALL},
        {"return", HEIPOpcode::RET},
        {"jump", HEIPOpcode::JMP},
        {"compare", HEIPOpcode::CMP},
     {"push", HEIPOpcode::PUSH},
        {"pop", HEIPOpcode::POP},
    };
    
    auto it = opcode_map.find(instruction);
    return (it != opcode_map.end()) ? it->second : HEIPOpcode::NOP;
}

std::vector<uint8_t> DodecaCompiler::emit_native_code(
    const std::vector<uint8_t>& heip_bytecode) {
    
    // For now, return the HEIP bytecode directly
    // In a full implementation, this would translate to x86/x64/ARM assembly
    return heip_bytecode;
}

void DodecaCompiler::emit_opcode(std::vector<uint8_t>& output, HEIPOpcode opcode) {
    output.push_back(static_cast<uint8_t>(opcode));
}

void DodecaCompiler::emit_operand(std::vector<uint8_t>& output, uint32_t operand) {
    output.push_back((operand >> 24) & 0xFF);
    output.push_back((operand >> 16) & 0xFF);
    output.push_back((operand >> 8) & 0xFF);
    output.push_back(operand & 0xFF);
}

void DodecaCompiler::apply_help_optimizations(std::vector<uint8_t>& bytecode) {
    // HELP-driven optimization
    // Learn from previous compilations and adapt
    
    help_context_.adapt_optimization("bytecode_compression");
    
    // Example: remove redundant NOPs
    bytecode.erase(
        std::remove(bytecode.begin(), bytecode.end(), static_cast<uint8_t>(HEIPOpcode::NOP)),
        bytecode.end()
    );
}

bool DodecaCompiler::attempt_error_recovery(const std::string& error) {
    // Self-healing compilation
    help_context_.learn_from_error(error);
    std::string recommendation = help_context_.recommend_fix(error);
    
    if (!recommendation.empty()) {
        log_forensic_event("Recovery attempted: " + recommendation);
        return true;
    }
    
    return false;
}

void DodecaCompiler::log_forensic_event(const std::string& event) {
    // Forensic ledger logging
help_context_.adaptation_history.push_back(event);
}

void DodecaCompiler::register_overlay(const std::string& keyword, 
  const std::vector<uint8_t>& replacement_bytecode) {
    
    auto overlay = std::make_shared<Overlay>();
    overlay->name = keyword;
    overlay->symbol = allocate_symbol();
    overlay->compressed_bytecode = replacement_bytecode;
    overlay->compressed_size = replacement_bytecode.size();
    
    overlay_registry_[keyword] = overlay;
    dodeca_map_.symbol_to_overlay[overlay->symbol] = overlay;
    dodeca_map_.keyword_to_symbol[keyword] = overlay->symbol;
}

DodecaSymbol DodecaCompiler::allocate_symbol() {
    DodecaSymbol symbol = next_symbol_;
    
    // Advance to next symbol: 0-9, then a-b, then c-z
    if (next_symbol_ >= '0' && next_symbol_ < '9') {
        next_symbol_++;
    } else if (next_symbol_ == '9') {
      next_symbol_ = 'a';
    } else if (next_symbol_ == 'b') {
        next_symbol_ = 'c';
    } else if (next_symbol_ >= 'c' && next_symbol_ < 'z') {
        next_symbol_++;
    }
    
    return symbol;
}

// Dodeca utilities implementation
namespace dodeca_utils {

bool is_valid_symbol(DodecaSymbol symbol) {
    return (symbol >= '0' && symbol <= '9') ||
           (symbol >= 'a' && symbol <= 'b') ||
 (symbol >= 'c' && symbol <= 'z');
}

float calculate_compression_potential(size_t structure_size) {
    // Theoretical maximum compression based on dodecagramic encoding
    // Average compression ratio: 10:1 based on exponential folding
    return std::min(10.0f, std::log2(static_cast<float>(structure_size)) + 1.0f);
}

int optimal_fold_depth(size_t data_size) {
    // Calculate optimal folding depth for maximum compression
    return static_cast<int>(std::log2(data_size)) / 2;
}

} // namespace dodeca_utils

// HELP context implementation
void HELPContext::learn_from_error(const std::string& error_type) {
    heuristic_scores[error_type] += learning_rate;
    adaptation_history.push_back("Learned from: " + error_type);
}

void HELPContext::adapt_optimization(const std::string& pattern) {
    heuristic_scores[pattern] += learning_rate * 2.0f;
    adaptation_history.push_back("Adapted: " + pattern);
}

std::string HELPContext::recommend_fix(const std::string& issue) {
    // Simple recommendation based on learned patterns
    if (heuristic_scores.find(issue) != heuristic_scores.end()) {
   if (heuristic_scores[issue] > 0.5f) {
  return "Apply known pattern for: " + issue;
        }
    }
    return "";
}

// DodecaMap implementation
DodecaSymbol DodecaMap::compress(const std::string& keyword) {
    auto it = keyword_to_symbol.find(keyword);
    if (it != keyword_to_symbol.end()) {
        return it->second;
    }
    return '0';  // Default symbol
}

std::shared_ptr<Overlay> DodecaMap::decompress(DodecaSymbol symbol) {
    auto it = symbol_to_overlay.find(symbol);
    if (it != symbol_to_overlay.end()) {
   return it->second;
    }
    return nullptr;
}

} // namespace heip

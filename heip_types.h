#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cstdint>

namespace heip {

// Dodecagramic symbol type (0-9, a-b, then c-z as needed)
using DodecaSymbol = char;

// Core types for the H.E.I.P. language
enum class InstructionType {
  INSTRUCT,      // Basic instruction
    GUIDE,// Protocol reference
    STATE,         // State declaration
  BUBBLE,        // Mutable container
    CHAIN,         // Immutable sequence
    CASE,   // Standardized container
    FRANCHISE,     // Organizational structure (namespace/module)
    PROTOCOL,      // Instruction sequence
    RANGE,         // Contextual execution boundary
    OVERLAY,       // Symbolic compression keyword
    SUPERLATIVE    // Dynamic best-reference resolver
};

enum class MutabilityType {
    MUTABLE,       // Bubble, Collection
    IMMUTABLE      // Chain, Set
};

// Opcode mapping for exponential compression
enum class HEIPOpcode : uint8_t {
    NOP = 0x00,
LOAD = 0x01,
    STORE = 0x02,
    ADD = 0x03,
    SUB = 0x04,
    MUL = 0x05,
    DIV = 0x06,
    CALL = 0x07,
    RET = 0x08,
    JMP = 0x09,
    JZ = 0x0A,
    JNZ = 0x0B,
    CMP = 0x0C,
    PUSH = 0x0D,
    POP = 0x0E,
    ALLOC = 0x0F,
    FREE = 0x10,
    // HELP-specific opcodes
    HELP_LEARN = 0x20,
    HELP_ADAPT = 0x21,
    HELP_HEAL = 0x22,
    HELP_RECOMMEND = 0x23,
    // Frame runtime opcodes
    FRAME_CREATE = 0x30,
    FRAME_ENTER = 0x31,
    FRAME_EXIT = 0x32,
    STATE_SAVE = 0x33,
    STATE_RESTORE = 0x34,
    // Overlay compressed opcodes (exponential forms)
    OVERLAY_EXPAND = 0x40,
    SYMBOL_RESOLVE = 0x41
};

// Overlay definition - replaces entire structures with symbols
struct Overlay {
    std::string name;
    DodecaSymbol symbol;
    std::vector<uint8_t> compressed_bytecode;  // Exponentially folded form
    size_t original_size;
    size_t compressed_size;
    
    float compression_ratio() const {
        return original_size > 0 ? 
            static_cast<float>(original_size) / compressed_size : 1.0f;
    }
};

// Instruction node in the protocol chain
struct Instruction {
    InstructionType type;
  std::string name;
    std::vector<std::string> params;
    std::vector<uint8_t> bytecode;
    uint32_t range_start;
    uint32_t range_end;
    std::shared_ptr<Overlay> overlay_ref;  // If this instruction uses overlay compression
};

// Protocol - sequence of instructions forming behavioral etiquette
struct Protocol {
  std::string name;
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::unordered_map<std::string, std::string> state_variables;
    uint32_t range_scope;
};

// Franchise - organizational structure with delegation
struct Franchise {
    std::string name;
    std::vector<std::shared_ptr<Protocol>> protocols;
    std::unordered_map<std::string, std::shared_ptr<Franchise>> sub_franchises;
};

// State container for runtime
struct State {
    std::string name;
    std::unordered_map<std::string, void*> variables;
    MutabilityType mutability;
    bool is_traced;  // For forensic ledger
};

// Range - contextual execution boundary
struct Range {
    uint32_t start;
    uint32_t end;
    std::string context;
    std::vector<std::shared_ptr<State>> states;
};

// Dodecagramic compression mapping
struct DodecaMap {
    std::unordered_map<DodecaSymbol, std::shared_ptr<Overlay>> symbol_to_overlay;
    std::unordered_map<std::string, DodecaSymbol> keyword_to_symbol;
    
 // Convert complex structures to dodecagramic symbols
    DodecaSymbol compress(const std::string& keyword);
    std::shared_ptr<Overlay> decompress(DodecaSymbol symbol);
};

// HELP context for learning and adaptation
struct HELPContext {
    uint64_t compilation_count;
    float learning_rate;
    std::vector<std::string> adaptation_history;
  std::unordered_map<std::string, float> heuristic_scores;
    
    void learn_from_error(const std::string& error_type);
    void adapt_optimization(const std::string& pattern);
    std::string recommend_fix(const std::string& issue);
};

// Frame - execution context with temporal state
struct Frame {
    std::string name;
    std::vector<std::shared_ptr<Protocol>> active_protocols;
    std::shared_ptr<State> local_state;
    std::shared_ptr<Range> execution_range;
    uint64_t frame_id;
  uint64_t timestamp;
    
    // Self-healing properties
    bool can_recover;
    std::vector<uint8_t> checkpoint_state;
};

} // namespace heip

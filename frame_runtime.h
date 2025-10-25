#pragma once
#include "../core/heip_types.h"
#include <vector>
#include <memory>
#include <chrono>

namespace heip {

// Frame Interpreter Runtime (FIR)
// The execution engine for H.E.I.P. compiled code
class FrameRuntime {
public:
    FrameRuntime();
    ~FrameRuntime();
    
    // Load and execute bytecode
    bool load_bytecode(const std::vector<uint8_t>& bytecode);
    int execute();
    
    // Frame management
    std::shared_ptr<Frame> create_frame(const std::string& name);
    void enter_frame(std::shared_ptr<Frame> frame);
    void exit_frame();
    std::shared_ptr<Frame> current_frame() const { return current_frame_; }
  
    // State management
    void save_state();
  void restore_state();
    void create_checkpoint();
    
    // Self-healing runtime
    void enable_self_healing(bool enable) { self_healing_enabled_ = enable; }
    bool attempt_recovery();
    
    // Range execution
    void set_execution_range(uint32_t start, uint32_t end);
    bool in_range(uint32_t position) const;

    // Statistics
    uint64_t get_instruction_count() const { return instruction_count_; }
    uint64_t get_execution_time_us() const;
    float get_uptime_percentage() const { return uptime_percentage_; }
    
private:
    // Bytecode execution
    std::vector<uint8_t> bytecode_;
    size_t program_counter_;
    
    // Frame stack
    std::vector<std::shared_ptr<Frame>> frame_stack_;
    std::shared_ptr<Frame> current_frame_;
    uint64_t next_frame_id_;
 
    // State checkpointing
    std::vector<std::vector<uint8_t>> checkpoint_stack_;
    
    // Execution engine
    bool execute_instruction(uint8_t opcode);
    bool execute_heip_opcode(HEIPOpcode opcode);
    
    // Stack and memory
    std::vector<uint32_t> stack_;
    std::vector<uint8_t> memory_;
    
    // Self-healing
    bool self_healing_enabled_;
    std::vector<std::string> error_log_;
    bool handle_execution_error(const std::string& error);
    
    // Performance tracking
    uint64_t instruction_count_;
    std::chrono::high_resolution_clock::time_point start_time_;
    std::chrono::high_resolution_clock::time_point end_time_;
    float uptime_percentage_;
    
  // Forensic ledger
    void log_execution_event(const std::string& event);
    std::vector<std::string> execution_log_;
};

} // namespace heip

#include "frame_runtime.h"
#include <iostream>
#include <stdexcept>

namespace heip {

FrameRuntime::FrameRuntime()
  : program_counter_(0)
    , next_frame_id_(1)
    , self_healing_enabled_(true)
    , instruction_count_(0)
    , uptime_percentage_(100.0f) {
    
    start_time_ = std::chrono::high_resolution_clock::now();
    
    // Allocate initial memory (1MB)
 memory_.resize(1024 * 1024);
    
    // Create root frame
    current_frame_ = create_frame("__root__");
}

FrameRuntime::~FrameRuntime() {
    end_time_ = std::chrono::high_resolution_clock::now();
}

bool FrameRuntime::load_bytecode(const std::vector<uint8_t>& bytecode) {
    bytecode_ = bytecode;
    program_counter_ = 0;
    log_execution_event("Bytecode loaded: " + std::to_string(bytecode.size()) + " bytes");
    return true;
}

int FrameRuntime::execute() {
  try {
  log_execution_event("Execution started");
        
      while (program_counter_ < bytecode_.size()) {
    uint8_t opcode = bytecode_[program_counter_++];
      
        if (!execute_instruction(opcode)) {
          if (self_healing_enabled_ && attempt_recovery()) {
        log_execution_event("Self-healing recovery successful");
     continue;
 }
    std::cerr << "Execution failed at PC: " << program_counter_ - 1 << std::endl;
           return 1;
      }
            
      instruction_count_++;
       
            // Check execution range
     if (!in_range(static_cast<uint32_t>(program_counter_))) {
        log_execution_event("Execution out of range");
  break;
}
 }
        
    log_execution_event("Execution completed successfully");
 return 0;
 
    } catch (const std::exception& e) {
        std::cerr << "Runtime exception: " << e.what() << std::endl;

        if (self_healing_enabled_ && attempt_recovery()) {
            log_execution_event("Exception recovered");
  return execute();  // Retry
        }
        
        return 1;
    }
}

bool FrameRuntime::execute_instruction(uint8_t opcode) {
    HEIPOpcode heip_opcode = static_cast<HEIPOpcode>(opcode);
    return execute_heip_opcode(heip_opcode);
}

bool FrameRuntime::execute_heip_opcode(HEIPOpcode opcode) {
 switch (opcode) {
      case HEIPOpcode::NOP:
     break;
            
        case HEIPOpcode::LOAD: {
 // Load value onto stack
      if (program_counter_ + 4 > bytecode_.size()) return false;
    uint32_t value = (bytecode_[program_counter_] << 24) |
                 (bytecode_[program_counter_ + 1] << 16) |
           (bytecode_[program_counter_ + 2] << 8) |
           bytecode_[program_counter_ + 3];
     program_counter_ += 4;
         stack_.push_back(value);
          break;
        }
        
    case HEIPOpcode::STORE: {
     // Store top of stack to memory
      if (stack_.empty()) return false;
      uint32_t value = stack_.back();
            stack_.pop_back();
         
     if (program_counter_ + 4 > bytecode_.size()) return false;
       uint32_t address = (bytecode_[program_counter_] << 24) |
      (bytecode_[program_counter_ + 1] << 16) |
           (bytecode_[program_counter_ + 2] << 8) |
          bytecode_[program_counter_ + 3];
            program_counter_ += 4;
            
       if (address + 4 > memory_.size()) return false;
    memory_[address] = (value >> 24) & 0xFF;
        memory_[address + 1] = (value >> 16) & 0xFF;
            memory_[address + 2] = (value >> 8) & 0xFF;
  memory_[address + 3] = value & 0xFF;
            break;
     }
        
        case HEIPOpcode::ADD: {
          if (stack_.size() < 2) return false;
            uint32_t b = stack_.back(); stack_.pop_back();
            uint32_t a = stack_.back(); stack_.pop_back();
   stack_.push_back(a + b);
        break;
        }
     
    case HEIPOpcode::SUB: {
     if (stack_.size() < 2) return false;
            uint32_t b = stack_.back(); stack_.pop_back();
            uint32_t a = stack_.back(); stack_.pop_back();
      stack_.push_back(a - b);
   break;
        }
     
        case HEIPOpcode::MUL: {
    if (stack_.size() < 2) return false;
   uint32_t b = stack_.back(); stack_.pop_back();
   uint32_t a = stack_.back(); stack_.pop_back();
            stack_.push_back(a * b);
  break;
        }
        
        case HEIPOpcode::CALL: {
   // Save return address and jump
            if (program_counter_ + 4 > bytecode_.size()) return false;
       uint32_t target = (bytecode_[program_counter_] << 24) |
             (bytecode_[program_counter_ + 1] << 16) |
              (bytecode_[program_counter_ + 2] << 8) |
   bytecode_[program_counter_ + 3];
  program_counter_ += 4;
       
          stack_.push_back(static_cast<uint32_t>(program_counter_));
     program_counter_ = target;
  break;
  }
        
        case HEIPOpcode::RET: {
  if (stack_.empty()) return false;
            program_counter_ = stack_.back();
    stack_.pop_back();
         break;
        }
        
        case HEIPOpcode::JMP: {
   if (program_counter_ + 4 > bytecode_.size()) return false;
        uint32_t target = (bytecode_[program_counter_] << 24) |
           (bytecode_[program_counter_ + 1] << 16) |
        (bytecode_[program_counter_ + 2] << 8) |
           bytecode_[program_counter_ + 3];
       program_counter_ = target;
     break;
        }
 
        case HEIPOpcode::PUSH: {
            if (stack_.empty()) return false;
         // Push is implicit in our stack machine
        break;
        }
      
        case HEIPOpcode::POP: {
            if (stack_.empty()) return false;
            stack_.pop_back();
            break;
        }
        
        case HEIPOpcode::FRAME_CREATE: {
      create_checkpoint();
            log_execution_event("Frame created");
          break;
        }
  
        case HEIPOpcode::FRAME_EXIT: {
    log_execution_event("Frame exited");
   break;
        }
     
        case HEIPOpcode::HELP_LEARN: {
       log_execution_event("HELP learning invoked");
 break;
        }
        
        case HEIPOpcode::HELP_HEAL: {
  log_execution_event("HELP self-healing triggered");
      attempt_recovery();
            break;
        }
        
        case HEIPOpcode::OVERLAY_EXPAND: {
     // Overlay expansion handled during compilation
  log_execution_event("Overlay expanded");
            break;
   }
        
        default:
      return false;
    }
  
    return true;
}

std::shared_ptr<Frame> FrameRuntime::create_frame(const std::string& name) {
    auto frame = std::make_shared<Frame>();
    frame->name = name;
    frame->frame_id = next_frame_id_++;
    frame->timestamp = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
    frame->can_recover = true;
    
    frame_stack_.push_back(frame);
    return frame;
}

void FrameRuntime::enter_frame(std::shared_ptr<Frame> frame) {
    current_frame_ = frame;
    log_execution_event("Entered frame: " + frame->name);
}

void FrameRuntime::exit_frame() {
    if (!frame_stack_.empty()) {
        frame_stack_.pop_back();
    }
    
    if (!frame_stack_.empty()) {
  current_frame_ = frame_stack_.back();
    }
    
  log_execution_event("Exited frame");
}

void FrameRuntime::save_state() {
    // Save current execution state
  std::vector<uint8_t> state;
    
    // Save program counter
    state.push_back((program_counter_ >> 24) & 0xFF);
    state.push_back((program_counter_ >> 16) & 0xFF);
    state.push_back((program_counter_ >> 8) & 0xFF);
    state.push_back(program_counter_ & 0xFF);
    
// Save stack
    for (uint32_t val : stack_) {
  state.push_back((val >> 24) & 0xFF);
     state.push_back((val >> 16) & 0xFF);
        state.push_back((val >> 8) & 0xFF);
        state.push_back(val & 0xFF);
    }
    
    if (current_frame_) {
     current_frame_->checkpoint_state = state;
    }
}

void FrameRuntime::restore_state() {
    if (current_frame_ && !current_frame_->checkpoint_state.empty()) {
        const auto& state = current_frame_->checkpoint_state;
        
        // Restore program counter
        program_counter_ = (state[0] << 24) | (state[1] << 16) | 
          (state[2] << 8) | state[3];
        
        // Restore stack
     stack_.clear();
    for (size_t i = 4; i < state.size(); i += 4) {
            uint32_t val = (state[i] << 24) | (state[i+1] << 16) | 
             (state[i+2] << 8) | state[i+3];
 stack_.push_back(val);
    }
        
     log_execution_event("State restored from checkpoint");
    }
}

void FrameRuntime::create_checkpoint() {
    save_state();
    log_execution_event("Checkpoint created");
}

bool FrameRuntime::attempt_recovery() {
    log_execution_event("Attempting self-healing recovery");
    
    // Try to restore from checkpoint
    restore_state();
    
    // Clear error state
    error_log_.clear();
    
    // Recovery successful if we have a valid checkpoint
    return current_frame_ && !current_frame_->checkpoint_state.empty();
}

void FrameRuntime::set_execution_range(uint32_t start, uint32_t end) {
    if (current_frame_) {
        auto range = std::make_shared<Range>();
        range->start = start;
        range->end = end;
        current_frame_->execution_range = range;
    }
}

bool FrameRuntime::in_range(uint32_t position) const {
    if (current_frame_ && current_frame_->execution_range) {
        return position >= current_frame_->execution_range->start &&
               position <= current_frame_->execution_range->end;
    }
    return true;  // No range restriction
}

uint64_t FrameRuntime::get_execution_time_us() const {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
 end_time_ - start_time_
    );
    return static_cast<uint64_t>(duration.count());
}

void FrameRuntime::log_execution_event(const std::string& event) {
    execution_log_.push_back(event);
}

bool FrameRuntime::handle_execution_error(const std::string& error) {
    error_log_.push_back(error);
    
    // Update uptime percentage
    float error_rate = static_cast<float>(error_log_.size()) / 
          static_cast<float>(instruction_count_ + 1);
    uptime_percentage_ = (1.0f - error_rate) * 100.0f;
    
    return self_healing_enabled_;
}

} // namespace heip

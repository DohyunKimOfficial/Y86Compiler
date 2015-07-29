#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "./y86.h"

namespace y86compiler {
Y86Operand::Y86Operand() {}

Y86Register::Y86Register(enum Y86RegisterType reg_type)
: Y86Operand(), reg_type(reg_type) {
}

Y86Register::Y86Register(std::string reg_str)
: Y86Operand(), reg_type(register_parse[reg_str]) {
}

std::string
Y86Register::to_string() {
  return rs_dictionary[this->reg_type];
}

std::string
Y86Register::to_hexstring() {
  char hex[2];
  sprintf(hex, "%1x", this->reg_type);

  return std::string(hex);
}

Y86Immediate::Y86Immediate(data_t value)
: Y86Operand(), value(value) {
}

Y86Immediate::Y86Immediate(std::string s_value) {
  data_t rep_value;
  data_t actual_value;
#ifdef y86_32
  sscanf(s_value.c_str(), "%08x", &rep_value);
#else
  sscanf(s_value.c_str(), "%16lx", &rep_value);
#endif  // y86_32

  int8_t* ptr_v = (int8_t*)(&rep_value);
  int8_t* ptr_rv = (int8_t*)(&actual_value);

  for (uint32_t i = 0; i < sizeof(data_t); i++) {
    ptr_rv[sizeof(data_t)-i-1] = ptr_v[i];
  }

  this->value = actual_value;
}

std::string
Y86Immediate::to_hexstring() {
  data_t rep_value;
  int8_t* ptr_v = (int8_t*)(&this->value);
  int8_t* ptr_rv = (int8_t*)(&rep_value);

  for (uint32_t i = 0; i < sizeof(data_t); i++) {
    ptr_rv[sizeof(data_t)-i-1] = ptr_v[i];
  }

#ifdef y86_32
  char hex[9];
  sprintf(hex, "%08x", rep_value);
#else
  char hex[17];
  sprintf(hex, "%016lx", rep_value);
#endif

  return std::string(hex);
}

std::string
Y86Immediate::to_string() {
#ifdef y86_32
  char dec[13];
  sprintf(dec, "$%d", this->value);
#else
  char dec[26];
  sprintf(dec, "$%ld", this->value);
#endif  // y86_32

  return std::string(dec);
}

Y86Assembly::Y86Assembly()
: i_inst(i_unknown), ic_inst(ic_al), num_operand(0), next(NULL) {
}

Y86Assembly::Y86Assembly(std::string hex_str)
: next(NULL) {
  std::string inst_switch = hex_str.substr(0,2);
  this->i_inst = inst_hex_parse[inst_switch].first;
  this->ic_inst = inst_hex_parse[inst_switch].second;

  switch (this->i_inst) {
    case i_halt:
    case i_nop:
    case i_ret:
      this->num_operand = 0;
      this->operand[0] = NULL;
      this->operand[1] = NULL;
      this->operand[2] = NULL;
      break;
    case i_jmp:
    case i_call:
      this->num_operand = 1;
#ifdef y86_32
      this->operand[0] = new Y86Immediate(hex_str.substr(2,8));
      this->operand[1] = NULL;
      this->operand[2] = NULL;
#else
      this->operand[0] = new Y86Immediate(hex_str.substr(2,16));
      this->operand[1] = NULL;
      this->operand[2] = NULL;
#endif  // y86_32
      break;
    case i_cmov:
    case i_op:
      this->num_operand = 2;
      this->operand[0] = new Y86Register(hex_str.substr(2,1));
      this->operand[1] = new Y86Register(hex_str.substr(3,1));
      this->operand[2] = NULL;
      break;
    case i_push:
    case i_pop:
      this->num_operand = 1;
      this->operand[0] = new Y86Register(hex_str.substr(2,1));
      this->operand[1] = NULL;
      this->operand[2] = NULL;
      break;
    case i_irmov:
      this->num_operand = 2;
#ifdef y86_32
      this->operand[0] = new Y86Immediate(hex_str.substr(4,8));
      this->operand[1] = new Y86Register(hex_str.substr(3,1));
#else
      this->operand[0] = new Y86Immediate(hex_str.substr(4, 16));
      this->operand[1] = new Y86Register(hex_str.substr(3,1));
#endif  // y86_32
      this->operand[2] = NULL;
      break;
    case i_rmmov:
    case i_mrmov:
      this->num_operand = 3;
#ifdef y86_32
      this->operand[0] = new Y86Register(hex_str.substr(2,1));
      this->operand[1] = new Y86Register(hex_str.substr(3,1));
      this->operand[2] = new Y86Immediate(hex_str.substr(4,8));
#else
      this->operand[0] = new Y86Register(hex_str.substr(2,1));
      this->operand[1] = new Y86Register(hex_str.substr(3,1));
      this->operand[2] = new Y86Immediate(hex_str.substr(4,16));
#endif  // y86_32
      break;
    default:
      // TODO default
      break;
  }
}

Y86Assembly::~Y86Assembly() {
  for (int32_t i = 0; i < this->num_operand; i++) {
    delete this->operand[i];
  }
}

Y86Assembly::Y86Assembly(Y86InstType i_inst,
                         Y86InstCondType ic_inst,
                         Y86Operand* oper1,
                         Y86Operand* oper2,
                         Y86Operand* oper3,
                         Y86Assembly* next)
: num_operand(0), i_inst(i_inst), ic_inst(ic_inst), next(next)
{
}

std::string
Y86Assembly::to_string() {
  std::pair<enum Y86InstType, enum Y86InstCondType> key;
  key.first = this->i_inst;
  key.second = this->ic_inst;

  std::string result = inst_string[key] + " ";

  for (int32_t i = 0; i < this->num_operand; i++) {
    result += this->operand[i]->to_string();

    if (i < this->num_operand - 1) {
      result += ",";
    }
  }

  return result;
}

uint32_t
Y86Assembly::get_hex_length() {
  uint32_t length;
  switch(this->i_inst) {
    case i_halt:
    case i_nop:
    case i_ret:
      length = 2;
      break;
    case i_op:
    case i_cmov:
    case i_push:
    case i_pop:
      length = 4;
      break;
#ifdef y86_32
    case i_jmp:
    case i_call:
      length = 10;
      break;
    case i_irmov:
    case i_rmmov:
    case i_mrmov:
      length = 12;
      break;
    default:
      length = 8;
      break;
#else
    case i_jmp:
    case i_call:
      length = 18;
      break;
    case i_irmov:
    case i_rmmov:
    case i_mrmov:
      length = 20;
      break;
    default:
      length = 16;
      break;
#endif  // y86_32
  }

  return length;
}

}  // namespace y86compiler

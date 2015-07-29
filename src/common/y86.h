#ifndef COMMON_Y86_H_
#define COMMON_Y86_H_

#include <map>
#include <string>
#include <utility>

#include "./common.h"

namespace y86compiler {
enum Y86InstType {
  i_unknown = -1,
  i_halt    =  0,
  i_nop     =  1,
  i_cmov    =  2,
  i_irmov   =  3,
  i_rmmov   =  4,
  i_mrmov   =  5,
  i_op      =  6,
  i_jmp     =  7,
  i_call    =  8,
  i_ret     =  9,
  i_push    = 10,
  i_pop     = 11
};

enum Y86InstCondType {
  ic_al     =  0,
  ic_le     =  1,
  ic_lt     =  2,
  ic_eq     =  3,
  ic_ne     =  4,
  ic_ge     =  5,
  ic_gt     =  6
};

enum Y86RegisterType {
  r_invalid = 15,
#ifdef y86_32
  r_eax     =  0,
  r_ecx     =  1,
  r_edx     =  2,
  r_ebx     =  3,
  r_esi     =  6,
  r_edi     =  7,
  r_esp     =  4,
  r_ebp     =  5
#else
  r_rax     =  0,
  r_rcx     =  1,
  r_rdx     =  2,
  r_rbx     =  3,
  r_rsp     =  4,
  r_rbp     =  5,
  r_rsi     =  6,
  r_rdi     =  7,
  r_r8      =  8,
  r_r9      =  9,
  r_r10     = 10,
  r_r11     = 11,
  r_r12     = 12,
  r_r13     = 13,
  r_r14     = 14
#endif  // 32BIt
};

static std::map<std::string, enum Y86RegisterType> sr_dictionary = {
#ifdef y86_32
  {"%eax", r_eax}, {"%ecx", r_ecx}, {"%edx", r_edx}, {"%ebx", r_ebx},
  {"%esi", r_esi}, {"%edi", r_edi}, {"%esp", r_esp}, {"%ebp", r_ebp}
#else
  {"%rax", r_rax}, {"%rcx", r_rcx}, {"%rdx", r_rdx}, {"%rbx", r_rbx},
  {"%rsp", r_rsp}, {"%rbp", r_rbp}, {"%rsi", r_rsi}, {"%rdi", r_rdi},
  {"%r8",  r_r8},  {"%r9",  r_r9},  {"%r10", r_r10}, {"%r11", r_r11},
  {"%r12", r_r12}, {"%r13", r_r13}, {"%r14", r_r14}
#endif  // y86_32
};

static std::map<enum Y86RegisterType, std::string> rs_dictionary = {
#ifdef y86_32
  {r_eax, "%eax"}, {r_ecx, "%ecx"}, {r_edx, "%edx"}, {r_ebx, "%ebx"},
  {r_esi, "%esi"}, {r_edi, "%edi"}, {r_esp, "%esp"}, {r_ebp, "%ebp"}
#else
  {r_rax, "%rax"}, {r_rcx, "%rcx"}, {r_rdx, "%rdx"}, {r_rbx, "%rbx"},
  {r_rsp, "%rsp"}, {r_rbp, "%rbp"}, {r_rsi, "%rsi"}, {r_rdi, "%rdi"},
  {r_r8,   "%r8"}, {r_r9,   "%r9"}, {r_r10, "%r10"}, {r_r11, "%r11"},
  {r_r12, "%r12"}, {r_r13, "%r13"}, {r_r14, "%r14"}
#endif  // y86_32
};

static std::map<std::string,
                std::pair<enum Y86InstType,
                          enum Y86InstCondType> > inst_parse = {
  {"halt",     { i_halt, ic_al}},
  {"nop",      {  i_nop, ic_al}},
  {"cmoval",   { i_cmov, ic_al}},
  {"cmovle",   {  i_jmp, ic_le}},
  {"cmovl",    {  i_jmp, ic_lt}},
  {"cmove",    {  i_jmp, ic_eq}},
  {"cmovne",   {  i_jmp, ic_ne}},
  {"cmovge",   {  i_jmp, ic_ge}},
  {"cmovg",    {  i_jmp, ic_gt}},
  {"jal",      {  i_jmp, ic_al}},
  {"jle",      {  i_jmp, ic_le}},
  {"jl",       {  i_jmp, ic_lt}},
  {"je",       {  i_jmp, ic_eq}},
  {"jne",      {  i_jmp, ic_ne}},
  {"jg",       {  i_jmp, ic_ge}},
  {"jgt",      {  i_jmp, ic_gt}},
  {"call",     { i_call, ic_al}},
  {"ret",      {  i_ret, ic_al}},
#ifdef y86_32
  {"irmovl",   {i_irmov, ic_al}},
  {"rmmovl",   {i_rmmov, ic_al}},
  {"mrmovl",   {i_mrmov, ic_al}},
  {"addl",     {   i_op, ic_al}},
  {"subl",     {   i_op, ic_le}},
  {"andl",     {   i_op, ic_lt}},
  {"xorl",     {   i_op, ic_eq}},
  {"pushl",    { i_push, ic_al}},
  {"popl",     {  i_pop, ic_al}}
#else
  {"irmovq",   {i_irmov, ic_al}},
  {"rmmovq",   {i_rmmov, ic_al}},
  {"mrmovq",   {i_mrmov, ic_al}},
  {"addq",     {   i_op, ic_al}},
  {"subq",     {   i_op, ic_le}},
  {"andq",     {   i_op, ic_lt}},
  {"xorq",     {   i_op, ic_eq}},
  {"pushq",    { i_push, ic_al}},
  {"popq",     {  i_pop, ic_al}}
#endif  // y86_32
};

static std::map<std::string,
                std::pair<enum Y86InstType,
                          enum Y86InstCondType> > inst_hex_parse = {
  {"00", { i_halt, ic_al}},
  {"10", {  i_nop, ic_al}},
  {"20", { i_cmov, ic_al}},
  {"21", { i_cmov, ic_le}},
  {"22", { i_cmov, ic_lt}},
  {"23", { i_cmov, ic_eq}},
  {"24", { i_cmov, ic_ne}},
  {"25", { i_cmov, ic_ge}},
  {"26", { i_cmov, ic_gt}},
  {"70", {  i_jmp, ic_al}},
  {"71", {  i_jmp, ic_le}},
  {"72", {  i_jmp, ic_lt}},
  {"73", {  i_jmp, ic_eq}},
  {"74", {  i_jmp, ic_ne}},
  {"75", {  i_jmp, ic_ge}},
  {"76", {  i_jmp, ic_gt}},
  {"80", { i_call, ic_al}},
  {"90", {  i_ret, ic_al}},
#ifdef y86_32
  {"30", {i_irmov, ic_al}},
  {"40", {i_rmmov, ic_al}},
  {"50", {i_mrmov, ic_al}},
  {"60", {   i_op, ic_al}},
  {"61", {   i_op, ic_le}},
  {"62", {   i_op, ic_lt}},
  {"63", {   i_op, ic_eq}},
  {"a0", { i_push, ic_al}},
  {"b0", {  i_pop, ic_al}}
#else
  {"30", {i_irmov, ic_al}},
  {"40", {i_rmmov, ic_al}},
  {"50", {i_mrmov, ic_al}},
  {"60", {   i_op, ic_al}},
  {"61", {   i_op, ic_le}},
  {"62", {   i_op, ic_lt}},
  {"63", {   i_op, ic_eq}},
  {"a0", { i_push, ic_al}},
  {"b0", {  i_pop, ic_al}}
#endif  // y86_32
};

static std::map<std::pair<enum Y86InstType,
                          enum Y86InstCondType>,
                std::string> inst_string = {
  {{i_halt, ic_al}, "halt"},
  {{i_nop, ic_al}, "nop"},
  {{i_cmov, ic_al}, "cmoval"},
  {{i_cmov, ic_le}, "cmovle"},
  {{i_cmov, ic_lt}, "cmovl"},
  {{i_cmov, ic_eq}, "cmove"},
  {{i_cmov, ic_ge}, "cmovge"},
  {{i_cmov, ic_gt}, "cmovg"},
  {{i_jmp, ic_al}, "jal"},
  {{i_jmp, ic_le}, "jle"},
  {{i_jmp, ic_lt}, "jl"},
  {{i_jmp, ic_eq}, "je"},
  {{i_jmp, ic_ge}, "jge"},
  {{i_jmp, ic_gt}, "jg"},
  {{i_call, ic_al}, "call"},
  {{i_ret, ic_al}, "ret"},
#ifdef y86_32
  {{i_irmov, ic_al}, "irmovl"},
  {{i_rmmov, ic_al}, "rmmovl"},
  {{i_mrmov, ic_al}, "mrmovl"},
  {{i_op, ic_al}, "addl"},
  {{i_op, ic_le}, "subl"},
  {{i_op, ic_lt}, "andl"},
  {{i_op, ic_eq}, "xorl"},
  {{i_push, ic_al}, "pushl"},
  {{i_pop, ic_al}, "popl"}
#else
  {{i_irmov, ic_al}, "irmovq"},
  {{i_rmmov, ic_al}, "rmmovq"},
  {{i_mrmov, ic_al}, "mrmovq"},
  {{i_op, ic_al}, "addq"},
  {{i_op, ic_le}, "subq"},
  {{i_op, ic_lt}, "andq"},
  {{i_op, ic_eq}, "xorq"},
  {{i_push, ic_al}, "pushq"},
  {{i_pop, ic_al}, "popq"}
#endif  // y86_32
};

static std::map<std::string, enum Y86RegisterType> register_parse = {
#ifdef y86_32
  {"0", r_eax},
  {"1", r_ecx},
  {"2", r_edx},
  {"3", r_ebx},
  {"6", r_esi},
  {"7", r_edi},
  {"4", r_esp},
  {"5", r_ebp}
#else
  {"0", r_rax},
  {"1", r_rcx},
  {"2", r_rdx},
  {"3", r_rbx},
  {"6", r_rsi},
  {"7", r_rdi},
  {"4", r_rsp},
  {"5", r_rbp},
  {"8", r_r8},
  {"9", r_r9},
  {"a", r_r10},
  {"b", r_r11},
  {"c", r_r12},
  {"d", r_r13},
  {"e", r_r14}
#endif  // y86_32
};

class Y86Operand {
 public:
  Y86Operand();
  virtual std::string to_string() = 0;
  virtual std::string to_hexstring() = 0;
};

class Y86Register : public Y86Operand {
 private:
  enum Y86RegisterType reg_type;
 public:
  Y86Register(enum Y86RegisterType reg_type);
  Y86Register(std::string hex_str);
  std::string to_string();
  std::string to_hexstring();
};

class Y86Immediate : public Y86Operand {
 private:
  data_t value;
 public:
  Y86Immediate(data_t value);
  Y86Immediate(std::string hex_str);
  std::string to_string();
  std::string to_hexstring();
};

//----------------------------------------------------------------------------
/// @brief Simple container for y86 assembly code
///
class Y86Assembly {
 private:
  Y86InstType i_inst;
  Y86InstCondType ic_inst;
  Y86Operand* operand[3];
  int32_t num_operand;
  Y86Assembly* next;

 public:
  Y86Assembly();
  Y86Assembly(std::string hex_str);
  Y86Assembly(Y86InstType i_inst,
              Y86InstCondType ic_inst,
              Y86Operand* oper1,
              Y86Operand* oper2,
              Y86Operand* oper3,
              Y86Assembly* next);
  ~Y86Assembly();

  std::string to_string();

  uint32_t get_hex_length();

  Y86Assembly* get_next();
  void set_next(Y86Assembly *next);
};
}

#endif  // COMMON_Y86_H_

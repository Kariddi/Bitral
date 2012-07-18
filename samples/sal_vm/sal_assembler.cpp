#include <iostream>
#include <streambuf>
#include <sstream>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <boost/unordered_map.hpp>

using namespace std;

enum sal_tokens { LD, ST, ADD, SUB, MUL, DIV, CMP, MOV, OR, XOR, AND, TEST, 
                  ADDI,SUBI, MULI, DIVI, CMPI, MOVI, ORI, XORI, ANDI, TESTI,
                  BRE, BRLE, BRL, BRG, BRGE, BR, HLT, NOP, INTEGER, REG_A_TOK,
                  REG_B_TOK, REG_C_TOK, REG_D_TOK, REG_E_TOK, REG_F_TOK, REG_SP_TOK, 
                  REG_PC_TOK, REG_STATUS_TOK, NO_REC_TOK, EOF_TOK };

int value;
ifstream inputf;
ofstream outputf;
sal_tokens current_token;
boost::unordered_map<string, sal_tokens> opcode_map;
boost::unordered_map<string, sal_tokens> reg_map;
typedef boost::unordered_map<string, sal_tokens>::iterator opcode_map_it; 
typedef boost::unordered_map<string, sal_tokens>::iterator reg_map_it;  
//stringstream sbf;

static void initLexer() {
  //opcode_map.reserve(NOP+1);
  //reg_map.reserve(NO_REC_TOK-REG_A_TOK);

  opcode_map["LD"] = LD;
  opcode_map["ST"] = ST;
  opcode_map["ADD"] = ADD;
  opcode_map["SUB"] = SUB;
  opcode_map["MUL"] = MUL;
  opcode_map["DIV"] = DIV;
  opcode_map["CMP"] = CMP;
  opcode_map["MOV"] = MOV;
  opcode_map["OR"] = OR;
  opcode_map["XOR"] = XOR;
  opcode_map["AND"] = AND;
  opcode_map["TEST"] = TEST;
  opcode_map["ADDI"] = ADDI;
  opcode_map["SUBI"] = SUBI;
  opcode_map["MULI"] = MULI;
  opcode_map["DIVI"] = DIVI;
  opcode_map["CMPI"] = CMPI;
  opcode_map["MOVI"] = MOVI;
  opcode_map["ORI"] = ORI;
  opcode_map["XORI"] = XORI;
  opcode_map["ANDI"] = ANDI;
  opcode_map["TESTI"] = TESTI;
  opcode_map["BRE"] = BRE;
  opcode_map["BRLE"] = BRLE;
  opcode_map["BRL"] = BRL;
  opcode_map["BRG"] = BRG;
  opcode_map["BRGE"] = BRGE;
  opcode_map["BR"] = BR;
  opcode_map["HLT"] = HLT;
  opcode_map["NOP"] = NOP;
  reg_map["A"] = REG_A_TOK;
  reg_map["B"] = REG_B_TOK;
  reg_map["C"] = REG_C_TOK;
  reg_map["D"] = REG_D_TOK;
  reg_map["E"] = REG_E_TOK;
  reg_map["F"] = REG_F_TOK;
  reg_map["SP"] = REG_SP_TOK;
  reg_map["PC"] = REG_PC_TOK;
  reg_map["STATUS"] = REG_STATUS_TOK;
}

static sal_tokens lexer() {
  string str_read;
  int c = inputf.get();
  if (c == EOF)
    return EOF_TOK;
  //Eat white chars
  while (isspace(c))
    c = inputf.get();
  if (isdigit(c) || c == '-') {
    stringstream ss;
    //Recognize number
    do {
      ss << static_cast<const char>(c);
      c = inputf.get();
    } while (isdigit(c));
    ss >> value;
    return INTEGER;
  } else {
    stringstream ss;
    //Recognize opcode or register
    if (c == '$') {
      //REGISTER
      c = inputf.get();
      do {
        ss << static_cast<const char>(c);
        c = inputf.get();
      } while (isalpha(c));
      
      if (!isspace(c) && c != EOF)
        inputf.unget();
 
      str_read = ss.str();
      reg_map_it token_iterator = reg_map.find(str_read);
      if (token_iterator != reg_map.end())
        return token_iterator->second;
      else {
        inputf.seekg(-str_read.size()+1, ios::cur);
        value = str_read[0];
        return NO_REC_TOK; 
      }
    } else if (isalpha(c)) {
      //Opcode
      do {
        ss << static_cast<const char>(c);
        c = inputf.get();
      } while (isalpha(c));
      
      if (!isspace(c) && c != EOF)
        inputf.unget();
  
      str_read = ss.str();
      opcode_map_it token_iterator = opcode_map.find(str_read);
      if (token_iterator != opcode_map.end())
        return token_iterator->second;
      else {
        inputf.seekg(-str_read.size()+1, ios::cur);
        value = str_read[0];
        return NO_REC_TOK; 
      } 
    } else {
      value = c;
      return NO_REC_TOK;
    }
  }
  return NO_REC_TOK; //Unreachable, but suppresses warning
}

static bool parseData() {
  if (current_token == NO_REC_TOK)
    return false;

  while (current_token == INTEGER) {
    outputf << static_cast<char>(0);
    outputf.write((const char*) &value, sizeof(value));
    current_token = lexer();
  }
  if (current_token != NO_REC_TOK)
    return true;
  else
    return false;
}

static bool parseRegRegInst() {
  char data[4];
  data[0] = static_cast<char>(current_token);
  data[1] = 0;
  current_token = lexer();
  if (current_token >= REG_A_TOK && current_token <= REG_STATUS_TOK)
    data[2] = static_cast<char>(current_token-REG_A_TOK);
  else
    return false;
  current_token = lexer();
  if (current_token != NO_REC_TOK || value != ',')
    return false;
  current_token = lexer();
  if (current_token >= REG_A_TOK && current_token <= REG_STATUS_TOK)
    data[3] = static_cast<char>(current_token);
  else
     return false;
  outputf.write(data, 4);
  return true;
}

static bool parseRegImmInst() {
  char data[4];
  data[0] = static_cast<char>(current_token);
  current_token = lexer();
  if (current_token >= REG_A_TOK && current_token <= REG_STATUS_TOK)
    data[1] = static_cast<char>(current_token);
  else
    return false;
  current_token = lexer();
  if (current_token != NO_REC_TOK || value != ',')
    return false;
  current_token = lexer();
  if (current_token == INTEGER) {
    data[2] = static_cast<char>(value & 0xff);
    data[3] = static_cast<char>((value >> 8) & 0xff);
  } else
    return false;
  outputf.write(data, 4);
  return true;
}

static bool parseImmOnlyInst() {
  char data[4];
  data[0] = static_cast<char>(current_token);
  current_token = lexer();
  if (current_token == INTEGER) {
    data[1] = static_cast<char>(value & 0xff);
    data[2] = static_cast<char>((value >> 8) & 0xff); 
    data[3] = static_cast<char>((value >> 16) & 0xff);
  }
  else
    return false;

  outputf.write(data, 4);
  return true;

}

static bool parseNoOperandInst() {
  char data[4];
  data[0] = static_cast<char>(current_token);
  data[1] = 0;
  data[2] = 0;
  data[3] = 0;

  outputf.write(data, 4);
  return true;
}

static bool parseInstructions() {
  bool valid_parse = true;
  if (current_token < LD || current_token > NOP)
    return false;
  while (current_token >= LD && current_token <= NOP) {
    if (current_token >= LD && current_token <= TEST)
      //REG + REG instruction
      valid_parse = parseRegRegInst();
    else if (current_token >= ADDI && current_token <= TESTI)
      valid_parse = parseRegImmInst();
    else if (current_token >= BRE && current_token <= BR)
      valid_parse = parseImmOnlyInst();
    else
      valid_parse = parseNoOperandInst();
    if (!valid_parse)
      break;
    current_token = lexer();
  }

  return valid_parse;
}

int main(int argc, char** argv) {

  if (argc != 3)
    return 1;

  const char* input_path = argv[1];
  const char* output_path = argv[2];

  inputf.open(input_path);
  outputf.open(output_path, fstream::trunc);
  
  initLexer();  
  
  current_token = lexer();
  if (!parseData()) {
    cerr << "Error parsing data part\n";
    inputf.close();
    outputf.close();
    remove(output_path);
    return 1;
  }

//  while (current_token != EOF_TOK) {
  if (!parseInstructions() || current_token != EOF_TOK) {
    cerr << "Error parsing instruction: " << current_token << endl;
    inputf.close();
    outputf.close();
    remove(output_path);
    return 1;
  }
//    current_token = lexer();
//  }

  inputf.close();
  outputf.close();
//  while ((token = lexer()) != EOF_TOK) {

/*    if (token < NOP)
      cout << "Found instruction number: " << token << endl;
    else if ( token >= REG_A && token <= REG_STATUS)
      cout << "Found register\n";
    else if ( token == INTEGER )
      cout << "Found integer: " << value << endl;
    else if (token == NO_REC_TOK )
      cout << "Character: " << static_cast<char>(value) << endl;
  */
  //}
//  int data;
  // Parsing data part
/*  while (inputf.get(*sbf.rdbuf()).good()) {
    data = inputf.get();
    sbf >> data;
    cout << data << endl;
    outputf.put(0);
    outputf.write((const char*)&data, sizeof(data));
    sbf.clear();
  }*/

  return 0;
}

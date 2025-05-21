#ifndef One_Bit_ALU_h
#define One_Bit_ALU_h

#include "Digital_logic_structures.h"
#include <bitset>

class unobitALU{
  private:
    //outside values (input)
    std::bitset<1> A = false;
    std::bitset<1> B = false;
    std::bitset<1> ENA = false;
    std::bitset<1> ENB = false;
    std::bitset<1> INVA = false;
    std::bitset<1> F1 = false;
    std::bitset<1> F2 = false;
    std::bitset<1> Cin = false;
    //outside values (output)
    std::bitset<1> Cout = false;
    std::bitset<1> Output = false;
    //inside values
    //Decoder
    std::bitset<1> Dand(){
      return AND(NOT(F1),NOT(F2));
    }
    std::bitset<1> Dnotb(){
      return AND(NOT(F1),F2);
    }
    std::bitset<1> Dor(){
      return AND(F1,NOT(F2));
    }
    std::bitset<1> Dsum(){
      return AND(F1,F2);
    }
    //Logical unit
    std::bitset<1> AB(){
      return AND(Dand(),AND(XOR(INVA,AND(A,ENA)),AND(B,ENB)));
    }
    std::bitset<1> AplusB(){
      return AND(Dor(),OR(XOR(INVA,AND(A,ENA)),AND(B,ENB)));
    }
    std::bitset<1> notB(){
      return AND(Dnotb(),NOT(AND(B,ENB)));
    }
    //Full adder
    std::bitset<1> half_sum(std::bitset<1>a ,std::bitset<1> b){
      return XOR(a,b);
    }
    std::bitset<1> half_carryout(std::bitset<1>a ,std::bitset<1> b, std::bitset<1> c){
      return AND(AND(a,b),c);
    }
    std::bitset<1> full_sum(){
      return AND(half_sum(half_sum(XOR(INVA,AND(A,ENA)),AND(B,ENB)),Cin),Dsum());
    }
    std::bitset<1> full_carryout(){
      return OR(half_carryout(Dsum(),XOR(INVA,AND(A,ENA)),AND(B,ENB)),half_carryout(Dsum(),half_sum(XOR(INVA,AND(A,ENA)),AND(B,ENB)),Cin));
    }
  public:
    inline void setvalues(std::bitset<1> a, std::bitset<1> b, std::bitset<1> carryin, std::bitset<1> inva,std::bitset<1> ena, std::bitset<1> enb, std::bitset<1> f1, std::bitset<1> f2) { A = a; B = b; Cin = carryin; INVA = inva; ENA = ena; ENB = enb; F1 =f1; F2 = f2; }
    void unoULArun(std::bitset<1> &cout, std::bitset<1> &output){ 
      output = OR(OR(AB(),AplusB()),OR(notB(),full_sum()));
      cout = full_carryout();
      }
};

#endif
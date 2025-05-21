#include "Digital_logic_structures.h"
#include "One_Bit_ALU.h"
#include <iostream>

class fullALU {
private:
  // outside values (input)
  std::bitset<8> A;
  std::bitset<8> B;
  std::bitset<1> ENA = 0;
  std::bitset<1> ENB = 0;
  std::bitset<1> F1 = 0;
  std::bitset<1> F2 = 0;
  std::bitset<1> F3 = 0;
  std::bitset<1> Cin = 0;
  int overflow = 0;
  // outside values (output)
  std::bitset<1> Cout = 0;
  std::bitset<8> Output = 0;
  std::bitset<1> F = 0;
  unobitALU oneALU;
  // Additional structure
  void inverter(std::bitset<8> a) {
    std::bitset<1> output;

    for (int i = 0; i < 8; i++) {
      output = invplusone(i, (std::bitset<1>)a[i]);
      if (Cout == 1)
        overflow++;
      if (overflow != 0) {
        Cin = 1;
        overflow--;
      } else
        Cin = 0;
      B[i] = output[0];
    }
    Cin = 0;
  }
  // Decoder
  std::bitset<1> Dminus() { return AND(AND(NOT(F1), NOT(F2)), NOT(F3)); }
  std::bitset<1> Dplus() { return AND(AND(NOT(F1), NOT(F2)), F3); }
  std::bitset<1> Dmulti() { return AND(AND(NOT(F1), F2), NOT(F3)); }
  std::bitset<1> Dshifttoleft() { return AND(AND(NOT(F1), F2), F3); }
  std::bitset<1> Dminusone() { return AND(AND(F1, NOT(F2)), NOT(F3)); }
  std::bitset<1> DBnotequal() { return AND(AND(F1, NOT(F2)), F3); }
  std::bitset<1> Dshifttoright() { return AND(AND(F1, F2), NOT(F3)); }
  std::bitset<1> DAnotequal() { return AND(AND(F1, F2), F3); }
  // Logic unit
  std::bitset<1> minus(std::bitset<1> a, std::bitset<1> b) {
    std::bitset<1> output;
    oneALU.setvalues(a, b, Cin, 0, ENA, ENB, 1, 1);
    oneALU.unoULArun(Cout, output);
    return output;
  }
  std::bitset<1> plus(std::bitset<1> a, std::bitset<1> b) {
    std::bitset<1> output;
    oneALU.setvalues(a, b, Cin, 0, ENA, ENB, 1, 1);
    oneALU.unoULArun(Cout, output);
    return output;
  }
  std::bitset<1> shifter(std::bitset<1> a, std::bitset<1> b,
                         std::bitset<1> direction) {
    std::bitset<1> output;
    oneALU.setvalues(AND(b, direction), AND(a, NOT(direction)), 0, 0, 1, 1, 1,
                     0);
    oneALU.unoULArun(Cout, output);
    return output;
  }
  std::bitset<1> minusone(std::bitset<1> a) {
    oneALU.setvalues(0, a, 0, 0, 0, 1, 0, 1);
    oneALU.unoULArun(Cout, a);
    return a;
  }

  std::bitset<1> invplusone(int i, std::bitset<1> a) {
    std::bitset<1> output;
    if (i == 0) {
      oneALU.setvalues(a, 1, Cin, 1, ENA, ENB, 1, 1);
      oneALU.unoULArun(Cout, output);
      return output;
    } else {
      oneALU.setvalues(a, 0, Cin, 1, ENA, ENB, 1, 1);
      oneALU.unoULArun(Cout, output);
      return output;
    }
  }
  std::bitset<1> EQUAL(std::bitset<1> a, std::bitset<1> b) {
    return NOT(XOR(a, b));
  }
  // mux

  void mux(int i, std::bitset<1> a, std::bitset<1> b, bool &index) {
    std::bitset<1> output;
    if (Dminus() == 1) {
      if (i == 0)
        inverter(B);
      Output[i] = minus(a, b)[0];
    } else if (Dplus() == 1)
      Output[i] = plus(a, b)[0];
    else if (Dmulti() == 1) {
      // VELIAU PADARYTI!!!!!!!!!!!!!!!!!!!
      Output[i] = output[0];
    } else if (Dshifttoleft() == 1) {
      if (i == 0)
        output = AND(0, (std::bitset<1>)A[i + 1]);
      else if (i == 7)
        output = AND(NOT(0), (std::bitset<1>)A[i - 1]);
      else
        output = shifter((std::bitset<1>)A[i - 1], (std::bitset<1>)A[i + 1], 0);
      Output[i] = output[0];
    } else if (Dminusone() == 1) {
      if (A[i] == 0)
        A[i] = minusone((std::bitset<1>)A[i])[0];
      else {
        A[i] = minusone((std::bitset<1>)A[i])[0];
        index = true;
      }
      Output = A;
    } else if (DBnotequal() == 1) {
      if (B[i] != 0) {
        F = false;
        index = true;
      }
    } else if (Dshifttoright() == 1) {
      Output[i] = output[0];
    } else if (DAnotequal() == 1) {
      Output[i] = output[0];
    }
  }

public:
  inline void setvalues(std::bitset<8> a, std::bitset<8> b, std::bitset<1> cin,
                        std::bitset<1> ENa, std::bitset<1> ENb,
                        std::bitset<1> f1, std::bitset<1> f2,
                        std::bitset<1> f3) {
    A = a;
    B = b;
    Cin = cin;
    ENA = ENa;
    ENB = ENb;
    F1 = f1;
    F2 = f2;
    F3 = f3;
  }
  std::bitset<8> RUN() {
    bool index = false;
    for (int i = 0; i < 8; i++) {
      mux(i, (std::bitset<1>)A[i], (std::bitset<1>)B[i], index);
      if (Cout == 1)
        overflow++;
      if (overflow == 0) {
        Cin = 0;
      } else {
        Cin = 1;
        overflow--;
      }
      if (index)
        break;
    }
    return Output;
  }
  std::bitset<1> retrunf() { return F; }
};

int main() {
  fullALU ALU;
  ALU.setvalues(0b01011111, 0b00000011, 0, 1, 1, 0, 0, 0);
  std::cout << "Output: " << ALU.RUN() << std::endl;
  std::cout << "F: " << ALU.retrunf() << std::endl;
  return 0;
}
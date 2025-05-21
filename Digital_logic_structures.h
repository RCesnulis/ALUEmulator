#ifndef Digital_logic_structures_H
#define Digital_logic_structures_H

#include <bitset>

std::bitset<1> NAND(std::bitset<1> a,std::bitset<1> b){
  if(a == 1 && b == 1)
    return 0;
  return 1;
}
std::bitset<1> NOT(std::bitset<1> a){
  return NAND(a,a);
}
std::bitset<1> AND(std::bitset<1> a, std::bitset<1> b){
  return NAND(NAND(a,b),NAND(a,b));
}
std::bitset<1> OR(std::bitset<1> a, std::bitset<1> b){
  return NAND(NAND(a,a),NAND(b,b));
}
std::bitset<1> NOR(std::bitset<1> a, std::bitset<1> b){
  return NAND(NAND(NAND(a,a),NAND(b,b)),NAND(NAND(a,a),NAND(b,b)));
}
std::bitset<1> XOR(std::bitset<1> a, std::bitset<1> b){
  return NAND(NAND(a,NAND(a,b)),NAND(b,NAND(a,b)));
}

#endif
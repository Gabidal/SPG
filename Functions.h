#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <vector>

class Pattern;
class Node;

extern unsigned char Rock_Generator(Pattern* p, Node* node);

extern unsigned char Tree_Generator(Pattern* p, Node* node);

extern unsigned char Rikka_Generator(Pattern* p, Node* node);

extern unsigned char River_Generator(Pattern* p, Node* node);

extern unsigned char Cactus_Generator(Pattern* p, Node* node);

extern inline Node* At(Node* list, int x, int z);

//extern void Water_Flow(Pattern* p, int X, int Z);

template<typename T>
extern void Append(std::vector<T>& a, std::vector<T> b);

#endif
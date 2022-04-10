#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

class Pattern;
class Node;

extern unsigned char Rock_Generator(Pattern* p, Node* node);

extern unsigned char Tree_Generator(Pattern* p, Node* node);

extern unsigned char Rikka_Generator(Pattern* p, Node* node);

extern unsigned char River_Generator(Pattern* p, Node* node);

extern inline Node* At(Node* list, int x, int z);

#endif
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <vector>
#include <string>
#include <functional>

class Node {
public:
    float Y;
    unsigned char Color;

    /*Node(float y = 0, char c = 0) {
        Y = y;
        Color = c;
    }*/
};

class Pattern;
typedef unsigned char (*FUNCTION)(Pattern*, int Amount);

class Packet {
public:
    FUNCTION Function;
    float Weight;

    Packet(FUNCTION f, float w) {
        Function = f;
        Weight = w;
    }
};

class Pattern {
public:
    unsigned char Color;  //Colors represent node ground types.
    Node* Nodes; //Points back to the chunk.
    int X;	//starting address X
    int Z;	//starting address Y
    FUNCTION Function; //modifier
    float Weight = 0;

    //First in main we create these patterns, and later on
    //we give them the target node list.
    Pattern(FUNCTION func);

    Pattern(FUNCTION func, float weight);

    Pattern(int x, int y, Pattern& p);

    void Calculate(int x, int z, Node* nodes);

    /*Node& At(int X, int Z) {
        return Nodes[(CHUNK_SIZE * X) + Z];
    }*/
};

//-res [how much points shall there be?]
//Note the default chunk size is 16x16
[[nodiscard]]
extern std::vector<Node*> TerGen(std::string args, std::vector<Packet> Packets);

class TerGen_Chunk;
class Node;

class TerGen_Chunk_Coordinates {
public:
    int X;
    int Z;

    TerGen_Chunk_Coordinates(int x, int z) {
        X = x;
        Z = z;
    }
};

class TerGen_Node_Coordinates {
public:
    int X;
    int Z;

    TerGen_Node_Coordinates(int x, int z) {
        X = x;
        Z = z;
    }
};

namespace UTILS
{
    extern unsigned char Get_Free_Color();
    extern TerGen_Chunk* Get_Chunk(TerGen_Chunk_Coordinates coordinates);
    extern TerGen_Chunk* Get_Chunk(TerGen_Node_Coordinates coordinates);
    extern Node* Get_Node(int x, int z);
    extern void For_All_Nodes(std::vector<Node*> nodes, std::function<void(Node*, double, double, double, double)> lambda);
    extern void For_All_Nodes(std::function<void(Node*, double, double, double, double)> lambda);

    extern unsigned char Get_Color(FUNCTION func);
    extern FUNCTION Get_Function(unsigned char color);
}

#endif
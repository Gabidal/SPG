#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>
#include <vector>

using namespace std;

class IntVector{
public:
    int X;
    int Y;
    int Z;

    IntVector(int x, int y, int z = 0) {
        X = x;
        Y = y;
        Z = z;
    }

    IntVector() {
        X = 0;
        Y = 0;
        Z = 0;
    }

    //This function is used to calculate the distance between two vectors.
    int Distance(IntVector v) {
        return  sqrt(pow(X - v.X, 2) + pow(Y - v.Y, 2) + pow(Z - v.Z, 2));
    }

    //This function add two vectors together.
    IntVector Add(IntVector v) {
        return IntVector(X + v.X, Y + v.Y, Z + v.Z);
    }

    //This function subtracts two vectors.
    IntVector Subtract(IntVector v) {
        return IntVector(X - v.X, Y - v.Y, Z - v.Z);
    }

    //This function multiplies two vectors.
    IntVector Multiply(IntVector v) {
        return IntVector(X * v.X, Y * v.Y, Z * v.Z);
    }

    //This function divides two vectors.
    IntVector Divide(IntVector v) {
        return IntVector(X / v.X, Y / v.Y, Z / v.Z);
    }

    //This function multiplies a vector with a list of vectors
    //This is used for example to calculate a explosion force to nearby objects.
    void Multiply(vector<IntVector>* v) {
        for(int i = 0; i < v->size(); i++) {
            v->at(i) = Multiply(v->at(i));
        }
    }

    IntVector Normalize(){
        int length = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));

        if (length < 0.00001) {
            return IntVector(0, 0, 0);
        }

        return IntVector(X / length, Y / length, Z / length);
    }

    IntVector Scale(int scale) {
        return IntVector(X * scale, Y * scale, Z * scale);
    }
};

class FloatVector {
public:
    float X;
    float Y;
    float Z;

    FloatVector(float x, float y, float z = 0) {
        X = x;
        Y = y;
        Z = z;
    }

    FloatVector() {
        X = 0;
        Y = 0;
        Z = 0;
    }

    //This function is used to calculate the distance between two vectors.
    float Distance(FloatVector v) {
        return  sqrt(pow(X - v.X, 2) + pow(Y - v.Y, 2) + pow(Z - v.Z, 2));
    }

    //this function add two vectors together.
    FloatVector Add(FloatVector v) {
        return FloatVector(X + v.X, Y + v.Y, Z + v.Z);
    }

    //This function subtracts two vectors.
    FloatVector Subtract(FloatVector v) {
        return FloatVector(X - v.X, Y - v.Y, Z - v.Z);
    }

    //This function multiplies two vectors.
    FloatVector Multiply(FloatVector v) {
        return FloatVector(X * v.X, Y * v.Y, Z * v.Z);
    }

    //This function divides two vectors.
    FloatVector Divide(FloatVector v) {
        return FloatVector(X / v.X, Y / v.Y, Z / v.Z);
    }

    //This function multiplies a vector with a list of vectors
    //This is used for example to calculate a explosion force to nearby objects.
    void Multiply(vector<FloatVector>* v) {
        for (int i = 0; i < v->size(); i++) {
            v->at(i) = Multiply(v->at(i));
        }
    }

    FloatVector Normalize() {
        float length = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));

        if (length < 0.00001) {
            return FloatVector(0, 0, 0);
        }

        return FloatVector(X / length, Y / length, Z / length);
    }

    FloatVector Scale(float scale) {
        return FloatVector(X * scale, Y * scale, Z * scale);
    }
};

#endif
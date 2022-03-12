#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <math.h>
#include <vector>

using namespace std;

class Vector{
public:
    float X;
    float Y;
    float Z;

    Vector(float x, float y, float z = 0) {
        X = x;
        Y = y;
        Z = z;
    }

    Vector() {
        X = 0;
        Y = 0;
        Z = 0;
    }

    //This function is used to calculate the distance between two vectors.
    float Distance(Vector v) {
        return  sqrt(pow(X - v.X, 2) + pow(Y - v.Y, 2) + pow(Z - v.Z, 2));
    }

    //This function add two vectors together.
    Vector Add(Vector v) {
        return Vector(X + v.X, Y + v.Y, Z + v.Z);
    }

    //This function subtracts two vectors.
    Vector Subtract(Vector v) {
        return Vector(X - v.X, Y - v.Y, Z - v.Z);
    }

    //This function multiplies two vectors.
    Vector Multiply(Vector v) {
        return Vector(X * v.X, Y * v.Y, Z * v.Z);
    }

    //This function divides two vectors.
    Vector Divide(Vector v) {
        return Vector(X / v.X, Y / v.Y, Z / v.Z);
    }

    //This function multiplies a vector with a list of vectors
    //This is used for example to calculate a explosion force to nearby objects.
    void Multiply(vector<Vector>* v) {
        for(int i = 0; i < v->size(); i++) {
            v->at(i) = Multiply(v->at(i));
        }
    }

    Vector Normalize(){
        float length = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));

        if (length < 0.00001) {
            return Vector(0, 0, 0);
        }

        return Vector(X / length, Y / length, Z / length);
    }

    Vector Scale(float scale) {
        return Vector(X * scale, Y * scale, Z * scale);
    }
};

#endif